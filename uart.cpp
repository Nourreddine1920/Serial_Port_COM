#include "uart.h"
#include "ui_uart.h"

Uart::Uart(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Uart)
{
    ui->setupUi(this);

    // Disable maximizing
      setFixedSize(width(), height());
}

Uart::~Uart()
{
    delete ui;
}

