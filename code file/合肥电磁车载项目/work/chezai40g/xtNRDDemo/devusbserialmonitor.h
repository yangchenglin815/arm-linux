#ifndef DEVUSBSERIALMONITOR_H
#define DEVUSBSERIALMONITOR_H

#include <QThread>

class DevUsbSerialMonitor : public QThread
{
    Q_OBJECT
public:
    explicit DevUsbSerialMonitor(QObject *parent = 0);

    /* FUNCTIONS */
    void stopThread();
    
signals:
    void signalDeviceAttached(QString devName);
    void signalDeviceDisconnected(QString devName);
    
public slots:

protected:
    void run();

    
};

#endif // DEVUSBSERIALMONITOR_H
