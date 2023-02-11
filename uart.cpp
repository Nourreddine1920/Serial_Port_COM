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

    // Ports
    QList<QSerialPortInfo> ports = info.availablePorts();
    QList<QString> stringPorts;
    for(int i = 0 ; i < ports.size() ; i++){
        stringPorts.append(ports.at(i).portName());
    }
    ui->comboBox->addItems(stringPorts);

}

Uart::~Uart()
{
    delete ui;
}

