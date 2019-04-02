#include "devinfo.h"
#include "ui_devinfo.h"

devinfo::devinfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::devinfo)
{
    ui->setupUi(this);
}

devinfo::~devinfo()
{
    delete ui;
}

//关闭info界面
void devinfo::on_btnReturn_clicked()
{
    this->close();
}
