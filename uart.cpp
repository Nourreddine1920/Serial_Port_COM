#include "uart.h"
#include "ui_uart.h"
#include<QtSerialPort/QSerialPort>
#include<QMessageBox>
#include "dashboard.h"
#include <QFontDatabase>
#include <QSettings>
#include "configchoice.h"
#include <QStatusBar>
#include <QDesktopServices>



Uart::Uart(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Uart)
{
    ui->setupUi(this);

    // Create a status bar
    QStatusBar *statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
    // Create QLabel widgets for the logos
    QLabel *linkedinLabel = new QLabel(this);
    QLabel *instagramLabel = new QLabel(this);
    QLabel *facebookLabel = new QLabel(this);

    // Set the pixmap images for each label
    QPixmap linkedinPixmap("C:/Users/nawledbr/Documents/Serial_Port_COM/linkedin-removebg-preview.png"); // Replace with the actual path to the LinkedIn logo image
    QPixmap instagramPixmap("C:/Users/nawledbr/Documents/Serial_Port_COM/insta.png"); // Replace with the actual path to the Instagram logo image
    QPixmap facebookPixmap("C:/Users/nawledbr/Documents/Serial_Port_COM/facebook-removebg-preview.png"); // Replace with the actual path to the Facebook logo image

    linkedinLabel->setPixmap(linkedinPixmap.scaled(21, 21, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    instagramLabel->setPixmap(instagramPixmap.scaled(19, 19, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    facebookLabel->setPixmap(facebookPixmap.scaled(19, 19, Qt::KeepAspectRatio, Qt::SmoothTransformation));
//    linkedinLabel->setStyleSheet("background-color: #D3D3D3	;");
//    instagramLabel->setStyleSheet("background-color: #D3D3D3	;");
//    facebookLabel->setStyleSheet("background-color: #D3D3D3	;");

    // Set the cursor shape to indicate clickable labels
    linkedinLabel->setCursor(Qt::PointingHandCursor);
    instagramLabel->setCursor(Qt::PointingHandCursor);
    facebookLabel->setCursor(Qt::PointingHandCursor);

    // Connect the linkActivated signal of the labels to the corresponding slots
//    connect(linkedinLabel, &QLabel::linkActivated, this, &Uart::openLinkedInUrl);
//    connect(instagramLabel, &QLabel::linkActivated, this, &Uart::openInstagramUrl);
//    connect(facebookLabel, &QLabel::linkActivated, this, &Uart::openFacebookUrl);

    // Enable text interaction and set open external links property for the labels
    linkedinLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    linkedinLabel->setOpenExternalLinks(true);
    instagramLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    instagramLabel->setOpenExternalLinks(true);
    facebookLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    facebookLabel->setOpenExternalLinks(true);


//    // Set the labels' text with the URLs
//    linkedinLabel->setText("<a href=\"https://www.linkedin.com/company\"></a>");
//    instagramLabel->setText("<a href=\"https://www.instagram.com/company\"></a>");
//    facebookLabel->setText("<a href=\"https://www.facebook.com/company\"></a>");


    // Add the QLabel widgets to the status bar
    statusBar->addPermanentWidget(linkedinLabel);
    statusBar->addPermanentWidget(instagramLabel);
    statusBar->addPermanentWidget(facebookLabel);

    // Create a QLabel for the footer text
    QLabel *footerLabel = new QLabel("© ACTIA Engineering Services", this);
    footerLabel->setStyleSheet("background-color: #D3D3D3	; color: #36454F;");
    footerLabel->setAlignment(Qt::AlignCenter);

    // Set the gray background color
    QPalette palette = footerLabel->palette();
    QPalette palette1 = linkedinLabel->palette();
    QPalette palette2 = instagramLabel->palette();
    QPalette palette3 = facebookLabel->palette();

//    palette.setColor(QPalette::Background, QColor(200, 200, 200)); // Adjust the color as desired
    footerLabel->setAutoFillBackground(true);
    linkedinLabel->setAutoFillBackground(true);
    instagramLabel->setAutoFillBackground(true);
    facebookLabel->setAutoFillBackground(true);

    footerLabel->setPalette(palette);
    linkedinLabel->setPalette(palette1);
    instagramLabel->setPalette(palette2);
    facebookLabel->setPalette(palette3);

    // Add the QLabel to the status bar
    statusBar->addWidget(footerLabel, 1);

    // Set the status bar properties
    statusBar->setSizeGripEnabled(false); // Optional: Disable the size grip handle on the status bar
    statusBar->setStyleSheet("background-color: #D3D3D3	;");

    statusBar->setStyleSheet("QStatusBar { background-color: #D3D3D3; }");
    statusBar->setStyleSheet("QStatusBar::item { border: none; }"); // Remove borders around the widgets
    statusBar->setContentsMargins(0, 0, 10, 0); // Add some right margin to the widgets

    // Disable maximizing
    setFixedSize(width(), height());

    QWidget::setWindowTitle("UART Connection ");






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


    // Set the font and style sheet for the title label
    QFontDatabase fontDatabase;
    QStringList fontFamilies = fontDatabase.families();

    // Choose the first available font as the best font
    QString bestFont = fontFamilies.first();

    // Create a font object with the best font and size
    QFont font(bestFont, 17);

    // Set the font and style sheet for the label
    ui->label_7->setFont(font);

    ui->label_7->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");

    ui->label_7->setAlignment(Qt::AlignCenter);



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
    QString styleSheet2 =
        "QPushButton {"
        "    background-color: gray;"
        "    border: none;"
        "    color: white;"
        "    padding: 3px 3px;"
        "    text-align: center;"
        "    text-decoration: none;"
        "    font-size: 14px;"
        "    margin: 4px 2px;"
        "    border-radius: 10px;"
        "}"
        ""
        "QPushButton:hover {"
        "    background-color: #3e8e41;"
        "}";
    ui->btnDisconnect->setStyleSheet(styleSheet2);
    ui->btnConnect->setStyleSheet(styleSheet2);
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

                QString styleSheet = "\
                    QMessageBox {\
                        background-color:#D3D3D3	;\
                        color: #263238;\
                        font-family:  Fantasy ;\
                        font-size: 12px;\
                    }\
                    \
                    QMessageBox QLabel {\
                        color: #000000	;\
                    }\
                    \
                    QMessageBox QPushButton {\
                        background-color: #4CAF50;\
                        border: 1px solid #388E3C;\
                        color: #FFFFFF;\
                        padding: 3px;\
                        min-width: 50px;\
                    }\
                    \
                    QMessageBox QPushButton:hover {\
                        background-color: #388E3C;\
                    }";

                if(serialPort->open(QIODevice::ReadWrite)){

                        QMessageBox msgBox;
                        msgBox.setWindowTitle("Serial Connection");
                        msgBox.setStyleSheet(styleSheet);
                        msgBox.setIcon(QMessageBox::Information);
                        msgBox.setText("Connexion OK sur " + portName);
                        msgBox.exec();

//                QMessageBox* MessageBOX;
////                MessageBOX->setStyleSheet(styleSheet);
//                QMessageBox::information(this,"COM ouverte","connexion OK sur"+ portName);
//                //serialPort->write("Hello/n");

                }else{
                //probleme d'ouverure du port serie
                QMessageBox::critical(this,"Erreur sur port"+QString(portName),serialPort->errorString());
                exit(1);
                }







                QByteArray buffer;
                const int MAX_BUFFER_SIZE = 20; // Replace with your desired buffer size


                QByteArray data = serialPort->readAll();
                buffer.append(data);
//                QString message(data);
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

       // }/*
                // Initialize the singleton instance of Uart
                Uart::getInstance()->serialPort = serialPort;
                ConfigChoice* configChoice = new ConfigChoice();
                configChoice->show();
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
//           qDebug() << "Received message:" << data;


           // Check if buffer exceeds maximum size


           // Check if buffer contains a complete message
           const char MESSAGE_TERMINATOR = '\n'; // Replace with your desired message terminator
           int messageEndIndex = buffer.indexOf(MESSAGE_TERMINATOR);
           if (messageEndIndex != -1)
           {
               QByteArray message = buffer.left(messageEndIndex);
               buffer.remove(0, messageEndIndex + 1); // Remove the message and the terminator from the buffer

               // Process the message here
//               qDebug() << "Received message:" << message;
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
//    QString message = ui->lineEdit_3->text();
//    QByteArray data = message.toUtf8();
//    ui->textBrowser->setTextColor(Qt::darkGreen); // Color of message to send is green.
//    ui->textBrowser->append(message);
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
//    serialPort->write(data);


    QSettings settings("UARTConfig.txt", QSettings::IniFormat);
    settings.beginGroup("UART4Configs");

    QString baudrate;
    QString Parity;
    QString stopBits;
    QString DataBits;
    QString FlowControl;

    QString BaudrateConfig = settings.value("Baudrate" , baudrate).toString();
    QString ParityConfig = settings.value("Parity" , Parity).toString();
    QString stopBitsConfig = settings.value("stopBits" , stopBits).toString();
    QString DataBitsConfig = settings.value("DataBits" , DataBits).toString();
    QString FlowControlConfig = settings.value("FlowControl" , FlowControl).toString();
    settings.endGroup();

    struct Message {
        uint8_t id; // Message ID
        uint16_t length; // Length of the payload
        uint8_t *payload; // Pointer to the payload data
    };

    // Define the message ID and payload
    uint8_t messageIPID = 0x01;
    char delimiter[2] = "|";
    char delimiter2[2] = ",";

    uint8_t messageBaudID = 0x02;
    uint8_t messageParityID = 0x03;
    uint8_t messageStopID = 0x04;
    uint8_t messageDataID = 0x05;
    uint8_t messageFlowID = 0x06;

    QByteArray dataBaud = BaudrateConfig.toUtf8();
    QByteArray dataparity = ParityConfig.toUtf8();
    QByteArray datastop = stopBitsConfig.toUtf8();
    QByteArray databits = DataBitsConfig.toUtf8();
    QByteArray dataflow = FlowControlConfig.toUtf8();



//    QByteArray checking = "\n";


//    QByteArray payloadData = "This is my payload data";

    // Create a message packet
    QByteArray packet;
//    packet.append(messageIPID);
//    packet.append(delimiter);


    packet.append(messageBaudID);
    packet.append(delimiter);

    packet.append(dataBaud);

    packet.append(delimiter);
    packet.append(messageParityID);
    packet.append(delimiter);

    packet.append(dataparity);

    packet.append(delimiter);
    packet.append(messageStopID);
    packet.append(delimiter);

    packet.append(datastop);
    packet.append(delimiter);

    packet.append(messageDataID);
    packet.append(delimiter);

    packet.append(databits);
    packet.append(delimiter);

    packet.append(messageFlowID);
    packet.append(delimiter);

    packet.append(dataflow);
    packet.append(delimiter2);


//    packet.append(checking);


    // Write the packet to the serial port
//    QString baud="AT+BAUD4\r\n";
//    serialPort->write("AT+BAUD4\r\n"); // Change to 9600 baud rate
//    qDebug() << " message:" << baud;


        serialPort->write(packet); // Change to 9600 baud rate
//        qDebug() << " packet:" << packet;


////        QSettings settings("UARTConfig.txt", QSettings::IniFormat);
        settings.beginGroup("UART5Configs");

        QString baudrate1;
        QString Parity1;
        QString stopBits1;
        QString DataBits1;
        QString FlowControl1;

        QString BaudrateConfig1 = settings.value("Baudrate" , baudrate1).toString();
        QString ParityConfig1 = settings.value("Parity" , Parity1).toString();
        QString stopBitsConfig1 = settings.value("stopBits" , stopBits1).toString();
        QString DataBitsConfig1 = settings.value("DataBits" , DataBits1).toString();
        QString FlowControlConfig1 = settings.value("FlowControl" , FlowControl1).toString();
        settings.endGroup();


        // Define the message ID and payload
        uint8_t messageIPID1 = 0x01;
        char delimiter1[2] = "|";

        uint8_t messageBaudID1 = 0x1;
        uint8_t messageParityID1 = 0x03;
        uint8_t messageStopID1 = 0x04;
        uint8_t messageDataID1 = 0x05;
        uint8_t messageFlowID1 = 0x06;

        QByteArray dataBaud1 = BaudrateConfig1.toUtf8();
        QByteArray dataparity1 = ParityConfig1.toUtf8();
        QByteArray datastop1 = stopBitsConfig1.toUtf8();
        QByteArray databits1 = DataBitsConfig1.toUtf8();
        QByteArray dataflow1 = FlowControlConfig1.toUtf8();



    //    QByteArray checking = "\n";


    //    QByteArray payloadData = "This is my payload data";

        // Create a message packet
        QByteArray packet1;
    //    packet.append(messageIPID);
    //    packet.append(delimiter);


        packet1.append(messageBaudID1);
        packet1.append(delimiter1);

        packet1.append(dataBaud1);

        packet1.append(delimiter1);
        packet1.append(messageParityID1);
        packet1.append(delimiter1);

        packet1.append(dataparity1);

        packet1.append(delimiter1);
        packet1.append(messageStopID1);
        packet1.append(delimiter1);

        packet1.append(datastop1);
        packet1.append(delimiter1);

        packet1.append(messageDataID1);
        packet1.append(delimiter1);

        packet1.append(databits1);
        packet1.append(delimiter1);

        packet1.append(messageFlowID1);
        packet1.append(delimiter1);

        packet1.append(dataflow1);
        packet1.append(delimiter2);


        serialPort->write(packet1);



        QSettings settingsSPI("SPIConfig.txt", QSettings::IniFormat);


        settingsSPI.beginGroup("SPI1Configs");

        QString Mode;
        QString NSS;
        QString DataSize;
        QString FirstBit;

        QString ModeConfig1 = settingsSPI.value("Mode" , Mode).toString();
        QString NSSConfig1 = settingsSPI.value("NSS" , NSS).toString();
        QString DataSizeConfig1 = settingsSPI.value("DataSize" , DataSize).toString();
        QString FirstBitConfig1 = settingsSPI.value("FirstBit" , FirstBit).toString();
        settingsSPI.endGroup();


        qDebug() << " Mode:" << ModeConfig1;

        // Define the message ID and payload
//        uint8_t messageIPID1 = 0x01;
//        char delimiter1[2] = "|";

        uint8_t messageModeID = 0x8;
        uint8_t messageNSSID = 0x03;
        uint8_t messageDataSizeID = 0x04;
        uint8_t messageFirstBitID = 0x05;

        QByteArray dataMode = ModeConfig1.toUtf8();
        QByteArray dataNSS = NSSConfig1.toUtf8();
        QByteArray dataSize = DataSizeConfig1.toUtf8();
        QByteArray dataFirstbits = FirstBitConfig1.toUtf8();



    //    QByteArray checking = "\n";


    //    QByteArray payloadData = "This is my payload data";

        // Create a message packet
        QByteArray packet2;
    //    packet.append(messageIPID);
    //    packet.append(delimiter);


        packet2.append(messageModeID);
        packet2.append(delimiter1);

        packet2.append(dataMode);

        packet2.append(delimiter1);
        packet2.append(messageNSSID);
        packet2.append(delimiter1);

        packet2.append(dataNSS);

        packet2.append(delimiter1);
        packet2.append(messageDataSizeID);
        packet2.append(delimiter1);

        packet2.append(dataSize);
        packet2.append(delimiter1);

        packet2.append(messageFirstBitID);
        packet2.append(delimiter1);

        packet2.append(dataFirstbits);

        serialPort->write(packet2);






            qDebug() << " packet:" << packet;
            qDebug() << " packet1:" << packet1;
            qDebug() << " packet2:" << packet2;

//            qDebug() << " packe1:" << packet1;
//        serialPort->write(delimiter2);
        ui->textBrowser->setTextColor(Qt::darkGreen); // Color of message to send is green.
        ui->textBrowser->append(packet);
        ui->textBrowser->append(packet1);
        ui->textBrowser->append(packet2);



}

void Uart::openLinkedInUrl()
{
    QDesktopServices::openUrl(QUrl("https://www.linkedin.com/company/actia-engineering-services/mycompany/"));
}
void Uart::openFacebookUrl()
{
    QDesktopServices::openUrl(QUrl("https://mail.google.com/mail/u/0/#inbox"));

}
void Uart::openInstagramUrl()
{
    QDesktopServices::openUrl(QUrl("https://www.overleaf.com/project/646c5828c06d704d40e977c0"));

}

QSerialPort* Uart::getSerialPort() const {
    return serialPort;
}

Uart* Uart::instance = nullptr;

Uart* Uart::getInstance()
{
    if (!instance) {
        instance = new Uart();
    }
    return instance;
}





