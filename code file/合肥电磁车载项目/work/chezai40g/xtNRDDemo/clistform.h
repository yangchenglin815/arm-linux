#ifndef CLISTFORM_H
#define CLISTFORM_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTimer>
#include <QRegExp>
#include <QMessageBox>
class XtNRDDemo;
namespace Ui {
class CListForm;
}

class CListForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit CListForm(QWidget *parent = 0);
    ~CListForm();
    XtNRDDemo*pParent;

signals:
    //void signalAddItem(QString lng,QString lat, QString testvalue,QString time);
private slots:

      //void slot_additem(QString lng,QString lat,QString strTimeStamp,QString testvalue);
      void slot_info(QString taskname,QString max,QString avg,QString allrec);

      void on_btnReturn_clicked();
      void slot_gettaskname(QString taskname);


      void on_btnUpdate_clicked();

private:
    Ui::CListForm *ui;

      QString cltaskname;
    void AddItem(QString lng,QString lat,QString testvalue,QString time);

};

#endif // CLISTFORM_H
