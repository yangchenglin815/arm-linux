#ifndef DEVKEY_H
#define DEVKEY_H

#include <QThread>

class DevKey : public QThread
{
    Q_OBJECT
public:
    explicit DevKey(QObject *parent = 0);
    /* FUNCTIONS */
    void stopThread();
signals:
   // void signalKeyPress();
public slots:

protected:
    void run();
    
};

#endif // DEVKEY_H
