#include "uartips.h"
#include "ui_uartips.h"
#include "dash.h"

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
    Dash* dash = new Dash();
    dash->show();
    this->hide();
}

