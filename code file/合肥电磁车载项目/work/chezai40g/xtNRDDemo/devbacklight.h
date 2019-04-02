#ifndef DEVBACKLIGHT_H
#define DEVBACKLIGHT_H

#include <QObject>

enum BlKeepTimeUpdateReson {
    BLKT_RESON_TIMEOUT,
    BLKT_RESON_MOUSEVENT
};

class DevBacklight : public QObject
{
    Q_OBJECT
public:
    explicit DevBacklight(QObject *parent = 0);

    /* FUNCTIONS */
    bool getBacklightStat();
    
signals:
    
public slots:
    void slotKeepTimeUpdate(int type); // 1: TimerTimeout 2: MouseEvent

private:
    /* FUNCTIONS */
    void setBlBrightness(int value);
    int getBlBrightness();


    /* OBJECTS */
    int blKeepTime;
    bool isBacklightON;
};

#endif // DEVBACKLIGHT_H
