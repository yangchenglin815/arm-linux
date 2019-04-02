#ifndef DEVBATTERY_H
#define DEVBATTERY_H

#include <QThread>

enum BatteryLevel {
};

class DevBattery : public QThread
{
    Q_OBJECT
public:
    explicit DevBattery(QObject *parent = 0);

    /* FUCHTIONS */
    void stopThread();
    
signals:
    void signalBatteryUpdate(int pct);
    void signalChargerConnected(bool stat);
    void signalLowBatteryShutdown();
    void signalLowBatteryDetected(bool stat);

protected:
    void run();
    
private:
    /* FUCHTIONS */
    int getAdcSample(const char *devpath);

    /* OBJECTS */

};

#endif // DEVBATTERY_H
