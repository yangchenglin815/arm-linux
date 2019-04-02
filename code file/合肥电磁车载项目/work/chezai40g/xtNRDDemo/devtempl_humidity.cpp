
#include <QStringList>
#include <QRegExp>

#include "devtempl_humidity.h"
#include "xtconfig.h"
#include "common.h"
#include <QDebug>
#include <QFile>

static volatile bool isThreadToExit = false;

DevTempl_Humidity::DevTempl_Humidity(QObject *parent) :
    QThread(parent)
{

    //serialInit();
}

//
void DevTempl_Humidity::run()
{

    QString templ;
    QString humidity;
    while (!isThreadToExit)
    {
       templ=read_Templ();
       //qDebug()<<"read templ";
       humidity=read_Humidity();
      //qDebug()<<"read humidity";
       emit signalTempl_HumidityUpdate(templ, humidity);
      //qDebug()<<"send success";
       xtSDelay(0, 1000*1000);
       //qDebug()<<"time delay";
    }

}

//
void DevTempl_Humidity::stopThread()
{
    isThreadToExit = true;
}


//read templ
QString DevTempl_Humidity::read_Templ()
{
    QFile t("/sys/class/hwmon/hwmon0/device/temp1_input");
    if(!t.open(QIODevice::ReadOnly | QIODevice::Text))
        {
          qDebug()<<"open error";

        }

    //qDebug()<<"t:"<<t.handle();
    //qDebug()<<"*************";
    QTextStream templInput(&t);
    QString tbuf;

    tbuf=templInput.readLine();
  //  qDebug()<<"templ:"<<tbuf;
    //t.flush();
    t.close();
    //qDebug()<<"close";
    return tbuf;
}

//read humidity
QString DevTempl_Humidity::read_Humidity()
{
    QFile h("/sys/class/hwmon/hwmon0/device/humidity1_input");
    if(!h.open(QIODevice::ReadOnly | QIODevice::Text))
        {
        qDebug()<<"open error";

        }
    //qDebug()<<"h:"<<h.handle();
    //qDebug()<<"*************";
    QTextStream humidityInput(&h);
    QString hbuf;

    hbuf=humidityInput.readLine();
   // qDebug()<<"humidity:"<<hbuf;
    //h.flush();
    h.close();
   // qDebug()<<"close";
    return hbuf;

}

//


