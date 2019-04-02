#ifndef DEVEVDO_H
#define DEVEVDO_H

#include <QThread>
#include "xtserial.h"

enum EvdoRssiLevel {
    RSSI_INVALID,
    RSSI_GREAT,
    RSSI_GOOD,
    RSSI_MODERATE,
    RSSI_POOR
};

class DevEvdo : public QThread
{
    Q_OBJECT
public:
    explicit DevEvdo(QObject *parent = 0);

    /* FUNCTIONS */
    void stopThread();
    void sendData(QByteArray baData);
    int getIPCount();
    int GetNetCardCount();
    
signals:
    void signalRssiLevelUpdate(int level,int value);
    void signalRssiMiss();
    
public slots:

protected:
    void run();

private:
    /* FUCHTIONS */
    void devInit();
    int getRssi(const char *devpath);
    int getEvdoCIndex();
    bool isDialupConnectionEstablished(QString interface);
    QString simTest();
    int evdoPPPD();
    int genScriptEvdo();

    /* OBJECTS */
    XtSerial rssiSerial;  // RSSI

    QString ciNetwork;
    QString ciRssi;
};

#endif // DEVEVDO_H
