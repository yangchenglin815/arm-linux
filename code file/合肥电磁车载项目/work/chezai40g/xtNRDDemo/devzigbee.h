#ifndef DEVZIGBEE_H
#define DEVZIGBEE_H

#include <QThread>

#include "xtserial.h"

class DevZigbee : public QThread
{
    Q_OBJECT
public:
    explicit DevZigbee(QObject *parent = 0);

    /* FUNCTIONS */
    void stopThread();
    void sendData(QByteArray baData);

signals:
    void signalDataReceived(QByteArray baData);
    //void signalDataSend();
    
protected:
    void run();

private:
    /* FUCHTIONS */
    void serialInit();
    void serialClose();

    /* OBJECTS */
    XtSerial zbSerial;
    
};

#endif // DEVZIGBEE_H
