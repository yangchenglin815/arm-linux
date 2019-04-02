#include <QStringList>
#include <QRegExp>
#include <QDir>

#include "devradiationdetector.h"
#include "xtconfig.h"
#include "common.h"
#include <QDebug>
#include <QRegExp>
#include <qmath.h>

static volatile bool isThreadToExit = false;

DevRadiationDetector::DevRadiationDetector(QObject *parent) :
    QThread(parent)
{
#if defined(CONFIG_RDA_USE_NARDA)
    getFt232CI(baSerialPath);

    isRemoteConnected = false;
#else
    getFt232CI(baSerialPath);
    serialInit();
#endif
}
//
void DevRadiationDetector::run()
{
    fd_set rfds;
    struct timeval tv;
    int retval;

#if defined(CONFIG_RDA_USE_FH40G)

/* FH40G协议.pdf
 * Unit=
 * 0: uSv/h   1: uGy/h   2: uR/h  3: cpm
 * when connecting an external alpha/beta detector
 * 4: 1/s   5: cps  6: calibrated probe for contamination, unit e.g. BQ/CM2
 */
QStringList slRRxUnit;
slRRxUnit << "uSv/h" << "uGy/h" << "uR/h" << "cpm" << "1/s" << "cps";

/* FH40G协议.pdf
 * Rx Status=
 * 01: undefined
 * 02: Display range exceeded
 * 04: Dose rate alarm
 * 08: Doserate alarm / external probe
 * 10: Artificial radiation(external probe FHT627)
 */
QStringList slRRxStatus;
slRRxStatus << "undefined" << "Display range exceeded" << "Dose rate alarm" \
          << "Doserate alarm / external probe" << "Artificial radiation(external probe FHT627)";


#elif defined(CONFIG_RDA_USE_LB124)

#elif defined(CONFIG_RDA_USE_NARDA)

#endif

    while (!isThreadToExit) {
        if (rdSerial.sfd >= 0) {
#if defined(CONFIG_RDA_USE_NARDA)
            if (!isRemoteConnected) {
                if (startRemoteConnection()) {
                    DBG_ERR("remote connection failed.");
                    xtSDelay(0, 500*1000);
                    continue;
                }
                isRemoteConnected = true;
            }
#endif


            FD_ZERO(&rfds);
            FD_SET(rdSerial.sfd, &rfds);

            tv.tv_sec = 0;
            tv.tv_usec = 200*1000; // 200ms

            retval = select(rdSerial.sfd+1, &rfds, NULL, NULL, &tv);

            if (retval > 0) {
                QByteArray baRBuf;

                // Data Read
                rdSerial.serialRead(baRBuf);
               // qDebug()<<"size="<<baRBuf.size();
                //qDebug()<<"baRBuf="<<baRBuf;

                //DBG_INFO("#Total %04d Bytes#\n%s", baRBuf.size(), baRBuf.data());

                // Data Processing
#if defined(CONFIG_RDA_USE_FH40G)
                QString strRData;
                QString strNbr;
                float rdValue;
                baRBuf.replace("  "," ");
                baRBuf.trimmed();
                QRegExp rxRData("#(.*)E(.)(.*) (.) (.*)E(.)(.*) (.) (.*)");

                  //@@#0.1729E+0 0 0.1558E+0 0 00
                int pos = rxRData.indexIn(baRBuf);

                if (pos >= 0) {

                    rdValue = 0;
                    strNbr = rxRData.cap(9);
                    strNbr.truncate(2);
                    emit signalNbrUpdate(strNbr);
                   // qDebug()<<"emit nbr";
                    if(rxRData.cap(6)=="+")
                    {
                       // qDebug()<<"exit tantou";
                        rdValue = (float)(rxRData.cap(5).toDouble() * qPow(10, rxRData.cap(7).toInt()) * 1000);
                    }
                    else
                    {
                       /* qDebug()<<rxRData.cap(5);
                        qDebug()<<rxRData.cap(7);
                        qDebug()<<rxRData.cap(8);
                        qDebug()<<rxRData.cap(9);
                        qDebug()<<qPow(10, rxRData.cap(7).toInt());*/
                        rdValue = (float)(rxRData.cap(5).toDouble() / qPow(10, rxRData.cap(7).toInt()) * 1000);
                    }
                    QString strRData;
                   // qDebug()<<"rdValue="<<rdValue;
                    if(int(rdValue)> 0)
                    {
                        if(int(rdValue)>=100)
                        {
                            strRData =QString::number(int(rdValue));
                            // QString strTemp1(QString::number(int(iMeasuredValue)));
                            // qDebug()<<">100  "<<strTemp1;
                           // iMeasuredValue = atoi(iMeasuredValue);
                        }
                        else
                        {
                             strRData =QString::number(rdValue);

                             int b = strRData.indexOf(".");
                             if(b>=0)
                                 strRData = strRData.left(b+2);

                        }
                    }
                    else
                    {
                        if(rxRData.cap(2)=="+")
                        {
                            //qDebug()<<"in tantou";
                            rdValue = (float)(rxRData.cap(1).toDouble() * qPow(10, rxRData.cap(3).toInt()) * 1000);
                        }
                        else
                        {
                            rdValue = (float)(rxRData.cap(1).toDouble() / qPow(10, rxRData.cap(3).toInt()) * 1000);
                        }
                       // qDebug()<<"rdValue1="<<rdValue;
                        if(int(rdValue)>=100)
                        {
                            strRData =QString::number(int(rdValue));
                            // QString strTemp1(QString::number(int(iMeasuredValue)));
                            // qDebug()<<">100  "<<strTemp1;
                           // iMeasuredValue = atoi(iMeasuredValue);
                        }
                        else
                        {
                             strRData =QString::number(rdValue);
                           //  QString strTemp1(QString::number(iMeasuredValue));
                             int b = strRData.indexOf(".");
                             if(b>=0)
                                 strRData = strRData.left(b+2);
                            // qDebug()<<"<100  "<<strTemp1;
                           //   iMeasuredValue = atof(iMeasuredValue);
                        }
                    }

                    /*
                    if ((rdValue < 1.0) && (rxRData.cap(2).trimmed() == "0")) {
                        rdValue *= 1000;
                        strRData = QString::number(rdValue, 'f', 0);
                    }
                    */

                    /*
                    if ((rdValue < 1.0) && (rxRData.cap(2).trimmed() == "0")) {
                        rdValue *= 1000;
                        strRData = QString::number(rdValue, 'f', 0) + " nSv/h";
                    }
                    else
                    {
                        strRData = QString::number(rdValue, 'f', 4) + " " + slRRxUnit.at(rxRData.cap(2).toInt());
                    }
                    */

                    //
                    emit signalRadiationUpdate(strRData);

                }
                 else
                    emit signalRadiationUpdate(strRData);


#elif defined(CONFIG_RDA_USE_LB124)
                //

#elif defined(CONFIG_RDA_USE_NARDA)
                //

               // QString b = "6.303E-01, 6.303E-01, 1.032E+00, 6.204E-01, 0.0";

                QString strRData;

                float rdValue;
                QRegExp rxRData("(.*)E(.)(.*),(.*)E(.)(.*),(.*),(.*),(.*)");

               // 3.253E+00, 3.253E+00, 0.0, 0.0, 0.0;
                QStringList slRRxUnit;
                int pos = rxRData.indexIn(baRBuf);


                if (pos >= 0)
                {
                    //qDebug()<<"cap1="<<rxRData.cap(1);
                    //qDebug()<<"cap2="<<rxRData.cap(2);
                    //qDebug()<<"cap3="<<rxRData.cap(3);
                    strRData = QString::number(getRealValue(rxRData.cap(1),rxRData.cap(2),rxRData.cap(3)), 'f', 2);
                    //qDebug()<<"strRData:"<<strRData;
                    // strRData = QString::number(getRealValue(rxRData.cap(1),rxRData.cap(2),rxRData.cap(3)), 'f', 2) + " V/m";
                }
               // qDebug()<<"strRData:"<<strRData;
                 emit signalRadiationUpdate(strRData);
#endif
            }
        } else {
#if defined(CONFIG_RDA_USE_NARDA)
            if (!baSerialPath.isEmpty()) {
                ///DBG_INFO("FT232 SERIAL OPEN");
                serialInit();
            }
#endif
            if(!baSerialPath.isEmpty())
            {
                serialInit();
            }
            xtSDelay(0, 100*1000);
        }
    }
}

