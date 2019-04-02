#include <QRegExp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/types.h>
#include <linux/netlink.h>
#include <unistd.h>
#include <errno.h>

#include "devusbserialmonitor.h"
#include "common.h"

#define M_BUF_SZ 4096

static volatile bool isThreadToExit = false;

DevUsbSerialMonitor::DevUsbSerialMonitor(QObject *parent) :
    QThread(parent)
{
}

void DevUsbSerialMonitor::run()
{
    struct sockaddr_nl snl;
    const int bufsz = 4 * 1024 * 1024;
    int ret;
    char rbuf[M_BUF_SZ] = {0};

    memset(&snl, 0, sizeof(struct sockaddr_nl));

    snl.nl_family = AF_NETLINK;
    snl.nl_pid = getpid();
    snl.nl_groups = 1;

    int hotplug_sock = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
    if (-1 == hotplug_sock) {
        DBG_ERR("socket(): %s", strerror(errno));
        return;
    }
    setsockopt(hotplug_sock, SOL_SOCKET, SO_RCVBUFFORCE, &bufsz, sizeof(bufsz));
    ret = bind(hotplug_sock, (struct sockaddr *)&snl, sizeof(struct sockaddr_nl));
    if (ret < 0) {
        DBG_ERR("bind(): %s\n", strerror(errno));
        close(hotplug_sock);
        hotplug_sock = -1;
        return;
    }

    /* Example:
     * add@/devices/ahb.0/600000.ohci/usb2/2-2/2-2:1.0/ttyUSB0/tty/ttyUSB0
     * remove@/devices/ahb.0/600000.ohci/usb2/2-2/2-2:1.0/ttyUSB0
     */
    QRegExp rxAttached("add@/devices/(.*)/(.*)/(.*)/(.*)/(.*)/(ttyUSB\\d+)/(.*)/(.*)");
    QRegExp rxDisconnect("remove@/devices/(.*)/(.*)/(.*)/(.*)/(.*)/(ttyUSB\\d+)/(.*)");

    while (!isThreadToExit) {
        memset(rbuf, 0, M_BUF_SZ);
        int ret = recv(hotplug_sock, &rbuf, M_BUF_SZ, 0);
        if (ret > 0) {
            QString strTemp(rbuf);

            ///DBG_INFO("#Total %04d Bytes#\n%s", strTemp.size(), strTemp.toLatin1().data());

            int pos;
            pos = rxAttached.indexIn(strTemp);
            if (pos > -1) {
                xtSDelay(0, 100*1000);
                emit signalDeviceAttached(rxAttached.cap(6));
                continue;
            }
            pos = rxDisconnect.indexIn(strTemp);
            if (pos > -1) {
                emit signalDeviceDisconnected(rxDisconnect.cap(6));
                continue;
            }
        }
    }
}

//
void DevUsbSerialMonitor::stopThread()
{
    isThreadToExit = true;
}
