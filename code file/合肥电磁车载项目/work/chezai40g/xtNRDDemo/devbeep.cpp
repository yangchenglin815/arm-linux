#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "devbeep.h"
#include "xtconfig.h"
#include "common.h"
#include <QDebug>

static volatile bool isThreadToExit = false;

DevBeep::DevBeep(QObject *parent) :
    QThread(parent)
{
    bpCount = bplmsec = bprmsec = 0;
}

//
void DevBeep::run()
{
    while (!isThreadToExit) {
        if (bpCount > 0) {
            for (int i=0; ((!isThreadToExit) && (i<bpCount)); i++) {
                setBeepStat(BEEP_ON);
                xtSDelay(0, (bplmsec * 1000));

                setBeepStat(BEEP_OFF);
                xtSDelay(0, (bprmsec * 1000));
            }
            bpCount = 0;
        } else {
            xtSDelay(0, 300*1000); // delay 300ms
        }
    }
}

//
void DevBeep::slotBeepStart(int count, int lmsec, int rmsec)
{
    //qDebug()<<"beep start";
    bplmsec = lmsec;
    bprmsec = rmsec;
    bpCount = count;
}
void DevBeep::slotBeepStop()
{
    setBeepStat(BEEP_OFF);
}

//
int DevBeep::setBeepStat(BeepStat stat)
{
    int fd = open(DEV_FILE_BEEP, O_WRONLY);

    if (-1 == fd) {
        DBG_ERR("beep device open failed: " DEV_FILE_BEEP);
        goto ERR_RET;
    }

    if (BEEP_ON == stat) {
        write(fd, "1", 1);
    } else if (BEEP_OFF == stat) {
        write(fd, "0", 1);
    }
    ::close(fd);

    return 0;
ERR_RET:
    return -1;
}

//
void DevBeep::stopThread()
{
    isThreadToExit = true;
}
