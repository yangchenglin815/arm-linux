#include <QRegExp>
#include <QDir>
#include <QTextStream>
#include <QFile>
#include <QIODevice>
#include <QNetworkInterface>
#include <QList>

#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "devevdo.h"
#include "common.h"
#include "xtconfig.h"

#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_STRTMP_LEN 128
#define DIALUP_SOCKET_FILE "/var/volatile/dialup.skt"

static volatile bool isThreadToExit = false;

DevEvdo::DevEvdo(QObject *parent) :
    QThread(parent)
{
    devInit();
}

//
void DevEvdo::run()
{
    int count=0;
    unsigned int cnt = 0;
   // qDebug()<<"endoPPPDstart";
    // Dial-up
    if (!isDialupConnectionEstablished("ppp0")) {
        evdoPPPD();
    }
    int rssiValue=99;
  //  qDebug()<<"evdoPPPDend";
    //
    while (!isThreadToExit) {
        //
         //getIPCount();

        int c = GetNetCardCount();
        // qDebug()<<"getnetcardcount:"<<c<<"count="<<count<<"rssi="<<rssiValue;
         if(c>=1)
             count=0;
         else
             count++;
         if(count>20)
             {
            // qDebug()<<"evdopPPD";
             evdoPPPD();
             count=0;
             }

        // RSSI
        if ((0 == ((++cnt) % 5)) && (!ciRssi.isEmpty())) {
            rssiValue = getRssi(ciRssi.toLatin1().data());
           // if(simTest()=="READY")
//{

           // qDebug()<<"ready ready ready";
            if (rssiValue >= 0) {
                EvdoRssiLevel rssiLevel;

                if (rssiValue > 31) {
                    rssiLevel = RSSI_INVALID;
                } else if (rssiValue > 12) {
                    rssiLevel = RSSI_GREAT;
                } else if (rssiValue > 8) {
                    rssiLevel = RSSI_GOOD;
                } else if (rssiValue > 5) {
                    rssiLevel = RSSI_MODERATE;
                } else {
                    rssiLevel = RSSI_POOR;
                }

                emit signalRssiLevelUpdate((int)rssiLevel,rssiValue);
            }
      //  }
           /* else
                 emit signalRssiMiss();*/
            }
        xtSDelay(0, 1000 * 1000); // delay 200ms
    }
}

//
void DevEvdo::stopThread()
{
    isThreadToExit = true;
}

void DevEvdo::sendData(QByteArray baData)
{

    rssiSerial.serialWrite(baData);
}


bool DevEvdo::isDialupConnectionEstablished(QString interface)
{
    bool ok = false;

    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();

    foreach (QNetworkInterface tmpIFN, list) {
        DBG_INFO("%s", tmpIFN.name().toLatin1().data());
        if (tmpIFN.name().contains(interface)) {
            ok = true;
            break;
        }
    }

    DBG_INFO("connection already established? %s", ok ? "YES" : "NO");

    return ok;
}

//
void DevEvdo::devInit()
{
    int devIndx = getEvdoCIndex();

    if (devIndx >= 0) {
        ciNetwork = QString("/dev/ttyUSB") + QString::number(devIndx);
        ciRssi = QString("/dev/ttyUSB") + QString::number(devIndx + 1);
    } else {
        ciNetwork.clear();
        ciRssi.clear();
        DBG_ERR("no 3G(EVDO) device found");
    }
}

QString DevEvdo::simTest()
{
    QByteArray babuf;

    for (int i=0; i<3; i++) {
        babuf = "AT+CPIN?\r\n";
        rssiSerial.serialWrite(babuf);

        babuf.clear();
        if ((rssiSerial.serialRead(babuf) == 3) && (babuf.size()>0))
        {
                rssiSerial.serialRead(babuf);
                qDebug()<<"baRBuf=="<<babuf;
                rssiSerial.serialClose();

                    qDebug()<<"size>0";
                    QRegExp rxRssi("CPIN:(.*)");

                    int pos = rxRssi.indexIn(babuf);
                    if(pos>=0)
                        {
                        qDebug()<<"pos>=0";
                        QString str=rxRssi.cap(1);
                        qDebug()<<"str=="<<str;
                        return rxRssi.cap(1);

                    }


        }

        xtSDelay(0, 500*1000);
    }

}





