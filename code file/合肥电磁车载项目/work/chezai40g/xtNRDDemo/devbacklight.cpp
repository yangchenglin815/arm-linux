#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "devbacklight.h"
#include "xtconfig.h"
#include "common.h"

DevBacklight::DevBacklight(QObject *parent) :
    QObject(parent)
{
    if (0 == getBlBrightness()) {
        setBlBrightness(200);
    }
    isBacklightON = true;
}

//
void DevBacklight::slotKeepTimeUpdate(int type)
{
    ///static int cnt = 0;
    ///DBG_INFO("SCREEN Keep Time, %03d, %3d, %d", (++cnt), blKeepTime, type);
    //return ;
    if (type == BLKT_RESON_TIMEOUT) {
        if (isBacklightON && ((++blKeepTime) > ((SCREEN_KEEP_TIME) * 60))) {
            setBlBrightness(0);
            isBacklightON = false;
        }
    } else if (type == BLKT_RESON_MOUSEVENT) {
        blKeepTime = 0;

        if (!isBacklightON) {
            setBlBrightness(200);
            isBacklightON = true;
        }
    }
}

//
void DevBacklight::setBlBrightness(int value)
{
    char wbuf[4] = {0, 0, 0, 0};
    int fd = open(DEV_FILE_BACKLIGHT, O_WRONLY);

    if (value > 255 || value < 0) {
        DBG_ERR("screen backlight: invalid brightness %d", value);
        return;
    }

    if (-1 == fd) {
        DBG_ERR("screen backlight: device open failed" DEV_FILE_BACKLIGHT);
        return;
    }

    snprintf(wbuf, 4, "%d", value);
    write(fd, wbuf, strlen(wbuf));

    ::close(fd);
}
int DevBacklight::getBlBrightness()
{
    char rbuf[4];
    int retval;

    int fd = open(DEV_FILE_BACKLIGHT, O_RDONLY);

    if (-1 == fd) {
        DBG_ERR("screen backlight: device open failed" DEV_FILE_BACKLIGHT);
        return -1;
    }

    retval = read(fd, rbuf, 3);
    ::close(fd);

    if (retval > 0) {
        rbuf[retval] = '\0';
        return atoi(rbuf);

    } else {
        return -1;
    }
}

//
bool DevBacklight::getBacklightStat()
{
    return isBacklightON;
}