/*float DevRadiationDetector::getRealValue(QString a, QString b, QString c)
{
    int t = 1;
    if(b=="-")
    {

        if(c.toInt()!=0)
             t = 10*c.toInt();
        return a.toFloat() / t;

    }
    else
    {
        if(c.toInt()!=0)
             t = 10*c.toInt();
        return a.toFloat() * t;
    }
    return 0.0;
}*/

//
void DevRadiationDetector::serialInit()
{
   // qDebug()<<"serial init";
#if defined(CONFIG_RDA_USE_FH40G)
    XtSerialAttr serialAttr;
    serialAttr.devpath = baSerialPath;
   // serialAttr.devpath = DEV_CI_DB9;
    serialAttr.sBaud = BAUD9600;
    serialAttr.sDataBits = DATA_7;
    serialAttr.sParityType = PAR_EVEN;
    serialAttr.sStopBits = STOP_2;
    serialAttr.sFlowType = FLOW_HARDWARE;
   // serialAttr.

    rdSerial.serialOpen(serialAttr);

#elif defined(CONFIG_RDA_USE_LB124)
    XtSerialAttr serialAttr;
    serialAttr.devpath = DEV_CI_DB9;
    serialAttr.sBaud = BAUD19200;
    serialAttr.sDataBits = DATA_8;
    serialAttr.sParityType = PAR_NONE;
    serialAttr.sStopBits = STOP_1;
    serialAttr.sFlowType = FLOW_OFF;

    rdSerial.serialOpen(serialAttr);

#elif defined(CONFIG_RDA_USE_NARDA)
    XtSerialAttr serialAttr;
    serialAttr.devpath = baSerialPath;   //
    serialAttr.sBaud = BAUD460800;
    serialAttr.sDataBits = DATA_8;
    serialAttr.sParityType = PAR_NONE;
    serialAttr.sStopBits = STOP_1;
    serialAttr.sFlowType = FLOW_OFF;

    rdSerial.serialOpen(serialAttr);

#endif
}
void DevRadiationDetector::serialClose()
{
    rdSerial.serialClose();
}

