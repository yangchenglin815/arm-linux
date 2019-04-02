#include "devzigbee.h"
#include "xtconfig.h"
#include "common.h"
#include <QDebug>

static volatile bool isThreadToExit = false;

DevZigbee::DevZigbee(QObject *parent) :
    QThread(parent)
{
    serialInit();
}

//
void DevZigbee::run()
{
    fd_set rfds;
    struct timeval tv;
    int retval;

    while (!isThreadToExit) {
        if (zbSerial.sfd >= 0) {
            FD_ZERO(&rfds);
            FD_SET(zbSerial.sfd, &rfds);

            tv.tv_sec = 1;         // delay: 1s + 500ms = 1.5s
            tv.tv_usec = 500*1000;

            retval = select(zbSerial.sfd+1, &rfds, NULL, NULL, &tv);
            // Data Send
           // emit signalDataSend();
            //qDebug()<<"send data";
            if (retval > 0) {
                QByteArray baRBuf;

                // Data Read
                zbSerial.serialRead(baRBuf);

               // DBG_INFO("#Total %04d Bytes#\n%s", baRBuf.size(), baRBuf.data());

                // Data Processing
                if (baRBuf.size() > 0) {
                    emit signalDataReceived(baRBuf);
                }
            }
        } else {
            xtSDelay(0, 100 * 1000); // delay 100ms
        }
    }
}

//
void DevZigbee::stopThread()
{
    isThreadToExit = true;
}

//
void DevZigbee::sendData(QByteArray baData)
{

    zbSerial.serialWrite(baData);
    //qDebug()<<"baData:"<<baData;
}

//
void DevZigbee::serialInit()
{
    XtSerialAttr serialAttr;
    serialAttr.devpath = DEV_CI_ZIGBEE;
    serialAttr.sBaud = BAUD115200;
    serialAttr.sDataBits = DATA_8;
    serialAttr.sParityType = PAR_NONE;
    serialAttr.sStopBits = STOP_1;
    serialAttr.sFlowType = FLOW_OFF;

    zbSerial.serialOpen(serialAttr);
}

void DevZigbee::serialClose()
{
    zbSerial.serialClose();
}
