#include "dash.h"
#include "ui_dash.h"
#include "uartips.h"
#include "uart.h"

Dash::Dash(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dash)
{
    ui->setupUi(this);
    setFixedSize(width(), height());
    QWidget::setWindowTitle("IPs Configurations ");





}

Dash::~Dash()
{
    delete ui;
}

void Dash::on_UARTbtn_clicked()
{
    Uartips* uartips = new Uartips();
    uartips->show();
    this->hide();

}




