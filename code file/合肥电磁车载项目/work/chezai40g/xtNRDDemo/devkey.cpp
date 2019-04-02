#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>

#include <sys/time.h>
#include <sys/select.h>
#include "devkey.h"
static volatile bool isThreadToExit = false;
DevKey::DevKey(QObject *parent) :
    QThread(parent)
{
}
//
void DevKey::stopThread()
{
    isThreadToExit = true;
}

//
void DevKey::run()
{


    int fd = -1;
    struct input_event in;


    fd_set rfds;
    struct timeval tv;

    fd = open("/dev/input/event1", O_RDONLY);
        if (-1 == fd) {
            perror("/dev/input/event1 device open failed");
            exit(EXIT_FAILURE);
        }

    while (!isThreadToExit)
    {
            FD_ZERO(&rfds);
            FD_SET(fd, &rfds);
            tv.tv_sec = 5;
            tv.tv_usec = 0;

            if (select(fd+1, &rfds, NULL, NULL, &tv) > 0) {
                if ((read(fd, &in, sizeof(struct input_event))) \
                        == sizeof(struct input_event)) {
                    if (in.type == EV_KEY) {
                        printf("[D] Time: %ld.%06ld, Code: 0x%x, Value: %d",
                            in.time.tv_sec, in.time.tv_usec, in.code, in.value);
                        if (0x100 == in.code)
                        {
                            if (0 == in.value)
                            {
                                printf(" ---> key: Pressed.\n");
                                //emit signalKeyPress();
                            }

                            else
                                printf(" ---> key: Released.\n");
                        }
                    }
                }
            }
        }
}
