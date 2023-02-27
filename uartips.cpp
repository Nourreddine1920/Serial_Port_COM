#include "uartips.h"
#include "ui_uartips.h"
#include"uart.h"

Uartips::Uartips(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Uartips)
{
    ui->setupUi(this);
}

Uartips::~Uartips()
{
    delete ui;
}

void Uartips::on_commandLinkButton_clicked()
{

}


void Uartips::on_btnStaticUART_clicked()
{
    Uart* uart = new Uart();
    uart->show();
    this->hide();
}

