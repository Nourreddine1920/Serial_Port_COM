#include "uart.h"
#include "ui_uart.h"

Uart::Uart(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Uart)
{
    ui->setupUi(this);

    // Disable maximizing
    setFixedSize(width(), height());

    QWidget::setWindowTitle("UART Configurations ");
}

Uart::~Uart()
{
    delete ui;
}

