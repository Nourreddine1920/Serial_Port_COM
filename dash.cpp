#include "dash.h"
#include "ui_dash.h"
#include "uart.h"

Dash::Dash(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dash)
{
    ui->setupUi(this);
    setFixedSize(width(), height());

}

Dash::~Dash()
{
    delete ui;
}

void Dash::on_UARTbtn_clicked()
{
    Uart* uart = new Uart();
    uart->show();
    this->hide();

}

