#ifndef DEVBEEP_H
#define DEVBEEP_H

#include <QThread>

enum BeepStat {
    BEEP_OFF,
    BEEP_ON
};

class DevBeep : public QThread
{
    Q_OBJECT
public:
    explicit DevBeep(QObject *parent = 0);

    /* FUNCTIONS */
    void stopThread();
    
signals:
    
public slots:
    void slotBeepStart(int count, int lmsec=1000, int rmsec=1000);
    void slotBeepStop();

protected:
    void run();

private:
    /* FUNCTIONS */
    int setBeepStat(BeepStat stat);

    /* OBJECTS */
    int bpCount;
    int bplmsec;
    int bprmsec;
};

#endif // DEVBEEP_H
