#include "info.h"
#include "ui_info.h"

info::info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::info)
{
    ui->setupUi(this);
}

info::~info()
{
    delete ui;
}

void info::on_btnReturn_clicked()
{
    this->close();
}
