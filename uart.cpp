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
    // Baud Rate Ratios
    QList<qint32> baudRates = info.standardBaudRates(); // What baudrates does my computer support ?
    QList<QString> stringBaudRates;
    for(int i = 0 ; i < baudRates.size() ; i++){
        stringBaudRates.append(QString::number(baudRates.at(i)));
    }
    ui->comboBox_5->addItems(stringBaudRates);
    // Data Bits
    ui->comboBox->addItem("5");
    ui->comboBox->addItem("6");
    ui->comboBox->addItem("7");
    ui->comboBox->addItem("8");
    // Stop Bits
    ui->comboBox_3->addItem("1 Bit");
    ui->comboBox_3->addItem("1,5 Bits");
    ui->comboBox_3->addItem("2 Bits");

}

Uart::~Uart()
{
    delete ui;
}

