#ifndef DEVRADIATIONDETECTOR_H
#define DEVRADIATIONDETECTOR_H

#include <QThread>

#include "xtserial.h"
#include "xtconfig.h"

class DevRadiationDetector : public QThread
{
    Q_OBJECT
public:
    explicit DevRadiationDetector(QObject *parent = 0);

    /* FUNCTIONS */
    void reqRadiationData();
    void stopThread();

signals:
    void signalRadiationUpdate(QString strData);
    void signalNbrUpdate(QString strNbr);
    
public slots:

#if defined(CONFIG_RDA_USE_NARDA)
    void slotDeviceAttached(QString devName);
    void slotDeviceDisconnected(QString devName);
#endif
    void slotDeviceAttached(QString devName);
    void slotDeviceDisconnected(QString devName);
protected:
    void run();

private:
    /* FUCHTIONS */
    void serialInit();
    void serialClose();

#if defined(CONFIG_RDA_USE_NARDA)
    int startRemoteConnection();
    void getFt232CI(QByteArray &baPath);
    float getRealValue(QString a,QString b,QString c);
#endif


    /* OBJECTS */
    XtSerial rdSerial;
    QByteArray baSerialPath;
    void getFt232CI(QByteArray &baPath);

#if defined(CONFIG_RDA_USE_NARDA)
    QByteArray baSerialPath;
    bool isRemoteConnected;
#endif
};

#endif // DEVRADIATIONDETECTOR_H
