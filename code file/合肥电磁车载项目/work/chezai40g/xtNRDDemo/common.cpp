#include <sys/select.h>
#include "common.h"
#include "xtconfig.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QThread>
#include <QSettings>
#include <QDebug>
//
int xtSDelay(long nsec, long nusec)
{
    struct timeval tv;

    tv.tv_sec = nsec;
    tv.tv_usec = nusec;

    return (select(0, NULL, NULL, NULL, &tv));
}

void LogMesg(QString log)
{


    if(config.logflag==0)
        return ;
    QFile file("/home/root/log.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        return;
    }
    // qDebug()<<log;
    //sprintf(strmsg,"%08x",pthread_self());
    QTextStream tsOutput(&file);
    QString strTimeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    tsOutput << "["<<QThread::currentThread()->currentThreadId()<<+"]"<<strTimeStamp + " " + log + "\n";
    file.flush();
    file.close();

}
XtConfig::XtConfig()
{
    QSettings settings("config.ini", QSettings::IniFormat);

    termnumber  = settings.value("sys/termnumber").toString();
    pwd         = settings.value("sys/pwd").toString();
    ip          = settings.value("sys/ip").toString();
    port        = settings.value("sys/port").toInt();
    speed       =  settings.value("sys/speed").toInt();
    logflag     =  settings.value("sys/logflag").toInt();
    workway  = settings.value("sys/workway").toString();
    vnumber  = settings.value("sys/vnumber").toString();
    tasktotal = settings.value("sys/tasktotal").toInt();
    version = settings.value("sys/version").toInt();
    LogMesg("termnumber :" + termnumber);
    LogMesg("pwd        :" + pwd);

    LogMesg("ip         :" + ip);
    LogMesg("port       :" + QString::number(port));
    LogMesg("speed      :" + QString::number(speed));
    LogMesg("logflag    :" + QString::number(logflag));
    LogMesg("workway    :" + workway);
    LogMesg("vnumber    :" + vnumber);
    LogMesg("tasktotal  :" + QString::number(tasktotal));
    LogMesg("version    :" + QString::number(version));
}
XtConfig config;
