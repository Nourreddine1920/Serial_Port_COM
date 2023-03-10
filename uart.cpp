#include "uart.h"
#include "ui_uart.h"
#include<QtSerialPort/QSerialPort>
#include<QMessageBox>
#include "dashboard.h"
#include <QFontDatabase>



Uart::Uart(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Uart)
{
    ui->setupUi(this);

    // Disable maximizing
    setFixedSize(width(), height());

    QWidget::setWindowTitle("UART Configurations ");






//    QLabel* label = new QLabel(this);
//    label->setText("UART Configurations");

//    label->setPixmap(QPixmap("C:/Users/nawledbr/Documents/Serial_Port_COM/config4.png"));
//    label->setStyleSheet("QLabel { background-color: #f0f0f0; border: 1px solid #ccc; border-radius: 5px; padding: 5px; }"
//                         "QLabel::scaledContents { align: center; }");

    QString styleSheet1 =
        "QLabel {"
        "    background-color: white;"
        "    border: none;"
        "    color: black;"
        "    padding: 15px 32px;"
        "    text-align: center;"
        "    text-decoration: none;"
        "    font-size: 20px;"
        "    margin: 4px 2px;"
        "    border-radius: 10px;"
        "}"
       ;



    // Add the title label and the icon to the main layout


//    QWidget::setFixedSize(QSize(411,511));

    QString styleSheet =
        "QPushButton {"
        "    background-color: gray;"
        "    border: none;"
        "    color: white;"
        "    padding: 3px 3px;"
        "    text-align: center;"
        "    text-decoration: none;"
        "    font-size: 12px;"
        "    margin: 4px 2px;"
        "    border-radius: 10px;"
        "}"
        ""
        "QPushButton:hover {"
        "    background-color: #3e8e41;"
        "}";
    ui->btnDisconnect->setStyleSheet(styleSheet);
    ui->btnConnect->setStyleSheet(styleSheet);
    ui->btnClear->setStyleSheet(styleSheet);
    ui->btnRefresh->setStyleSheet(styleSheet);
    ui->btnSendMsg->setStyleSheet(styleSheet);


//    ui->UartConfig->setStyleSheet(styleSheet1);




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

    ui->label->setStyleSheet("font: bold 15px; color: black; background-color: white;");
    ui->comboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
    ui->label_4->setStyleSheet("font: bold 15px; color: black; background-color: white;");
    ui->comboBox_4->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
    ui->label_3->setStyleSheet("font: bold 15px; color: black; background-color: white;");
    ui->comboBox_3->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
    ui->label_5->setStyleSheet("font: bold 15px; color: black; background-color: white;");
    ui->comboBox_5->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
    ui->label_6->setStyleSheet("font: bold 15px; color: black; background-color: white;");
    ui->comboBox_6->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
    ui->label_2->setStyleSheet("font: bold 15px; color: black; background-color: white;");
    ui->comboBox_2->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
    ui->label_8->setStyleSheet("font: bold 15px; color: black; background-color: white;");
    ui->lineEdit_2->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
    ui->lineEdit_3->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");



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
                //serialPort->write("Hello/n");

                }else{
                //probleme d'ouverure du port serie
                QMessageBox::critical(this,"Erreur sur port"+QString(portName),serialPort->errorString());
                exit(1);
                }



                QByteArray buffer;
                const int MAX_BUFFER_SIZE = 20; // Replace with your desired buffer size


                QByteArray data = serialPort->readAll();
                buffer.append(data);
                qDebug() << "Received message:" << data;
                ui->textBrowser->setTextColor(Qt::blue); // Receieved data's color is blue.
                ui->textBrowser->append(data);


                       // Check if buffer exceeds maximum size


                       // Check if buffer contains a complete message
//                       const char MESSAGE_TERMINATOR = '\n'; // Replace with your desired message terminator
//                       int messageEndIndex = buffer.indexOf(MESSAGE_TERMINATOR);
//                       if (messageEndIndex != -1)
//                       {
//                           QByteArray message = buffer.left(messageEndIndex);
//                           buffer.remove(0, messageEndIndex + 1); // Remove the message and the terminator from the buffer

                           // Process the message here

//                       }

       // }
                Dashboard* dashboard = new Dashboard();
                dashboard->show();
                this->hide();


}
// Recieve msg from UART application
//void Uart::recieveMessage(){
//    QByteArray dataBA = serialPort->readAll();
//    QString data(dataBA);
//    buffer.append(data);
//    //int index = buffer.indexOf(code);
//    //if(index != -1){
//        //QString message = buffer.mid(0,index);
//        ui->textBrowser->setTextColor(Qt::blue); // Receieved message's color is blue.
//        ui->textBrowser->append(buffer);
//        //buffer.remove(0,index+codeSize);
//      // }

//}
void Uart::recieveMessage(){
    QByteArray buffer;
    const int MAX_BUFFER_SIZE = 20; // Replace with your desired buffer size


           QByteArray data = serialPort->readAll();
           buffer.append(data);
           qDebug() << "Received message:" << data;


           // Check if buffer exceeds maximum size


           // Check if buffer contains a complete message
           const char MESSAGE_TERMINATOR = '\n'; // Replace with your desired message terminator
           int messageEndIndex = buffer.indexOf(MESSAGE_TERMINATOR);
           if (messageEndIndex != -1)
           {
               QByteArray message = buffer.left(messageEndIndex);
               buffer.remove(0, messageEndIndex + 1); // Remove the message and the terminator from the buffer

               // Process the message here
               qDebug() << "Received message:" << message;
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
    // Set text color to dark green
//    ui->textBrowser->setTextColor(Qt::darkGreen);

    // Set background color to light gray
//    ui->textBrowser->setStyleSheet("background-color: #f0f0f0;");

    // Set font family, size, and weight
//    ui->textBrowser->setFont(QFont("Arial", 12, QFont::Bold));

    // Set text alignment to center
//    ui->textBrowser->setAlignment(Qt::AlignCenter);

    // Add padding to the text browser
//    ui->textBrowser->setStyleSheet("padding: 10px;");
    serialPort->write(data);


}