void DevRadiationDetector::getFt232CI(QByteArray &baPath)
{
    QDir dirFt232(DEV_CI_FT232_DIR);
    dirFt232.setFilter(QDir::AllEntries);
    dirFt232.setSorting(QDir::Name);
   // qDebug()<<"path="<<dirFt232.currentPath();
    QStringList filters;
    filters << "ttyUSB*";

    dirFt232.setNameFilters(filters);

    QFileInfoList fiList = dirFt232.entryInfoList();
   // qDebug()<<"size="<<fiList.size();
    if (fiList.size() > 0) {

        baPath = QByteArray("/dev/") + fiList.at(0).fileName().toLatin1();
       // qDebug()<<"devbath="<<baPath;
    } else {
        baPath.clear();
    }
}

void DevRadiationDetector::slotDeviceAttached(QString devName)
{
    if (rdSerial.sfd < 0) {
        baSerialPath = QByteArray("/dev/")  + devName.toLatin1();
        ///DBG_INFO("Attach %s", devName.toLatin1().data());
    }
}

void DevRadiationDetector::slotDeviceDisconnected(QString devName)
{
    if ((rdSerial.sfd >= 0) && (baSerialPath == (QString("/dev/") + devName).toLatin1())) {
        baSerialPath.clear();
        rdSerial.serialClose();
        ///DBG_INFO("Remove %s", devName.toLatin1().data());
    }
}

//
void DevRadiationDetector::reqRadiationData()
{

#if defined(CONFIG_RDA_USE_FH40G)
    QByteArray baReq("@");
   // qDebug()<<baReq;
    rdSerial.serialWrite(baReq);
    baReq.clear();

    xtSDelay(0, 8*1000); // delay 8ms

    baReq.append("Rx\r\n");
   // qDebug()<<baReq;
    rdSerial.serialWrite(baReq);

#elif defined(CONFIG_RDA_USE_LB124)

#elif defined(CONFIG_RDA_USE_NARDA)
    QByteArray baReq("MEAS?;");
    //qDebug()<<"mEAS";
    if (isRemoteConnected) {
        rdSerial.serialWrite(baReq);
    }
#endif
}

//
void DevRadiationDetector::stopThread()
{
    isThreadToExit = true;
}

#if defined(CONFIG_RDA_USE_NARDA)
void DevRadiationDetector::slotDeviceAttached(QString devName)
{
    if (rdSerial.sfd < 0) {
        baSerialPath = QByteArray("/dev/")  + devName.toLatin1();
        ///DBG_INFO("Attach %s", devName.toLatin1().data());
    }
}

void DevRadiationDetector::slotDeviceDisconnected(QString devName)
{
    if ((rdSerial.sfd >= 0) && (baSerialPath == (QString("/dev/") + devName).toLatin1())) {
        baSerialPath.clear();
        rdSerial.serialClose();
        ///DBG_INFO("Remove %s", devName.toLatin1().data());
    }
}

int DevRadiationDetector::startRemoteConnection()
{
    QByteArray babuf;

    for (int i=0; i<3; i++) {
        babuf = "REMOTE ON;";
        rdSerial.serialWrite(babuf);

        babuf.clear();
        if ((rdSerial.serialRead(babuf) == 3) && (babuf == QByteArray("0;\r"))) {
            DBG_INFO("remote connection: OK");
            return 0;
        }

        DBG_ERR("remote connection failed, try again...");
        xtSDelay(0, 500*1000);
    }

    return -1;
}

void DevRadiationDetector::getFt232CI(QByteArray &baPath)
{
    QDir dirFt232(DEV_CI_FT232_DIR);
    dirFt232.setFilter(QDir::AllEntries);
    dirFt232.setSorting(QDir::Name);

    QStringList filters;
    filters << "ttyUSB*";

    dirFt232.setNameFilters(filters);

    QFileInfoList fiList = dirFt232.entryInfoList();

    if (fiList.size() > 0) {
        baPath = QByteArray("/dev/") + fiList.at(0).fileName().toLatin1();
    } else {
        baPath.clear();
    }
}

#endif
