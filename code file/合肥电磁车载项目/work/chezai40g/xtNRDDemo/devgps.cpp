#include <QStringList>
#include <QRegExp>

#include "devgps.h"
#include "xtconfig.h"
#include "common.h"
#include <QDebug>

static volatile bool isThreadToExit = false;

DevGps::DevGps(QObject *parent) :
    QThread(parent)
{
    serialInit();
}

//
void DevGps::run()
{
    fd_set rfds;
    struct timeval tv;
    int retval;

    while (!isThreadToExit) {
        if (gpsSerial.sfd >= 0) {
            FD_ZERO(&rfds);
            FD_SET(gpsSerial.sfd, &rfds);

            tv.tv_sec = 0;         // delay: 1s + 500ms = 1.5s
            tv.tv_usec = 100*1000;

            retval = select(gpsSerial.sfd+1, &rfds, NULL, NULL, &tv);

            if (retval > 0) {
                QByteArray baRBuf;

                // Data Read
                gpsSerial.serialRead(baRBuf);

                ///DBG_INFO("#Total %04d Bytes#\n%s", baRBuf.size(), baRBuf.data());
                 //qDebug()<<"baRBuf:"<<baRBuf;
                // Data Processing
                if (baRBuf.size() > 0) {
#if defined(CONFIG_GPS_GPRMC)
                    /*
                     * $GPRMC, <1>, <2>, <3>, <4>, <5>, <6>, <7>, <8>, <9>, <10>, <11>, <12>*hh<CR><LF>
                     * <1> UTC时间，hhmmss（时分秒）格式
                     * <2> 定位状态，A=有效定位，V=无效定位
                     * <3> 纬度ddmm.mmmm（度分）格式（前面的0也将被传输）
                     * <4> 纬度半球N（北半球）或S（南半球）
                     * <5> 经度dddmm.mmmm（度分）格式（前面的0也将被传输）
                     * <6> 经度半球E（东经）或W（西经）
                     * <7> 地面速率（000.0~999.9节，前面的0也将被传输）
                     * <8> 地面航向（000.0~359.9度，以真北为参考基准，前面的0也将被传输）
                     * <9> UTC日期，ddmmyy（日月年）格式
                     * <10> 磁偏角（000.0~180.0度，前面的0也将被传输）
                     * <11> 磁偏角方向，E（东）或W（西）
                     * <12> 模式指示（仅NMEA0183 3.00版本输出，A=自主定位，D=差分，E=估算，N=数据无效）
                     */
                    QRegExp rxGPRMC("GPRMC,(\\d*\\.\\d*),(\\w*),(\\d*\\.\\d*),(\\w*),(\\d*\\.\\d*),(.*)");
                     //GPRMC,063535.000,A,3017.3949,N,12004.0217,E,0.00,,210515,,,A*75
                    int pos = rxGPRMC.indexIn(QString(baRBuf));
                    if (pos >= 0) {
                        ///DBG_INFO("[1] >>> %s ___ %s ___ %s <<<", rxGPRMC.cap(2).toLatin1().data(), rxGPRMC.cap(3).toLatin1().data(), rxGPRMC.cap(5).toLatin1().data());
                        if (rxGPRMC.cap(2) == "A") {
                            QString strLongitude = rxGPRMC.cap(5);
                          //  strLongitude.remove('.').insert(3, '.');

                            QString strLatitude=rxGPRMC.cap(3);
                          //  strLatitude.remove('.').insert(2, '.');
                            /*
                            QString strLongitude = rxGPRMC.cap(5) + rxGPRMC.cap(6);
                            strLongitude.remove('.').insert(3, '.');

                            QString strLatitude(rxGPRMC.cap(3) + rxGPRMC.cap(4));
                            strLatitude.remove('.').insert(2, '.');
                            */
                            ///DBG_INFO("[2] >>> %s ___ %s<<<", strLongitude.toLatin1().data(), strLatitude.toLatin1().data());
                            emit signalGpsInfoUpdate(strLongitude, strLatitude);

                        } else if (rxGPRMC.cap(2) == "V") {
                            // do something
                        }
                    }
#elif defined(CONFIG_GPS_GPGGA)
                    /*
                     * $GPGGA,<1>,<2>,<3>,<4>,<5>,<6>,<7>,<8>,<9>,M,<10>,M,<11>,<12>*xx<CR><LF>
                     * $GPGGA：起始引导符及语句格式说明(本句为GPS定位数据)；
                     * <1> UTC时间，格式为hhmmss.sss；
                     * <2> 纬度，格式为ddmm.mmmm(第一位是零也将传送)；
                     * <3> 纬度半球，N或S(北纬或南纬)
                     * <4> 经度，格式为dddmm.mmmm(第一位零也将传送)；
                     * <5> 经度半球，E或W(东经或西经)
                     * <6> GPS状态， 0初始化， 1单点定位， 2码差分， 3无效PPS， 4固定解， 5浮点解， 6正在估算 7，人工输入固定值， 8模拟模式， 9WAAS查分
                     * <7> 使用卫星数量，从00到12(第一个零也将传送)
                     * <8> 水平精度因子，0.5到99.9
                     * <9> 天线离海平面的高度，-9999.9到9999.9米
                     * M 指单位米
                     * <10> 大地水准面高度，-9999.9到9999.9米
                     * M 指单位米
                     * <11> 差分GPS数据期限(RTCM SC-104)，最后设立RTCM传送的秒数量，如不是差分定位则为空
                     * <12> 差分参考基站标号，从0000到1023(首位0也将传送)。
                     * 语句结束标志符
                     * xx 从$开始到*之间的所有ASCII码的异或校验和
                     * <CR> 回车
                     * <LF> 换行
                     */
                    QRegExp rxGPGGA("GPGGA,(.*),(.*),(.*),(.*),(.*),(.*),(.*),(.*),(.*),(.*),(.*),(.*),,(.*)(.*)");
                    //GPGGA,063535.000,3017.3949,N,12004.0217,E,1,05,4.2,-1.2,M,7.0,M,,0000*41

                    int pos = rxGPGGA.indexIn(QString(baRBuf));
                    if (pos >= 0) {
                        ///DBG_INFO("[1] >>> Sat-NUM: %s, STAT: %s <<<", rxGPGGA.cap(7).toLatin1().data(), rxGPGGA.cap(6).toLatin1().data());
                        if (rxGPGGA.cap(6) == "1" || rxGPGGA.cap(6) == "2") {
                            QString strLongitude = rxGPGGA.cap(4) + rxGPGGA.cap(5);
                            strLongitude.remove('.').insert(3, '.');

                            QString strLatitude(rxGPGGA.cap(2) + rxGPGGA.cap(3));
                            strLatitude.remove('.').insert(2, '.');

                            ///DBG_INFO("[2] >>> Longitude: %s, Latitude: %s <<<", strLongitude.toLatin1().data(), strLatitude.toLatin1().data());
                            emit signalGpsInfoUpdate(strLongitude, strLatitude);

                        } else if (rxGPGGA.cap(6) == "0") {
                            // do something

                        }
                    }
#endif
                }
            }
        } else {
            xtSDelay(0, 100*1000);
        }
    }
}

//
void DevGps::stopThread()
{
    isThreadToExit = true;
}

//
void DevGps::serialInit()
{
    XtSerialAttr serialAttr;
    serialAttr.devpath = DEV_CI_GPS;
    serialAttr.sBaud = BAUD9600;
    serialAttr.sDataBits = DATA_8;
    serialAttr.sParityType = PAR_NONE;
    serialAttr.sStopBits = STOP_1;
    serialAttr.sFlowType = FLOW_OFF;

    gpsSerial.serialOpen(serialAttr);
}

void DevGps::serialClose()
{
    gpsSerial.serialClose();
}
