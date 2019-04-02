#ifndef DEVGPS_H
#define DEVGPS_H

#include <QThread>

#include "xtserial.h"

class DevGps : public QThread
{
    Q_OBJECT
public:
    explicit DevGps(QObject *parent = 0);

    /* FUNCTIONS */
    void stopThread();
    
signals:
    void signalGpsInfoUpdate(QString strLongitude, QString strLatitude);

protected:
    void run();

private:
    /* FUCHTIONS */
    void serialInit();
    void serialClose();

    /* OBJECTS */
    XtSerial gpsSerial;
};

#endif // DEVGPS_H