//
int DevEvdo::getRssi(const char *devpath)
{
    fd_set rfds;
    struct timeval tv;
    int retval;

    XtSerialAttr serialAttr;
    serialAttr.devpath = devpath;
    serialAttr.sBaud = BAUD115200;
    serialAttr.sDataBits = DATA_8;
    serialAttr.sParityType = PAR_NONE;
    serialAttr.sStopBits = STOP_1;
    serialAttr.sFlowType = FLOW_OFF;

    rssiSerial.serialOpen(serialAttr);

    //
    QByteArray baWBuf("AT+CSQ\r\n");

    rssiSerial.serialWrite(baWBuf);

    if (rssiSerial.sfd >= 0) {
        FD_ZERO(&rfds);
        FD_SET(rssiSerial.sfd, &rfds);

        tv.tv_sec = 0;
        tv.tv_usec = 500*1000; // 500ms

        retval = select(rssiSerial.sfd + 1, &rfds, NULL, NULL, &tv);

        if (retval > 0) {
            QByteArray baRBuf;

            rssiSerial.serialRead(baRBuf);
            rssiSerial.serialClose();

            ///DBG_INFO("RSSI(%s) #Total %04d Bytes#\n%s", devpath, baRBuf.size(), baRBuf.data());

            // Data Processing
            if (baRBuf.size() > 0) {
                QRegExp rxRssi("CSQ:(.*),(.*)");

                int pos = rxRssi.indexIn(baRBuf);

                if (pos >= 0) {
                    ///DBG_INFO("RSSI: %d", rxRssi.cap(1).toInt());

                    return rxRssi.cap(1).toInt();
                }
            }
            goto ERR_RET;

        } else {
            DBG_ERR("RSSI no response");
            goto ERR_RET;
        }
    } else {
        goto ERR_RET;
    }

ERR_RET:
    if (rssiSerial.sfd >= 0) {
        rssiSerial.serialClose();
    }

    return -1;
}

//
int DevEvdo::getEvdoCIndex()
{
    QDir dirDevEvdo(DEV_CI_EVDO_DIR);

    if (dirDevEvdo.exists()) {
        dirDevEvdo.setFilter(QDir::AllEntries);
        dirDevEvdo.setSorting(QDir::Name);

        QStringList filters;
        filters << "ttyUSB*";

        dirDevEvdo.setNameFilters(filters);

        QFileInfoList fiList = dirDevEvdo.entryInfoList();

        if (fiList.size() > 0) {
            return fiList.at(0).fileName().remove(0, 6).toInt();
        }
    }

    return -1;
}

//
int DevEvdo::evdoPPPD()
{
    int retval;
    int sockfd;
    int addrlen;
    struct sockaddr_un addr;

    //
    genScriptEvdo();

    //
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (-1 == sockfd) {
        DBG_ERR("socket() failed");
        return 1;
    }
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, DIALUP_SOCKET_FILE);
    addrlen = sizeof(addr);

    retval = ::connect(sockfd, (struct sockaddr *)&addr, addrlen);
    if (-1 == retval) {
        DBG_ERR("socket connect() failed");
        return 1;
    }

    retval = ::write(sockfd, "PPPD", 4);

    ///DBG_INFO("socket write %d bytes", retval);

    ::close(sockfd);

    return 0;
}
int DevEvdo::genScriptEvdo()
{
    QFile fileEvdo("/etc/ppp/peers/evdo");

    if (!fileEvdo.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        DBG_ERR("cannot generate script evdo(/etc/ppp/peers/evdo)");
        return -1;
    }

    QTextStream out(&fileEvdo);

    out << "debug\n"
           "nodetach\n"
           "lock\n";
    out << ciNetwork << endl;
    out << "115200\n"
           "user \"ctnet@mycdma.cn\"\n"
           "password \"vnet.mobi\"\n"
           "crtscts\n"
           "show-password\n"
           "usepeerdns\n"
           "noauth\n"
           "noipdefault\n"
           "novj\n"
           "novjccomp\n"
           "noccp\n"
           "defaultroute\n"
           "ipcp-accept-local\n"
           "ipcp-accept-remote\n"
           "connect '/usr/local/bin/chat -s -v -f /etc/ppp/evdo-chat-connect'\n"
           "disconnect '/usr/local/bin/chat -s -v -f /etc/ppp/evdo-chat-disconnect'\n";
    fileEvdo.close();

    return 0;
}

int DevEvdo::getIPCount()
{
    qDebug()<<"get ip count";
    char hname[128];
    struct hostent *hent;
    int i;

    gethostname(hname, sizeof(hname));

    //hent = gethostent();
    hent = gethostbyname(hname);
    if(hent == NULL)
        return -1;
    qDebug()<<"hostname:"<<hent->h_name;
    for(i = 0; hent->h_addr_list[i]; i++) {
        //printf("%s/t", inet_ntoa(*(struct in_addr*)(hent->h_addr_list[i])));
        qDebug()<<"in_addr="<<inet_ntoa(*(struct in_addr*)(hent->h_addr_list[i]));
    }
    return i;
}

int DevEvdo::GetNetCardCount()

 {

     int nCount = 0;

    FILE* f = fopen("/proc/net/dev", "r");

     if (!f)

     {

        fprintf(stderr, "Open /proc/net/dev failed!errno:%d\n", errno);

         return nCount;

     }



     char szLine[512];



     fgets(szLine, sizeof(szLine), f);    /* eat line */

     fgets(szLine, sizeof(szLine), f);



    while(fgets(szLine, sizeof(szLine), f))

    {

       char szName[128] = {0};

       sscanf(szLine, "%s", szName);

        int nLen = strlen(szName);

         if (nLen <= 0)continue;

         if (szName[nLen - 1] == ':') szName[nLen - 1] = 0;

        if (strcmp(szName, "lo") == 0)continue;

        nCount++;

    }



     fclose(f);

    f = NULL;

     return nCount;

 }
