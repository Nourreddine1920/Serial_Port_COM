#include "uart.h"
#include "ui_uart.h"
#include<QtSerialPort/QSerialPort>
#include<QMessageBox>
#include "dashboard.h"


Uart::Uart(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Uart)
{
    ui->setupUi(this);

    // Disable maximizing
    setFixedSize(width(), height());

    QWidget::setWindowTitle("UART Configurations ");

//    QWidget::setFixedSize(QSize(411,511));


    // Ports

    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
        QStringList stringPorts;

        // Parcours de la liste des ports série disponibles
        for(const QSerialPortInfo &info : portList) {
            // Vérification si le port contient la chaîne "STMicroelectronics STLink Virtual COM Port"
            if(info.description().contains("STMicroelectronics STLink Virtual COM Port")) {
                // Ajout du nom du port dans la liste à afficher sur l'interface
               stringPorts << info.portName();
            }
        }


    ui->comboBox_6->addItems(stringPorts);
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
    // Parities
    ui->comboBox_4->addItem("No Parity");
    ui->comboBox_4->addItem("Even Parity");
    ui->comboBox_4->addItem("Odd Parity");
    ui->comboBox_4->addItem("Mark Parity");
    ui->comboBox_4->addItem("Space Parity");
    //Flow Controls
    ui->comboBox_2->addItem("No Flow Control");
    ui->comboBox_2->addItem("Hardware Flow Control");
    ui->comboBox_2->addItem("Software Flow Control");

}

Uart::~Uart()
{
    delete ui;
}

void Uart::on_pushButton_clicked(){

}

void Uart::on_btnConnect_clicked()
{
    QString portName = ui->comboBox_6->currentText();
        serialPort = new QSerialPort(this);
        serialPort->setPortName(portName);

        //serialPort->open(QIODevice::ReadWrite);

//        if(!serialPort->isOpen()){
//            ui->textBrowser->setTextColor(Qt::red);
//            ui->textBrowser->append("!!!! Something went Wrong !!!!");
//        }
//        else {

            QString stringbaudRate = ui->comboBox_5->currentText();
                int intbaudRate = stringbaudRate.toInt();
                serialPort->setBaudRate(intbaudRate);

                QString dataBits = ui->comboBox->currentText();
                if(dataBits == "5 Bits") {
                   serialPort->setDataBits(QSerialPort::Data5);
                }
                else if((dataBits == "6 Bits")) {
                   serialPort->setDataBits(QSerialPort::Data6);
                }
                else if(dataBits == "7 Bits") {
                   serialPort->setDataBits(QSerialPort::Data7);
                }
                else if(dataBits == "8 Bits"){
                   serialPort->setDataBits(QSerialPort::Data8);
                }

                QString stopBits = ui->comboBox_3->currentText();
                if(stopBits == "1 Bit") {
                 serialPort->setStopBits(QSerialPort::OneStop);
                }
                else if(stopBits == "1,5 Bits") {
                 serialPort->setStopBits(QSerialPort::OneAndHalfStop);
                }
                else if(stopBits == "2 Bits") {
                 serialPort->setStopBits(QSerialPort::TwoStop);
                }

                QString parity = ui->comboBox_4->currentText();
                if(parity == "No Parity"){
                  serialPort->setParity(QSerialPort::NoParity);
                }
                else if(parity == "Even Parity"){
                  serialPort->setParity(QSerialPort::EvenParity);
                }
                else if(parity == "Odd Parity"){
                  serialPort->setParity(QSerialPort::OddParity);
                }
                else if(parity == "Mark Parity"){
                  serialPort->setParity(QSerialPort::MarkParity);
                }
                else if(parity == "Space Parity") {
                    serialPort->setParity(QSerialPort::SpaceParity);
                }


                QString flowControl = ui->comboBox_2->currentText();
                if(flowControl == "No Flow Control") {
                  serialPort->setFlowControl(QSerialPort::NoFlowControl);
                }
                else if(flowControl == "Hardware Flow Control") {
                  serialPort->setFlowControl(QSerialPort::HardwareControl);
                }
                else if(flowControl == "Software Flow Control") {
                  serialPort->setFlowControl(QSerialPort::SoftwareControl);
                }
                //code = ui->lineEdit_2->text();
                //codeSize = code.size();
                //connect(&serialPort,SIGNAL(readyRead()),this,SLOT(recieveMessage()));
                if(serialPort->open(QIODevice::ReadWrite)){
                QMessageBox::information(this,"COM ouverte","connexion OK sur"+ portName);
                serialPort->write("Hello\n");

                }else{
                //probleme d'ouverure du port serie
                QMessageBox::critical(this,"Erreur sur port"+QString(portName),serialPort->errorString());
                exit(1);
                }

       // }
                Dashboard* dashboard = new Dashboard();
                dashboard->show();
                this->hide();


}
// Recieve msg from UART application
void Uart::recieveMessage(){
    QByteArray dataBA = serialPort->readAll();
    QString data(dataBA);
    buffer.append(data);
    int index = buffer.indexOf(code);
    if(index != -1){
        QString message = buffer.mid(0,index);
        ui->textBrowser->setTextColor(Qt::blue); // Receieved message's color is blue.
        ui->textBrowser->append(message);
        buffer.remove(0,index+codeSize);
       }

}
// Disconnect Button
void Uart::on_btnDisconnect_clicked()
{

    serialPort->close();


}

// Button of Refresh Ports

void Uart::on_btnRefresh_clicked()
{
    ui->comboBox_6->clear();
        QList<QSerialPortInfo> ports = info.availablePorts();
        QList<QString> stringPorts;
        for(int i = 0 ; i < ports.size() ; i++){
            stringPorts.append(ports.at(i).portName());
        }
        ui->comboBox->addItems(stringPorts);

}


void Uart::on_btnClear_clicked()
{
    ui->textBrowser->clear();

}


void Uart::on_btnSendMsg_clicked()
{
    QString message = ui->lineEdit_3->text();
    QByteArray data = message.toUtf8();
    ui->textBrowser->setTextColor(Qt::darkGreen); // Color of message to send is green.
    ui->textBrowser->append(message);
    serialPort->write(data);


}




