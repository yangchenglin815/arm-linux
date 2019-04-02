#include "clistform.h"
#include "ui_clistform.h"
#include <QRegExp>
#include "common.h"
#include <QDebug>

CListForm::CListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CListForm)
{
   ui->setupUi(this);

   pParent =(XtNRDDemo*) parent;


   ui->list->setColumnCount(4);
   ui->list->setRowCount(6);
   QStringList headers;
   headers<<"经度"<<"纬度"<<"测量值"<<"时间";
 //  ui->twListData->setGeometry(QRect(0,80,400,241));
   ui->list->setHorizontalHeaderLabels(headers);
   ui->list->setColumnWidth(0,95);
   ui->list->setColumnWidth(1,95);
   ui->list->setColumnWidth(2,95);
   ui->list->setColumnWidth(3,170);
  // ui->twListData->setColumnWidth(4,210);
   // ui->twListData->resizeColumnsToContents();
  // connect((QWidget*)pParent, SIGNAL(signalAddItem(QString,QString,QString ,QString)), this, SLOT(slot_additem(QString,QString,QString,QString)));


   connect((QWidget*)pParent, SIGNAL(signalInfo(QString,QString,QString ,QString)), this, SLOT(slot_info(QString,QString,QString,QString)));
}


void CListForm::AddItem(QString lng,QString lat,QString testvalue,QString time)
{
     // this->close();
    //qDebug()<<"slotadd";
    ui->list->insertRow(0);
    //ui->list->removeAll();
    //ui->list->removeRow(6);

    ui->list->setItem(0, 0, new QTableWidgetItem(lng));
    ui->list->setItem(0, 1, new QTableWidgetItem(lat));
    ui->list->setItem(0, 2, new QTableWidgetItem(testvalue));
    ui->list->setItem(0, 3, new QTableWidgetItem(time));

}

void CListForm::slot_gettaskname(QString taskname)
{
     //qDebug()<<"slotgettaskname";
     cltaskname = taskname;

    // qDebug()<<"taskname="<<cltaskname;
}

void CListForm::slot_info(QString taskname,QString max,QString avg,QString allrec)
{
     // this->close();
    ui->lblTaskName->setText("本次测量:"+taskname);
    ui->lblTaskMax->setText("最大值:"+max);
    ui->lblTaskAvg->setText("平均值:"+avg);

    ui->lblTaskCount->setText("记录数:"+allrec);
}

CListForm::~CListForm()
{
    delete ui;
}

void CListForm::on_btnReturn_clicked()
{
    this->close();
}





void CListForm::on_btnUpdate_clicked()
{   //qDebug()<<"clicked update";
  //  ui->list->clear();

    ui->list->setRowCount(0);
    ui->list->clearContents();

    QSqlQuery query;
    //qDebug()<<"taskname="<<cltaskname;
    QString sql = "select lng,lat,testvalue,testtime from xt_data where taskname = '"+cltaskname+"' order by id asc";
    if(query.exec(sql))
        {//qDebug()<<"exec";
        while(query.next())
            {//qDebug()<<"while 1";
        QString lng = query.value(0).toString();
       // qDebug()<<lng;
        QString lat = query.value(1).toString();
       // qDebug()<<lat;
        QString testvalue = query.value(2).toString();
       // qDebug()<<testvalue;
        QString time = query.value(3).toString();
      //  qDebug()<<time;
        AddItem(lng,lat,testvalue,time);
 }
    }
}

