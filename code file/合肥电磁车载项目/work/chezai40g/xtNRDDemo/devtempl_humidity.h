#ifndef DEVTEMPL_HUMIDITY_H
#define DEVTEMPL_HUMIDITY_H

#include <QThread>

#include "xtserial.h"

class DevTempl_Humidity : public QThread
{
    Q_OBJECT
public:
    explicit DevTempl_Humidity(QObject *parent = 0);

    /* FUNCTIONS */
    void stopThread();

signals:
    void signalTempl_HumidityUpdate(QString templ, QString humidity);

protected:
    void run();

private:
    /* FUCHTIONS */
    QString read_Templ();
    QString read_Humidity();

    /* OBJECTS */
    XtSerial templ_humiditySerial;
};

#endif // DEVTEMPL_HUMIDITY_H
