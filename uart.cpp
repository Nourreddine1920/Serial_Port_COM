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
#include <QUrl>
#include <QBuffer>
#include <QProcess>

Uart::Uart(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Uart)
{
    ui->setupUi(this);

    // Create a status bar
    QStatusBar *statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
    // Create QLabel widgets for the logos
//    QLabel *linkedinLabel = new QLabel(this);
//    QLabel *instagramLabel = new QLabel(this);
//    QLabel *facebookLabel = new QLabel(this);

//    // Set the pixmap images for each label
//    QPixmap linkedinPixmap("C:/Users/nawledbr/Documents/Serial_Port_COM/linkedin-removebg-preview.png"); // Replace with the actual path to the LinkedIn logo image
//    QPixmap instagramPixmap("C:/Users/nawledbr/Documents/Serial_Port_COM/insta.png"); // Replace with the actual path to the Instagram logo image
//    QPixmap facebookPixmap("C:/Users/nawledbr/Documents/Serial_Port_COM/facebook-removebg-preview.png"); // Replace with the actual path to the Facebook logo image

//    linkedinLabel->setPixmap(linkedinPixmap.scaled(21, 21, Qt::KeepAspectRatio, Qt::SmoothTransformation));
//    instagramLabel->setPixmap(instagramPixmap.scaled(19, 19, Qt::KeepAspectRatio, Qt::SmoothTransformation));
//    facebookLabel->setPixmap(facebookPixmap.scaled(19, 19, Qt::KeepAspectRatio, Qt::SmoothTransformation));
////    linkedinLabel->setStyleSheet("background-color: #D3D3D3	;");
////    instagramLabel->setStyleSheet("background-color: #D3D3D3	;");
////    facebookLabel->setStyleSheet("background-color: #D3D3D3	;");




//    // Set the cursor shape to indicate clickable labels
//    linkedinLabel->setCursor(Qt::PointingHandCursor);
//    instagramLabel->setCursor(Qt::PointingHandCursor);




//    // Dans votre constructeur ou méthode d'initialisation
//    linkedinLabel->setText("<a href=\"https://www.linkedin.com/company/actia-engineering-services\">" +linkedinLabel->text()+ "</a>");
//    linkedinLabel->setOpenExternalLinks(true);

//    instagramLabel->setText("<a href=\"https://www.instagram.com/\">Instagram</a>");
//    instagramLabel->setOpenExternalLinks(true);

//    facebookLabel->setText("<a href=\"https://www.facebook.com/\">Facebook</a>");
//    facebookLabel->setOpenExternalLinks(true);

////     Connecter les signaux des labels à la fonction openUrl
//    connect(linkedinLabel, &QLabel::linkActivated, this, &Uart::openUrl);
//    connect(instagramLabel, &QLabel::linkActivated, this, &Uart::openUrl);
//    connect(facebookLabel, &QLabel::linkActivated, this, &Uart::openUrl);






    QPixmap linkedinPixmap("C:/Users/nawledbr/Documents/Serial_Port_COM/linkedin-removebg-preview.png");
    QPixmap instagramPixmap("C:/Users/nawledbr/Documents/Serial_Port_COM/browser.png");
    QPixmap facebookPixmap("C:/Users/nawledbr/Documents/Serial_Port_COM/gmail.png");

    // Redimensionner les icônes avec la taille souhaitée
    QPixmap linkedinIcon = linkedinPixmap.scaled(22, 22, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap instagramIcon = instagramPixmap.scaled(19, 19, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap facebookIcon = facebookPixmap.scaled(18, 18, Qt::KeepAspectRatio, Qt::SmoothTransformation);



    // Convertir les icônes en format HTML
    QByteArray linkedinData;
    QBuffer linkedinBuffer(&linkedinData);
    linkedinBuffer.open(QIODevice::WriteOnly);
    linkedinIcon.save(&linkedinBuffer, "PNG");
    QString linkedinHtmlIcon = QString("<img src=\"data:image/png;base64,%1\">").arg(QString::fromLatin1(linkedinData.toBase64().data()));

    QByteArray instagramData;
    QBuffer instagramBuffer(&instagramData);
    instagramBuffer.open(QIODevice::WriteOnly);
    instagramIcon.save(&instagramBuffer, "PNG");
    QString instagramHtmlIcon = QString("<img src=\"data:image/png;base64,%1\">").arg(QString::fromLatin1(instagramData.toBase64().data()));

    QByteArray facebookData;
    QBuffer facebookBuffer(&facebookData);
    facebookBuffer.open(QIODevice::WriteOnly);
    facebookIcon.save(&facebookBuffer, "PNG");
    QString facebookHtmlIcon = QString("<img src=\"data:image/png;base64,%1\">").arg(QString::fromLatin1(facebookData.toBase64().data()));
    // Créer les QLabel pour les icônes
    QLabel* linkedinLabel = new QLabel(this);
    QLabel* instagramLabel = new QLabel(this);
    QLabel* facebookLabel = new QLabel(this);

    // Définir le texte des labels avec les icônes HTML
    linkedinLabel->setText(QString("<a href=\"https://www.linkedin.com/company/actia-engineering-services\">%1</a>").arg(linkedinHtmlIcon));
    instagramLabel->setText(QString("<a href=\"https://lab-engineering.actia.tn\">%1</a>").arg(instagramHtmlIcon));
//    facebookLabel->setText(QString("<a href=\"mailto:contact@actia.com?subject=Subject%20of%20the%20email&body=Content%20of%20the%20email\">%1</a>").arg(facebookHtmlIcon));

    facebookLabel->setText(facebookHtmlIcon);
    facebookLabel->setOpenExternalLinks(true);
    facebookLabel->setCursor(Qt::PointingHandCursor);

//    facebookLabel->setToolTip("contact@actia.com");
    facebookLabel->setToolTip("<span style=\" font: bold 15px; color: #36454F; padding: 4px 8px; font-size: 15px;\">contact@actia.com</span>");

    // Connecter le signal linkHovered pour afficher l'info-bulle lorsque le curseur survole l'icône
    connect(facebookLabel, &QLabel::linkHovered, [facebookLabel]() {
        facebookLabel->setToolTip("contact@actia.com");
    });
    // Connecter le signal clicked de l'icône de courrier électronique à la slot correspondante
    connect(facebookLabel, &QLabel::linkActivated, this, &Uart::openGmail);


    // Activer l'ouverture des liens dans un navigateur externe
    linkedinLabel->setOpenExternalLinks(true);
    instagramLabel->setOpenExternalLinks(true);

    // Connecter les signaux des QLabel à la fonction d'ouverture des URL
//    connect(linkedinLabel, &QLabel::linkActivated, this, &Uart::openLinkedInUrl);
//    connect(instagramLabel, &QLabel::linkActivated, this, &Uart::openInstagramUrl);
//    connect(facebookLabel, &QLabel::linkActivated, this, &Uart::openFacebookUrl);

    // La fonction openUrl

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
    QLabel *footerLabel = new QLabel("© 2023 - ACTIA Engineering Services", this);
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
    QString comboBoxStyle = "QComboBox {"
      " border: 1px solid #555555;"
      " border-radius: 3px;"
      " padding: 1px 3px 1px 3px;"
      " min-width: 6em;"
      " background-color: #ffffff;"
      "}"
      "QComboBox::drop-down {"
      " subcontrol-origin: padding;"
      " subcontrol-position: top right;"
      " width: 20px;"
      " border-left-width: 1px;"
      " border-left-color: #555555;"
      " border-left-style: solid;"
      " border-top-right-radius: 3px;"
      " border-bottom-right-radius: 3px;"
      " background-color: #dddddd;"
      "}"
      "QComboBox::down-arrow {"
      " width: 0;"
      " height: 0;"
      " border-style: solid;"
      " border-width: 5px 5px 0 5px;"
      " border-color: #555555 transparent transparent transparent;"
      "}"
      "QComboBox QAbstractItemView {"
      " selection-background-color: #00ff00;"
      "}";
    ui->comboBox->setStyleSheet(comboBoxStyle);
    ui->label_4->setStyleSheet("font: bold 15px; color: black; background-color: white;");
    ui->comboBox_4->setStyleSheet(comboBoxStyle);
    ui->label_3->setStyleSheet("font: bold 15px; color: black; background-color: white;");
    ui->comboBox_3->setStyleSheet(comboBoxStyle);
    ui->label_5->setStyleSheet("font: bold 15px; color: black; background-color: white;");
    ui->comboBox_5->setStyleSheet(comboBoxStyle);
    ui->label_6->setStyleSheet("font: bold 15px; color: black; background-color: white;");
    ui->comboBox_6->setStyleSheet(comboBoxStyle);
    ui->label_2->setStyleSheet("font: bold 15px; color: black; background-color: white;");
    ui->comboBox_2->setStyleSheet(comboBoxStyle);
    QString styleSheet5 = "\
    QLineEdit { \
    background-color: #F5F5F5; \
    border: 1px solid #CCCCCC; \
    border-radius: 5px; \
    padding: 5px; \
    font-family: Arial; \
    font-size: 12px; \
    } \
    \
    QLineEdit:focus { \
    border-color: #4CAF50; \
    }";

    ui->lineEdit_3->setStyleSheet(styleSheet5);


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
    Uart* uart = Uart::getInstance();
    QSerialPort* serialPort = uart->getSerialPort();
    QString message = ui->lineEdit_3->text();
    char delimiter1[2] = "*";
    QString style1 ="color: #097969;"; // Adresse de couleur pour le vert (green)

    //            dataTextBrowser->setStyleSheet(QString("color1: %1;").arg(color1));
    ui->textBrowser->setStyleSheet("QTextBrowser { background-color:#E5E4E2; }");

    ui->textBrowser->setStyleSheet(style1);
    ui->textBrowser->append(message);
    ui->textBrowser->append("\n");

    ui->textBrowser->append("Connection OK on USART3 :)");

    QFont font("Segoe UI", 10); // Police Arial avec une taille de 12 points
    font.setBold(true);

    ui->textBrowser->setFont(font);




}

void Uart::openLinkedInUrl()
{
    QDesktopServices::openUrl(QUrl("https://www.linkedin.com/company/actia-engineering-services"));
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



void Uart::openUrl(const QString& url)
{
QDesktopServices::openUrl(QUrl(url));
}
void Uart::openGmail()
{
    QString email = "contact@actia.com";
    QString subject = "Subject of the email";
    QString body = "Content of the email";

    QString mailToUrl = QString("mailto:%1?subject=%2&body=%3")
    .arg(email, QUrl::toPercentEncoding(subject), QUrl::toPercentEncoding(body));

    QProcess::startDetached("xdg-email", QStringList() << mailToUrl);

}

