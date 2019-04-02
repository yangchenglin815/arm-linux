#ifndef DEVINFO_H
#define DEVINFO_H

#include <QWidget>

namespace Ui {
class devinfo;
}

class devinfo : public QWidget
{
    Q_OBJECT
    
public:
    explicit devinfo(QWidget *parent = 0);
    ~devinfo();
     Ui::devinfo *ui;
    
private slots:
    void on_btnReturn_clicked();

private:
   // Ui::devinfo *ui;
};

#endif // DEVINFO_H
