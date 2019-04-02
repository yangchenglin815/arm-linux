#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <QString>
/* DEBUG */
#define DBG_ERR(fmt, args...) \
    printf("[ERR] %s, %s(%d): " fmt "\n", __FILE__,__FUNCTION__,__LINE__, ##args)
#define DBG_INFO(fmt, args...) \
    printf("[DBG] %s, %s(%d): " fmt "\n", __FILE__,__FUNCTION__,__LINE__, ##args)

/*  */
int xtSDelay(long nsec, long nusec);
void LogMesg(QString log);
#endif // COMMON_H
