#include "uart.h"
#include "ui_uart.h"

Uart::Uart(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Uart)
{
    ui->setupUi(this);
}

Uart::~Uart()
{
    delete ui;
}

