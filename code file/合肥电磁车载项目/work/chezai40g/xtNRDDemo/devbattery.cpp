#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "devbattery.h"
#include "xtconfig.h"
#include "common.h"

#define ADC_RBUF_SIZE 16

#define ADC_SAMPLE_MAX 2455  // about 4.1V
#define ADC_SAMPLE_MIN 2120  // about 3.5V
#define LOW_BATTERY_THRESHOLD 2130
#define LOW_BATTERY_SHUTDOWN_THRESHOLD 2090 // about 3.4V

static volatile bool isThreadToExit = false;

DevBattery::DevBattery(QObject *parent) :
    QThread(parent)
{
}

//
void DevBattery::run()
{
    unsigned int cnt = 0;
    bool volatile isChargerConnected = false;

    bool volatile isBatteryLow = false;

    int lowBatteryCount = 0;
    int emptyBatteryCount = 0;

    while (!isThreadToExit) {
        // Charger Detection, Interval: cnt * 200ms = 5*200 = 1s
        if (0 == (cnt % 5)) {
            int adcVal = getAdcSample(DEV_FILE_ADC_CHARGER);

            // Data Processing
            if (adcVal >= 0) {
                if (adcVal >= 300) {
                    if (!isChargerConnected) {
                        emit signalChargerConnected(true);
                    }

                    isChargerConnected = true;

                } else {
                    if (isChargerConnected) {
                        emit signalChargerConnected(false);
                        isBatteryLow = false;
                    }

                    isChargerConnected = false;
                }
            }
        }

        // Battery, Interval: cnt * 200ms = 25*200 = 5s
        if (0 == (cnt % 25)) {
            int adcVal = getAdcSample(DEV_FILE_ADC_BATTERY);

            // Data Processing
            if (adcVal >= 0) {
                /* ADC MAX: ADC_SAMPLE_MAX, MIN: ADC_SAMPLE_MIN
                 * PCT = 100 * (Rr - ADC_SAMPLE_MIN) / (ADC_SAMPLE_MAX - ADC_SAMPLE_MIN)
                 * Rr: ADC Sample Value, PCT Range: 0-100
                 */
                int pct = 0;

                if (adcVal <= ADC_SAMPLE_MIN) {
                    pct = 0;
                } else if (adcVal >= ADC_SAMPLE_MAX) {
                    pct = 100;
                } else {
                    pct = (int)(100.0 * (adcVal - ADC_SAMPLE_MIN) / (ADC_SAMPLE_MAX - ADC_SAMPLE_MIN));
                }

                ///DBG_INFO("#%06d# ADC: %4d, Vol: %1.2f, PCT: %3d", cnt, adcVal, (3.3*adcVal/4096), pct);
                emit signalBatteryUpdate(pct);

                // Low Battery
                if (adcVal < LOW_BATTERY_THRESHOLD) {
                    lowBatteryCount = 0;
                    if ((!isBatteryLow) && (!isChargerConnected)) {
                        isBatteryLow = true;
                        emit signalLowBatteryDetected(true);
                    }
                } else {
                    // 12 * 25s = 300s
                    if (isBatteryLow && (++lowBatteryCount >= 12)) {
                        isBatteryLow = false;
                        lowBatteryCount = 0;
                        emit signalLowBatteryDetected(false);
                    }
                }
                // Empty Battery
                if (adcVal < LOW_BATTERY_SHUTDOWN_THRESHOLD && !isChargerConnected) {
                    // 12 * 25s = 300s
                    if (++emptyBatteryCount >= 12) {
                        emptyBatteryCount = 0;
                        emit signalLowBatteryShutdown();
                    }
                } else {
                    emptyBatteryCount = 0;
                }
            }
        }

        //
        ++cnt;

        // Delay 200ms
        xtSDelay(0, 200*1000);
    }
}

//
void DevBattery::stopThread()
{
    isThreadToExit = true;
}

//
int DevBattery::getAdcSample(const char *devpath)
{
    int fd = open(devpath, O_RDONLY);
    int retval;
    char rbuf[ADC_RBUF_SIZE];

    if (-1 == fd) {
        DBG_ERR("device open failed(%s)", devpath);
        return -1;
    }

    retval = read(fd, rbuf, ADC_RBUF_SIZE-1);
    ::close(fd);

    // Data Processing
    if (retval > 0) {
        rbuf[retval] = '\0';

        return atoi(rbuf);
    }

    return -1;
}
