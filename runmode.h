#ifndef RUNMODE_H
#define RUNMODE_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QRadioButton>
#include <QComboBox>
#include <QSpinBox>
#include "uart.h"
#include <QSerialPort>
#include <QDate>
#include <QTime>
#include <QFontDatabase>
#include<QFont>

namespace Ui {
class Runmode;
}

class Runmode : public QMainWindow
{
    Q_OBJECT

public:
    explicit Runmode(QWidget *parent = nullptr);
    ~Runmode();

private:
    Ui::Runmode *ui;


public slots :
    void returnDashboard();
    void addActionToMenu(QString menuItem, QString actionName);
    void sendRUNframe();



private slots :
    void showUART4Run(){
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

        auto textBrowser = new QTextBrowser(widget);
        auto label = new QLabel("Enter your message:", widget);

        auto lineEdit = new QLineEdit(widget);
        lineEdit->setPlaceholderText("Enter the data to write");

        auto button1 = new QPushButton("Send Message", widget);
        auto button2 = new QPushButton("Recieve Message", widget);

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

        Uart* uart = Uart::getInstance();
        QSerialPort* serialPort = uart->getSerialPort();


        // Create a vertical layout for the text browser, message input, and buttons
        auto layout = new QVBoxLayout(widget);
        layout->addWidget(label);
        layout->addWidget(lineEdit);

        layout->addWidget(textBrowser);

        auto buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(button1);
        buttonLayout->addWidget(button2);
        layout->addLayout(buttonLayout);

        // Set some styling properties for the text browser, message input, and buttons
//        lineEdit->setStyleSheet("QLineEdit { background-color: #ffffff; }");
//        button1->setStyleSheet("QPushButton { background-color: #33b5e5; color: white; }");
//        button2->setStyleSheet("QPushButton { background-color: #33b5e5; color: white; }");
        QFont font("Segoe UI", 10); // Police Arial avec une taille de 12 points

        label->setFont(font);
        label->setStyleSheet("font: bold 13px; color: #328930;");
        lineEdit->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
        button1->setStyleSheet(styleSheet2);
        button2->setStyleSheet(styleSheet2);
        textBrowser->setStyleSheet("QTextBrowser { background-color: #E3E0DF; }");
        font.setBold(true);
        textBrowser->setFont(font);



//        QByteArray buffer;
//        const int MAX_BUFFER_SIZE = 20; // Replace with your desired buffer size


//        QByteArray data = serialPort->readAll();
//        buffer.append(data);
////                QString message(data);
//        qDebug() << "Received message:" << data;

//        textBrowser->append(buffer);

        // Connect the "send message" button to a slot
        connect(button1, &QPushButton::clicked, [=]() {
            QString message = lineEdit->text();
            Uart* uart = Uart::getInstance();
            QSerialPort* serialPort = uart->getSerialPort();
            char delimiter1[2] = "*";
            char delim2[2]="+";


            QString style1 ="color: #097969;"; // Adresse de couleur pour le vert (green)

//            dataTextBrowser->setStyleSheet(QString("color1: %1;").arg(color1));

            textBrowser->setStyleSheet(style1);
            QByteArray packet1;

            QByteArray Message = message.toUtf8();
            packet1.append("0x2");
            packet1.append("|");

            packet1.append(Message);
            packet1.append("\t");


            packet1.append(delimiter1);

            packet1.append("\r");


            qDebug() << "packet1 :"<<  packet1 ;



            textBrowser->append(message);

            if (serialPort->isOpen() && serialPort->isWritable()) {
                qint64 bytesWritten = serialPort->write(packet1);
                if (bytesWritten == -1) {
                    qDebug() << "Error: Failed to write data to serial port";
                } else {
                    qDebug() << bytesWritten << "bytes written to serial port";
                }
            } else {
                qDebug() << "Error: Serial port is not open or not writable";
            }

            lineEdit->clear();
        });


        // Connect the "send message" button to a slot
        connect(button2, &QPushButton::clicked, [=]() {

            QString style = "color: #AA4A44;"; // Adresse de couleur pour le vert (green)

//            dataTextBrowser->setStyleSheet(QString("color1: %1;").arg(color1));

            textBrowser->setStyleSheet(style);

//            QString lastResponse = ""; // Initialiser lastResponse à une chaîne vide
//            QByteArray responseData;
//            while (serialPort->waitForReadyRead(100)) {
//            responseData.append(serialPort->readAll());


//            }

//                if (!responseData.isEmpty()) {
//                    lastResponse = QString::fromUtf8(responseData);

//                    qDebug() << "Received data:" << lastResponse;
//                    textBrowser->append(lastResponse);
//                } else {
//                    qDebug() << "No data received from serial port";
//                    textBrowser->append("No data received from serial port");
//                }

            QByteArray buffer;
            const int MAX_BUFFER_SIZE = 20; // Replace with your desired buffer size


            QByteArray data = serialPort->readAll();
            buffer.append(data);
//                QString message(data);
            qDebug() << "Received message:" << data;



            textBrowser->append(buffer);


        });


        // Set the layout for the widget
        widget->setLayout(layout);



    }

    void showUART5Run(){

        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

        Uart* uart = Uart::getInstance();
        QSerialPort* serialPort = uart->getSerialPort();


        auto textBrowser = new QTextBrowser(widget);
        auto label = new QLabel("Enter your message:", widget);

        auto lineEdit = new QLineEdit(widget);
        lineEdit->setPlaceholderText("Enter the data to write");

        auto button1 = new QPushButton("Send Message", widget);
        auto button2 = new QPushButton("Recieve Message", widget);

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


        // Create a vertical layout for the text browser, message input, and buttons
        auto layout = new QVBoxLayout(widget);
        layout->addWidget(label);
        layout->addWidget(lineEdit);

        layout->addWidget(textBrowser);

        auto buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(button1);
        buttonLayout->addWidget(button2);
        layout->addLayout(buttonLayout);

        // Set some styling properties for the text browser, message input, and buttons
//        lineEdit->setStyleSheet("QLineEdit { background-color: #ffffff; }");
//        button1->setStyleSheet("QPushButton { background-color: #33b5e5; color: white; }");
//        button2->setStyleSheet("QPushButton { background-color: #33b5e5; color: white; }");

        QFont font("Segoe UI", 10); // Police Arial avec une taille de 12 points
        label->setFont(font);
        label->setStyleSheet("font: bold 13px; color: #328930;");
        lineEdit->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
        button1->setStyleSheet(styleSheet2);
        button2->setStyleSheet(styleSheet2);
        textBrowser->setStyleSheet("QTextBrowser { background-color: #E3E0DF; }");
        font.setBold(true);
        textBrowser->setFont(font);


        // Connect the "send message" button to a slot
        connect(button1, &QPushButton::clicked, [=]() {
            QString message = lineEdit->text();
//            textBrowser->setStyleSheet("QTextBrowser { background-color: #E3E0DF; }");
            textBrowser->setTextColor(Qt::darkGreen);

            char delimiter1[2] = "*";


            QString style1 ="color: #097969;"; // Adresse de couleur pour le vert (green)

//            dataTextBrowser->setStyleSheet(QString("color1: %1;").arg(color1));

            textBrowser->setStyleSheet(style1);
            QByteArray packet1;

            QByteArray Message = message.toUtf8();
            packet1.append(Message);
            packet1.append(delimiter1);
            packet1.append("\r");


            qDebug() << "packet1 :"<<  packet1 ;

            textBrowser->append(message);
            QDate date = QDate::currentDate();
            QString dateString = date.toString();


            qDebug() << "date :  " <<dateString;

            QTime time = QTime::currentTime();


            QString timestring = time.toString();
            qDebug() << "time :  " <<timestring;


            textBrowser->append(message);

            if (serialPort->isOpen() && serialPort->isWritable()) {
                qint64 bytesWritten = serialPort->write(packet1);
                if (bytesWritten == -1) {
                    qDebug() << "Error: Failed to write data to serial port";
                } else {
                    qDebug() << bytesWritten << "bytes written to serial port";
                }
            } else {
                qDebug() << "Error: Serial port is not open or not writable";
            }


            lineEdit->clear();
        });


        // Connect the "send message" button to a slot
        connect(button2, &QPushButton::clicked, [=]() {

            QString style = "color: #AA4A44;"; // Adresse de couleur pour le vert (green)

//            dataTextBrowser->setStyleSheet(QString("color1: %1;").arg(color1));

            textBrowser->setStyleSheet(style);

//            QString lastResponse = ""; // Initialiser lastResponse à une chaîne vide
//            QByteArray responseData;
//            while (serialPort->waitForReadyRead(100)) {
//            responseData.append(serialPort->readAll());


//            }

//                if (!responseData.isEmpty()) {
//                    lastResponse = QString::fromUtf8(responseData);

//                    qDebug() << "Received data:" << lastResponse;
//                    textBrowser->append(lastResponse);
//                } else {
//                    qDebug() << "No data received from serial port";
//                    textBrowser->append("No data received from serial port");
//                }

            QByteArray buffer;
            const int MAX_BUFFER_SIZE = 20; // Replace with your desired buffer size


            QByteArray data = serialPort->readAll();
            buffer.append(data);
//                QString message(data);
            qDebug() << "Received message:" << data;



            textBrowser->append(buffer);
        });



        // Set the layout for the widget
        widget->setLayout(layout);

    }


    void showSPI1Run(){
        // Create a widget to hold the SPI IP functionality
        QWidget* spiWidget = new QWidget(this);
        setCentralWidget(spiWidget);

        Uart* uart = Uart::getInstance();
        QSerialPort* serialPort = uart->getSerialPort();



        // Create controls for sending and receiving data
        QLabel* sendDataLabel = new QLabel("Send Data:");
        QLineEdit* sendDataEdit = new QLineEdit;
        sendDataEdit->setPlaceholderText("Enter the data to write");

        QLabel* receivedDataLabel = new QLabel("Received Data:");
        QTextBrowser* receivedDataBrowser = new QTextBrowser;

        // Create buttons for sending and receiving data
        QPushButton* sendButton = new QPushButton("Send");
        QPushButton* receiveButton = new QPushButton("Receive");

        // Create a layout for the widget
        QVBoxLayout* layout = new QVBoxLayout(spiWidget);
        layout->addWidget(sendDataLabel);
        layout->addWidget(sendDataEdit);
        layout->addWidget(receivedDataLabel);
        layout->addWidget(receivedDataBrowser);
        auto buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(sendButton);
        buttonLayout->addWidget(receiveButton);
        layout->addLayout(buttonLayout);


        // Set some styling properties for the controls

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
        QFont font("Segoe UI", 10); // Police Arial avec une taille de 12 points
        sendDataLabel->setFont(font);
        receivedDataLabel->setFont(font);


        sendDataLabel->setStyleSheet("font: bold 13px; color: #328930;");
        receivedDataLabel->setStyleSheet("font: bold 13px; color: #328930;");
        // Create a label widget and set its font to Noto Sans
//        QFont font("Noto Sans");

        sendButton->setStyleSheet(styleSheet2);
        receiveButton->setStyleSheet(styleSheet2);

        receivedDataBrowser->setStyleSheet("QTextBrowser { background-color: #E3E0DF; }");
        font.setBold(true);
        receivedDataBrowser->setFont(font);




//        spiWidget->setStyleSheet("QWidget { background-color: #f0f0f0; }"
//                                 "QLineEdit, QTextBrowser { background-color: white; border: 1px solid #ccc; }"
//                                 "QPushButton { background-color: #33b5e5; color: white; }");


        // Connect the "send message" button to a slot
        connect(sendButton, &QPushButton::clicked, [=]() {
            QString message = sendDataEdit->text();
//            textBrowser->setStyleSheet("QTextBrowser { background-color: #E3E0DF; }");
            QString style1 ="color: #097969;"; // Adresse de couleur pour le vert (green)

//            dataTextBrowser->setStyleSheet(QString("color1: %1;").arg(color1));

            receivedDataBrowser->setStyleSheet(style1);

            char delimiter1[2] = "*";
//            char delimiter2[2] = "-";


            QByteArray packet1;

            QByteArray Message = message.toUtf8();
            packet1.append("0x3");
            packet1.append("/");

            packet1.append(Message);
            packet1.append("\t");



            packet1.append(delimiter1);

            packet1.append("\r");


            qDebug() << "packet1 :"<<  packet1 ;

            receivedDataBrowser->append(message);
            QDate date = QDate::currentDate();
            QString dateString = date.toString();


            qDebug() << "date :  " <<dateString;

            QTime time = QTime::currentTime();


            QString timestring = time.toString();
            qDebug() << "time :  " <<timestring;



            if (serialPort->isOpen() && serialPort->isWritable()) {
                qint64 bytesWritten = serialPort->write(packet1);
                if (bytesWritten == -1) {
                    qDebug() << "Error: Failed to write data to serial port";
                } else {
                    qDebug() << bytesWritten << "bytes written to serial port";
                }
            } else {
                qDebug() << "Error: Serial port is not open or not writable";
            }


            sendDataEdit->clear();
        });


        // Connect the "send message" button to a slot
        connect(receiveButton, &QPushButton::clicked, [=]() {

            QString style = "color: #AA4A44;"; // Adresse de couleur pour le vert (green)
            receivedDataBrowser->setStyleSheet(style);
            QByteArray buffer;
            const int MAX_BUFFER_SIZE = 20; // Replace with your desired buffer size


            QByteArray data = serialPort->readAll();
            buffer.append(data);
            qDebug() << "Received message:" << data;
            receivedDataBrowser->append(buffer);
        });

    }

    void showSPI2Run(){


        // Create a widget to hold the SPI IP functionality
        QWidget* spiWidget = new QWidget(this);
        setCentralWidget(spiWidget);

        // Create controls for configuring the SPI interface
        QLabel* DataOrderLabel = new QLabel("Data Order:");
//        QLineEdit* frequencyEdit = new QLineEdit("1000000");
        QComboBox* dataOrderCombo = new QComboBox;
        dataOrderCombo->addItem("MSB First");
        dataOrderCombo->addItem("LSB First");
        QLabel* BitOrderLabel = new QLabel("Bits Order:");

        QComboBox* bitOrderCombo = new QComboBox;
        bitOrderCombo->addItem("MSB First");
        bitOrderCombo->addItem("LSB First");

        // Create controls for sending and receiving data
        QLabel* sendDataLabel = new QLabel("Send Data:");
        QLineEdit* sendDataEdit = new QLineEdit;
        sendDataEdit->setPlaceholderText("Enter the data to write");

        QLabel* receivedDataLabel = new QLabel("Received Data:");
        QTextBrowser* receivedDataBrowser = new QTextBrowser;

        // Create buttons for sending and receiving data
        QPushButton* sendButton = new QPushButton("Send");
        QPushButton* receiveButton = new QPushButton("Receive");

        // Create a layout for the widget
        QVBoxLayout* layout = new QVBoxLayout(spiWidget);
        layout->addWidget(DataOrderLabel);
        layout->addWidget(dataOrderCombo);
        layout->addWidget(BitOrderLabel);

        layout->addWidget(bitOrderCombo);
        layout->addWidget(sendDataLabel);
        layout->addWidget(sendDataEdit);
        layout->addWidget(receivedDataLabel);
        layout->addWidget(receivedDataBrowser);
        auto buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(sendButton);
        buttonLayout->addWidget(receiveButton);
        layout->addLayout(buttonLayout);


        // Set some styling properties for the controls

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
        QFont font("Segoe UI", 10); // Police Arial avec une taille de 12 points
        sendDataLabel->setFont(font);
        receivedDataLabel->setFont(font);


        sendDataLabel->setStyleSheet("font: bold 13px; color: #328930;");
        receivedDataLabel->setStyleSheet("font: bold 13px; color: #328930;");
        // Create a label widget and set its font to Noto Sans
//        QFont font("Noto Sans");
        DataOrderLabel->setFont(font);
        BitOrderLabel->setFont(font);

        DataOrderLabel->setStyleSheet("font: bold 13px; color: #328930;");
        BitOrderLabel->setStyleSheet("font: bold 13px; color: #328930;");

        sendDataEdit->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

        dataOrderCombo->setStyleSheet("font-weight: bold; border: 1px solid 868482; color:#899499; background-color: white;");
        bitOrderCombo->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: #899499; background-color: white;");

        sendButton->setStyleSheet(styleSheet2);
        receiveButton->setStyleSheet(styleSheet2);

        receivedDataBrowser->setStyleSheet("QTextBrowser { background-color: #E3E0DF; }");
        font.setBold(true);
        receivedDataBrowser->setFont(font);




//        spiWidget->setStyleSheet("QWidget { background-color: #f0f0f0; }"
//                                 "QLineEdit, QTextBrowser { background-color: white; border: 1px solid #ccc; }"
//                                 "QPushButton { background-color: #33b5e5; color: white; }");

        // Connect the buttons to their corresponding functions
        connect(sendButton, &QPushButton::clicked, this, [sendDataEdit, receivedDataBrowser](){
            QString sendData = sendDataEdit->text();
            // Code to send data using the SPI interface
            QString receivedData = "Received data";
            QString style1 ="color: #097969;"; // Adresse de couleur pour le vert (green)

//            dataTextBrowser->setStyleSheet(QString("color1: %1;").arg(color1));

            receivedDataBrowser->setStyleSheet(style1);

            receivedDataBrowser->append(sendData);

            sendDataEdit->clear();

        });
        connect(receiveButton, &QPushButton::clicked, this, [receivedDataBrowser](){
            // Code to receive data using the SPI interface
            QString receivedData = "Showing data";
            QString style = "color: #AA4A44;"; // Adresse de couleur pour le vert (green)

//            dataTextBrowser->setStyleSheet(QString("color1: %1;").arg(color1));

            receivedDataBrowser->setStyleSheet(style);

            receivedDataBrowser->append(receivedData);
        });

    }

    void showI2C1Run(){
        // Create a widget for I2C
        // Create a widget for I2C
        QWidget* i2cWidget = new QWidget();
        setCentralWidget(i2cWidget);

        Uart* uart = Uart::getInstance();
        QSerialPort* serialPort = uart->getSerialPort();


        QVBoxLayout* i2cLayout = new QVBoxLayout(i2cWidget);

        // Create a QLabel to display the I2C device address
        QLabel* deviceAddressLabel = new QLabel("I2C Device Address:", i2cWidget);
        QLineEdit* deviceAddressLineEdit = new QLineEdit(i2cWidget);
        deviceAddressLineEdit->setPlaceholderText("Enter the device address");

        // Create a QComboBox to select the I2C register to access
        QLabel* registerLabel = new QLabel("Register:", i2cWidget);
        QComboBox* registerComboBox = new QComboBox(i2cWidget);
        registerComboBox->addItem("Register 1");
        registerComboBox->addItem("Register 2");
        registerComboBox->addItem("Register 3");

        // Create a QLineEdit to enter the data to write to the selected I2C register
        QLabel* dataLabel = new QLabel("Data:", i2cWidget);
        QLineEdit* dataLineEdit = new QLineEdit(i2cWidget);
        dataLineEdit->setPlaceholderText("Enter the data to write");

        // Create a QPushButton to initiate the I2C read operation
        QPushButton* readButton = new QPushButton("Read", i2cWidget);

        // Create a QPushButton to initiate the I2C write operation
        QPushButton* writeButton = new QPushButton("Write", i2cWidget);

        // Create a QTextBrowser to display the I2C read data
        QTextBrowser* dataTextBrowser = new QTextBrowser(i2cWidget);

        // Add the components to the layout
        i2cLayout->addWidget(deviceAddressLabel);
        i2cLayout->addWidget(deviceAddressLineEdit);
        i2cLayout->addWidget(registerLabel);
        i2cLayout->addWidget(registerComboBox);
        i2cLayout->addWidget(dataLabel);
        i2cLayout->addWidget(dataLineEdit);
        i2cLayout->addWidget(dataTextBrowser);
        auto buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(writeButton);
        buttonLayout->addWidget(readButton);
        i2cLayout->addLayout(buttonLayout);

        // adding some styles to the widget


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
//        QFont font("Segoe UI");

        readButton->setStyleSheet(styleSheet2);
        writeButton->setStyleSheet(styleSheet2);
        dataLineEdit->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
        dataTextBrowser->setStyleSheet("QTextBrowser { background-color: #E3E0DF; }");

        QFont font("Segoe UI", 10); // Police Arial avec une taille de 12 points
        font.setBold(true);
        dataTextBrowser->setFont(font);

        registerLabel->setStyleSheet("font: bold 13px; color: #328930;");
        dataLabel->setStyleSheet("font: bold 13px; color: #328930;");
        deviceAddressLabel->setStyleSheet("font: bold 13px; color: #328930;");
        registerComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color:#899499; background-color: white;");
        // Set the layout for the widget
        i2cWidget->setLayout(i2cLayout);

        // Connect the signals and slots
        QObject::connect(readButton, &QPushButton::clicked, [deviceAddressLineEdit, dataTextBrowser,serialPort]() {
            // Read data from the selected I2C register
            // Read data from the selected ADC channel
            QString deviceAddress = deviceAddressLineEdit->text();
            // Code to read data from ADC and update dataTextBrowser with the result

//            dataTextBrowser->setTextColor(Qt::darkRed);

            QString style = "color: #AA4A44;"; // Adresse de couleur pour le vert (green)

//            dataTextBrowser->setStyleSheet(QString("color1: %1;").arg(color1));

            dataTextBrowser->setStyleSheet(style);


            //            QString lastResponse = ""; // Initialiser lastResponse à une chaîne vide
            //            QByteArray responseData;
            //            while (serialPort->waitForReadyRead(100)) {
            //            responseData.append(serialPort->readAll());


//            }

//                if (!responseData.isEmpty()) {
//                    lastResponse = QString::fromUtf8(responseData);

//                    qDebug() << "Received data:" << lastResponse;
//                    textBrowser->append(lastResponse);
//                } else {
//                    qDebug() << "No data received from serial port";
//                    textBrowser->append("No data received from serial port");
//                }

            QByteArray buffer;
            const int MAX_BUFFER_SIZE = 20; // Replace with your desired buffer size


            QByteArray data = serialPort->readAll();
            QString datastring(data);
            buffer.append(data);
//                QString message(data);
            qDebug() << "Received message:" << datastring;



            dataTextBrowser->append(datastring);

            deviceAddressLineEdit->clear();


        });

        QObject::connect(writeButton, &QPushButton::clicked, [deviceAddressLineEdit, dataTextBrowser,serialPort]() {
            // Read data from the selected ADC channel
            QString message = deviceAddressLineEdit->text();
            char delimiter1[2] = "*";


//            dataTextBrowser->setTextColor(Qt::Key_Dead_Greek);

            QString style1 ="color: #097969;"; // Adresse de couleur pour le vert (green)

//            dataTextBrowser->setStyleSheet(QString("color: %1;").arg(color));

            dataTextBrowser->setStyleSheet(style1);


            QByteArray packet1;

            QByteArray Message = message.toUtf8();
            packet1.append(Message);
            packet1.append(delimiter1);
            packet1.append("\r");


            qDebug() << "packet1 :"<<  packet1 ;

            dataTextBrowser->append("Sensor address: \n");
            dataTextBrowser->append(message);

            if (serialPort->isOpen() && serialPort->isWritable()) {
                qint64 bytesWritten = serialPort->write(packet1);
                if (bytesWritten == -1) {
                    qDebug() << "Error: Failed to write data to serial port";
                } else {
                    qDebug() << bytesWritten << "bytes written to serial port";
                }
            } else {
                qDebug() << "Error: Serial port is not open or not writable";
            }

            deviceAddressLineEdit->clear();
            // Code to write data to I2C and update dataTextBrowser with the result
        });

    }

    void showADC1Run(){
        // Create a widget for ADC IP
        QWidget* adcWidget = new QWidget();
        setCentralWidget(adcWidget);

        Uart* uart = Uart::getInstance();
        QSerialPort* serialPort = uart->getSerialPort();


        QVBoxLayout* adcLayout = new QVBoxLayout(adcWidget);

        // Create a QLabel to display the ADC device address
        QLabel* deviceAddressLabel = new QLabel("ADC Device Address:", adcWidget);
        QLineEdit* deviceAddressLineEdit = new QLineEdit(adcWidget);
        deviceAddressLineEdit->setPlaceholderText("Enter the device address");

        // Create a QComboBox to select the ADC channel
        QLabel* channelLabel = new QLabel("Select Channel:", adcWidget);
        QComboBox* channelComboBox = new QComboBox(adcWidget);
        channelComboBox->addItem("Channel 1");
        channelComboBox->addItem("Channel 2");
        channelComboBox->addItem("Channel 3");

        // Create a QPushButton to initiate the ADC read operation
        QPushButton* readButton = new QPushButton("Read", adcWidget);
        QPushButton* writeButton = new QPushButton("Write", adcWidget);

        // Create a QTextBrowser to display the ADC read data
        QTextBrowser* dataTextBrowser = new QTextBrowser(adcWidget);

        // Add the components to the layout
        adcLayout->addWidget(deviceAddressLabel);
        adcLayout->addWidget(deviceAddressLineEdit);
        adcLayout->addWidget(channelLabel);
        adcLayout->addWidget(channelComboBox);
        adcLayout->addWidget(dataTextBrowser);
        auto buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(writeButton);
        buttonLayout->addWidget(readButton);
        adcLayout->addLayout(buttonLayout);


        // adding some styles
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
        QFont font("Segoe UI", 10); // Police Arial avec une taille de 12 points

        readButton->setStyleSheet(styleSheet2);
        writeButton->setStyleSheet(styleSheet2);
        deviceAddressLineEdit->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
        dataTextBrowser->setStyleSheet("QTextBrowser { background-color: #E3E0DF; }");
        channelLabel->setStyleSheet("font: bold 13px; color: #328930;");
        deviceAddressLabel->setStyleSheet("font: bold 13px; color: #328930;");
        channelComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color:#899499; background-color: white;");
        font.setBold(true);
        dataTextBrowser->setFont(font);


        // Set the layout for the widget
        adcWidget->setLayout(adcLayout);

        // Connect the signals and slots

        QObject::connect(writeButton, &QPushButton::clicked, [deviceAddressLineEdit, channelComboBox, dataTextBrowser,serialPort]() {
            // Read data from the selected ADC channel
            QString message = deviceAddressLineEdit->text();
            char delimiter1[2] = "*";


            QString style1 ="color: #097969;"; // Adresse de couleur pour le vert (green)

//            dataTextBrowser->setStyleSheet(QString("color1: %1;").arg(color1));

            dataTextBrowser->setStyleSheet(style1);
            QByteArray packet1;

            QByteArray Message = message.toUtf8();
            packet1.append(Message);
            packet1.append(delimiter1);
            packet1.append("\r");


            qDebug() << "packet1 :"<<  packet1 ;

            dataTextBrowser->append("analogique address: \n\r");




            dataTextBrowser->append(message);

            if (serialPort->isOpen() && serialPort->isWritable()) {
                qint64 bytesWritten = serialPort->write(packet1);
                if (bytesWritten == -1) {
                    qDebug() << "Error: Failed to write data to serial port";
                } else {
                    qDebug() << bytesWritten << "bytes written to serial port";
                }
            } else {
                qDebug() << "Error: Serial port is not open or not writable";
            }

            deviceAddressLineEdit->clear();


        });
        QObject::connect(readButton, &QPushButton::clicked, [deviceAddressLineEdit, channelComboBox, dataTextBrowser,serialPort]() {
            // Read data from the selected ADC channel
            QString deviceAddress = deviceAddressLineEdit->text();
            QString channel = channelComboBox->currentText();
            // Code to read data from ADC and update dataTextBrowser with the result

            QString style = "color: #AA4A44;"; // Adresse de couleur pour le vert (green)

//            dataTextBrowser->setStyleSheet(QString("color1: %1;").arg(color1));

            dataTextBrowser->setStyleSheet(style);



//            QString lastResponse = ""; // Initialiser lastResponse à une chaîne vide
//            QByteArray responseData;
//            while (serialPort->waitForReadyRead(100)) {
//            responseData.append(serialPort->readAll());


//            }

//                if (!responseData.isEmpty()) {
//                    lastResponse = QString::fromUtf8(responseData);

//                    qDebug() << "Received data:" << lastResponse;
//                    textBrowser->append(lastResponse);
//                } else {
//                    qDebug() << "No data received from serial port";
//                    textBrowser->append("No data received from serial port");
//                }

            QByteArray buffer;
            const int MAX_BUFFER_SIZE = 20; // Replace with your desired buffer size


            QByteArray data = serialPort->readAll();
            QString datastring(data);
            buffer.append(data);
//                QString message(data);
            qDebug() << "Received message:" << datastring;



            dataTextBrowser->append(datastring);

            deviceAddressLineEdit->clear();


        });

    }
    void showDACOUT1Run(){
        // Create a widget for DAC
        QWidget* dacWidget = new QWidget();
        setCentralWidget(dacWidget);

        Uart* uart = Uart::getInstance();
        QSerialPort* serialPort = uart->getSerialPort();


        QVBoxLayout* dacLayout = new QVBoxLayout(dacWidget);

        // Create a QLabel to display the DAC output voltage
        QLabel* voltageLabel = new QLabel("Digital Value :", dacWidget);
        QLineEdit* voltageLineEdit = new QLineEdit(dacWidget);
        voltageLineEdit->setPlaceholderText("Enter the digital value between 1 and 4096");
        voltageLineEdit->setMaxLength(4);

        // Create a QComboBox to select the DAC channel to output to
//        QLabel* channelLabel = new QLabel("Channel:", dacWidget);
//        QComboBox* channelComboBox = new QComboBox(dacWidget);
//        channelComboBox->addItem("Channel 1");
//        channelComboBox->addItem("Channel 2");

        // Create a QPushButton to initiate the DAC output
        QPushButton* writeButton = new QPushButton("Write", dacWidget);

        QPushButton* readButton = new QPushButton("Read", dacWidget);

        // Create a QTextBrowser to display the DAC output status
        QTextBrowser* statusTextBrowser = new QTextBrowser(dacWidget);

        // Add the components to the layout
        dacLayout->addWidget(voltageLabel);
        dacLayout->addWidget(voltageLineEdit);
//        dacLayout->addWidget(channelLabel);
//        dacLayout->addWidget(channelComboBox);
        dacLayout->addWidget(statusTextBrowser);

        auto buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(writeButton);
        buttonLayout->addWidget(readButton);
        dacLayout->addLayout(buttonLayout);



        // Set the layout for the widget
        dacWidget->setLayout(dacLayout);


            // adding some styles
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
            QFont font("Segoe UI", 10); // Police Arial avec une taille de 12 points

            readButton->setStyleSheet(styleSheet2);
            writeButton->setStyleSheet(styleSheet2);

            voltageLineEdit->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
            statusTextBrowser->setStyleSheet("QTextBrowser { background-color: #E3E0DF; }");
            voltageLabel->setStyleSheet("font: bold 13px; color: #328930;");
            font.setBold(true);
            statusTextBrowser->setFont(font);


        // Connect the signals and slots
            QObject::connect(readButton, &QPushButton::clicked, [voltageLineEdit, statusTextBrowser,serialPort]() {
                // Read data from the selected I2C register
                // Read data from the selected ADC channel
                QString deviceAddress = voltageLineEdit->text();
                // Code to read data from ADC and update dataTextBrowser with the result

                QString style = "color: #AA4A44;"; // Adresse de couleur pour le vert (green)

    //            dataTextBrowser->setStyleSheet(QString("color1: %1;").arg(color1));

                statusTextBrowser->setStyleSheet(style);



    //            QString lastResponse = ""; // Initialiser lastResponse à une chaîne vide
    //            QByteArray responseData;
    //            while (serialPort->waitForReadyRead(100)) {
    //            responseData.append(serialPort->readAll());


    //            }

    //                if (!responseData.isEmpty()) {
    //                    lastResponse = QString::fromUtf8(responseData);

    //                    qDebug() << "Received data:" << lastResponse;
    //                    textBrowser->append(lastResponse);
    //                } else {
    //                    qDebug() << "No data received from serial port";
    //                    textBrowser->append("No data received from serial port");
    //                }

                QByteArray buffer;
                const int MAX_BUFFER_SIZE = 20; // Replace with your desired buffer size


                QByteArray data = serialPort->readAll();
                QString datastring(data);
                buffer.append(data);
    //                QString message(data);
                qDebug() << "Received message:" << datastring;



                statusTextBrowser->append(datastring);

                voltageLineEdit->clear();


            });

            QObject::connect(writeButton, &QPushButton::clicked, [voltageLineEdit, statusTextBrowser,serialPort]() {
                // Read data from the selected ADC channel
                QString message = voltageLineEdit->text();
                char delimiter1[2] = "*";


                QString style1 ="color: #097969;"; // Adresse de couleur pour le vert (green)

    //            dataTextBrowser->setStyleSheet(QString("color1: %1;").arg(color1));

                statusTextBrowser->setStyleSheet(style1);
                QByteArray packet1;

                QByteArray Message = message.toUtf8();
                packet1.append(Message);
                packet1.append(delimiter1);
                packet1.append("\r");


                qDebug() << "packet1 :"<<  packet1 ;


                statusTextBrowser->append("Digital value (12 bit resolution) : \n\r");



                statusTextBrowser->append(message);

                if (serialPort->isOpen() && serialPort->isWritable()) {
                    qint64 bytesWritten = serialPort->write(packet1);
                    if (bytesWritten == -1) {
                        qDebug() << "Error: Failed to write data to serial port";
                    } else {
                        qDebug() << bytesWritten << "bytes written to serial port";
                    }
                } else {
                    qDebug() << "Error: Serial port is not open or not writable";
                }

                voltageLineEdit->clear();
                // Code to write data to I2C and update dataTextBrowser with the result
            });
    }

//    void showFrequencyMesureRun(){
//        // Create a widget for Timer
//        QWidget* timerWidget = new QWidget();
//        setCentralWidget(timerWidget);

//        QVBoxLayout* timerLayout = new QVBoxLayout(timerWidget);

//        // Create a QLabel to display the Timer mode
//        QLabel* modeLabel = new QLabel("Mode:", timerWidget);
//        QComboBox* modeComboBox = new QComboBox(timerWidget);
//        modeComboBox->addItem("Input Capture");
//        modeComboBox->addItem("Output Compare");

//        // Create a QLabel to display the Timer channel
//        QLabel* channelLabel = new QLabel("Channel:", timerWidget);
//        QComboBox* channelComboBox = new QComboBox(timerWidget);
//        channelComboBox->addItem("Channel 1");
//        channelComboBox->addItem("Channel 2");
//        channelComboBox->addItem("Channel 3");
//        channelComboBox->addItem("Channel 4");

//        // Create a QPushButton to start the Timer
//        QPushButton* startButton = new QPushButton("Start", timerWidget);

//        // Create a QPushButton to stop the Timer
//        QPushButton* stopButton = new QPushButton("Stop", timerWidget);

//        // Create a QLabel to display the frequency
//        QLabel* frequencyLabel = new QLabel("Frequency:", timerWidget);
//        QLineEdit* frequencyLineEdit = new QLineEdit(timerWidget);
//        frequencyLineEdit->setReadOnly(true);

//        // Add the components to the layout
//        timerLayout->addWidget(modeLabel);
//        timerLayout->addWidget(modeComboBox);
//        timerLayout->addWidget(channelLabel);
//        timerLayout->addWidget(channelComboBox);
//        timerLayout->addWidget(startButton);
//        timerLayout->addWidget(stopButton);
//        timerLayout->addWidget(frequencyLabel);
//        timerLayout->addWidget(frequencyLineEdit);

//        // Set the layout for the widget
//        timerWidget->setLayout(timerLayout);

//        // Connect the signals and slots
//        QObject::connect(startButton, &QPushButton::clicked, [modeComboBox, channelComboBox, frequencyLineEdit]() {
//            // Start the Timer in input capture mode with the selected channel
//            QString mode = modeComboBox->currentText();
//            QString channel = channelComboBox->currentText();
//            // Code to start the Timer and capture the frequency
//        });

//        QObject::connect(stopButton, &QPushButton::clicked, [frequencyLineEdit]() {
//            // Stop the Timer and display the captured frequency
//            // Code to stop the Timer and calculate and display the frequency in frequencyLineEdit
//        });


//    }

    void showFrequencyMesureRun(){
        // Create a widget for Timer
        QWidget* timerWidget = new QWidget();
        setCentralWidget(timerWidget);
        Uart* uart = Uart::getInstance();
        QSerialPort* serialPort = uart->getSerialPort();


        QVBoxLayout* timerLayout = new QVBoxLayout(timerWidget);

        // Create a QLabel to display the timer frequency
        QLabel* frequencyLabel = new QLabel("Timer Clock:", timerWidget);
        QLineEdit* frequencyLineEdit = new QLineEdit(timerWidget);
        frequencyLineEdit->setPlaceholderText("Enter the Timer Clock");

//        frequencyLineEdit->setReadOnly(true);

        // Create a QComboBox to select the Timer channel to use for input capture
//        QLabel* channelLabel = new QLabel("Channel:", timerWidget);
//        QComboBox* channelComboBox = new QComboBox(timerWidget);
//        channelComboBox->addItem("Channel 1");
//        channelComboBox->addItem("Channel 2");
//        channelComboBox->addItem("Channel 3");
//        channelComboBox->addItem("Channel 4");

        // Create a QPushButton to start the input capture operation
        QPushButton* startButton = new QPushButton("Send Data", timerWidget);
        QPushButton* stopButton = new QPushButton("Recieve Data", timerWidget);

        // Create a QTextBrowser to display the input capture data
        QTextBrowser* dataTextBrowser = new QTextBrowser(timerWidget);

        // Add the components to the layout
        timerLayout->addWidget(frequencyLabel);
        timerLayout->addWidget(frequencyLineEdit);
//        timerLayout->addWidget(channelLabel);
//        timerLayout->addWidget(channelComboBox);

        timerLayout->addWidget(dataTextBrowser);

        auto buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(startButton);
        buttonLayout->addWidget(stopButton);
        timerLayout->addLayout(buttonLayout);


        // Set the layout for the widget
        timerWidget->setLayout(timerLayout);



        // adding some styles
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
        QFont font("Segoe UI", 10); // Police Arial avec une taille de 12 points

        startButton->setStyleSheet(styleSheet2);
        stopButton->setStyleSheet(styleSheet2);

        frequencyLineEdit->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
        dataTextBrowser->setStyleSheet("QTextBrowser { background-color: #E3E0DF; }");
        frequencyLabel->setStyleSheet("font: bold 13px; color: #328930;");

        font.setBold(true);
        dataTextBrowser->setFont(font);


        // Connect the signals and slots
        QObject::connect(startButton, &QPushButton::clicked, [frequencyLineEdit, dataTextBrowser,serialPort]() {
            // Read data from the selected ADC channel
            QString message = frequencyLineEdit->text();
            char delimiter1[2] = "*";


            QString style1 ="color: #097969;"; // Adresse de couleur pour le vert (green)

//            dataTextBrowser->setStyleSheet(QString("color1: %1;").arg(color1));

            dataTextBrowser->setStyleSheet(style1);
            QByteArray packet1;

            QByteArray Message = message.toUtf8();
            packet1.append(Message);
            packet1.append(delimiter1);
            packet1.append("\r");


            qDebug() << "packet1 :"<<  packet1 ;


            dataTextBrowser->append("Timer Clock : \n\r");



            dataTextBrowser->append(message);

            if (serialPort->isOpen() && serialPort->isWritable()) {
                qint64 bytesWritten = serialPort->write(packet1);
                if (bytesWritten == -1) {
                    qDebug() << "Error: Failed to write data to serial port";
                } else {
                    qDebug() << bytesWritten << "bytes written to serial port";
                }
            } else {
                qDebug() << "Error: Serial port is not open or not writable";
            }

            frequencyLineEdit->clear();
            // Code to write data to I2C and update dataTextBrowser with the result




        });

        QObject::connect(stopButton, &QPushButton::clicked, [frequencyLineEdit, dataTextBrowser , serialPort]() {
            // Start the input capture operation on the selected Timer channel
//            QString frequency = frequencyLineEdit->text();
            // Code to start input capture and update frequencyLineEdit and dataTextBrowser with the result

            // Read data from the selected I2C register
            // Read data from the selected ADC channel
            QString deviceAddress = frequencyLineEdit->text();
            // Code to read data from ADC and update dataTextBrowser with the result

            QString style = "color: #AA4A44;"; // Adresse de couleur pour le vert (green)

//            dataTextBrowser->setStyleSheet(QString("color1: %1;").arg(color1));

            dataTextBrowser->setStyleSheet(style);



//            QString lastResponse = ""; // Initialiser lastResponse à une chaîne vide
//            QByteArray responseData;
//            while (serialPort->waitForReadyRead(100)) {
//            responseData.append(serialPort->readAll());


//            }

//                if (!responseData.isEmpty()) {
//                    lastResponse = QString::fromUtf8(responseData);

//                    qDebug() << "Received data:" << lastResponse;
//                    textBrowser->append(lastResponse);
//                } else {
//                    qDebug() << "No data received from serial port";
//                    textBrowser->append("No data received from serial port");
//                }

            QByteArray buffer;
            const int MAX_BUFFER_SIZE = 20; // Replace with your desired buffer size


            QByteArray data = serialPort->readAll();
            QString datastring(data);
            buffer.append(data);
//                QString message(data);
            qDebug() << "Received message:" << datastring;



            dataTextBrowser->append(datastring);

            frequencyLineEdit->clear();


        });

    }

//    void showGPIOOUTPUTRun(){
//        // Create a widget for GPIO output pin
//        QWidget* gpioOutputWidget = new QWidget();
//        setCentralWidget(gpioOutputWidget);

//        QVBoxLayout* gpioOutputLayout = new QVBoxLayout(gpioOutputWidget);

//        // Create a QLabel to display the GPIO pin number
//        QLabel* pinNumberLabel = new QLabel("Pin Number:", gpioOutputWidget);
//        QLineEdit* pinNumberLineEdit = new QLineEdit(gpioOutputWidget);
//        pinNumberLineEdit->setPlaceholderText("Enter the GPIO pin number");

//        // Create a QComboBox to select the output value
//        QLabel* valueLabel = new QLabel("Value:", gpioOutputWidget);
//        QComboBox* valueComboBox = new QComboBox(gpioOutputWidget);
//        valueComboBox->addItem("High");
//        valueComboBox->addItem("Low");

//        // Create a QPushButton to set the output value
//        QPushButton* setValueButton = new QPushButton("Set Value", gpioOutputWidget);

//        // Add the components to the layout
//        gpioOutputLayout->addWidget(pinNumberLabel);
//        gpioOutputLayout->addWidget(pinNumberLineEdit);
//        gpioOutputLayout->addWidget(valueLabel);
//        gpioOutputLayout->addWidget(valueComboBox);
//        gpioOutputLayout->addWidget(setValueButton);

//        // Set the layout for the widget
//        gpioOutputWidget->setLayout(gpioOutputLayout);

//        // Connect the signals and slots
//        QObject::connect(setValueButton, &QPushButton::clicked, [pinNumberLineEdit, valueComboBox]() {
//            // Set the output value of the selected GPIO pin
//            QString pinNumber = pinNumberLineEdit->text();
//            QString value = valueComboBox->currentText();
//            // Code to set the output value of the selected GPIO pin
//        });

//    }
        void showGPIOOUTPUTRun(){
            // Create a widget for GPIO Output
            QWidget* gpioOutputWidget = new QWidget();
                    setCentralWidget(gpioOutputWidget);

            QVBoxLayout* gpioOutputLayout = new QVBoxLayout(gpioOutputWidget);

            // Create a QLabel to display the status of the LED
            QLabel* ledStatusLabel = new QLabel("LED Status: OFF", gpioOutputWidget);

            // Create a QPushButton to turn ON the LED
            QPushButton* ledOnButton = new QPushButton("Turn ON LED", gpioOutputWidget);

            // Create a QPushButton to turn OFF the LED
            QPushButton* ledOffButton = new QPushButton("Turn OFF LED", gpioOutputWidget);

            // Create a QLabel to display the status of the relay
            QLabel* relayStatusLabel = new QLabel("Relay Status: OFF", gpioOutputWidget);

            // Create a QPushButton to turn ON the relay
            QPushButton* relayOnButton = new QPushButton("Turn ON Relay", gpioOutputWidget);

            // Create a QPushButton to turn OFF the relay
            QPushButton* relayOffButton = new QPushButton("Turn OFF Relay", gpioOutputWidget);


            // Create a QLabel to display the status of the relay
            QLabel* MotorStatusLabel = new QLabel("Motor Status: OFF", gpioOutputWidget);

            // Create a QPushButton to turn ON the relay
            QPushButton* MotorOnButton = new QPushButton("Power ON Motor", gpioOutputWidget);

            // Create a QPushButton to turn OFF the relay
            QPushButton* MotorOffButton = new QPushButton("Turn OFF Motor", gpioOutputWidget);

            // Add the components to the layout
            gpioOutputLayout->addWidget(ledStatusLabel);
            auto buttonLayout = new QHBoxLayout();
            buttonLayout->addWidget(ledOnButton);
            buttonLayout->addWidget(ledOffButton);
            gpioOutputLayout->addLayout(buttonLayout);

            gpioOutputLayout->addWidget(relayStatusLabel);
            auto buttonLayout1 = new QHBoxLayout();
            buttonLayout1->addWidget(relayOnButton);
            buttonLayout1->addWidget(relayOffButton);
            gpioOutputLayout->addLayout(buttonLayout1);

            gpioOutputLayout->addWidget(MotorStatusLabel);
            auto buttonLayout2 = new QHBoxLayout();
            buttonLayout2->addWidget(MotorOnButton);
            buttonLayout2->addWidget(MotorOffButton);
            gpioOutputLayout->addLayout(buttonLayout2);



            // Set the layout for the widget
            gpioOutputWidget->setLayout(gpioOutputLayout);


            // adding some styles
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
            QFont font("Segoe UI");

            ledOnButton->setStyleSheet(styleSheet2);
            ledOffButton->setStyleSheet(styleSheet2);
            relayOnButton->setStyleSheet(styleSheet2);
            relayOffButton->setStyleSheet(styleSheet2);
            MotorOnButton->setStyleSheet(styleSheet2);
            MotorOffButton->setStyleSheet(styleSheet2);

            ledStatusLabel->setStyleSheet("font: bold 16px; color: #328930;");
            relayStatusLabel->setStyleSheet("font: bold 16px; color: #328930;");

            MotorStatusLabel->setStyleSheet("font: bold 16px; color: #328930;");




            // Connect the signals and slots for LED control
            QObject::connect(ledOnButton, &QPushButton::clicked, [ledStatusLabel]() {
                // Code to turn ON the LED
                // For example, set GPIO pin to HIGH
                ledStatusLabel->setText("LED Status: ON");

                Uart* uart = Uart::getInstance();
                QSerialPort* serialPort = uart->getSerialPort();
                char delimiter1[2] = "*";


                QByteArray packet1;

                packet1.append("ON");
                packet1.append(delimiter1);
                packet1.append("\r");


                qDebug() << "packet1 :"<<  packet1 ;




                if (serialPort->isOpen() && serialPort->isWritable()) {
                    qint64 bytesWritten = serialPort->write(packet1);
                    if (bytesWritten == -1) {
                        qDebug() << "Error: Failed to write data to serial port";
                    } else {
                        qDebug() << bytesWritten << "bytes written to serial port";
                    }
                } else {
                    qDebug() << "Error: Serial port is not open or not writable";
                }




            });

            QObject::connect(ledOffButton, &QPushButton::clicked, [ledStatusLabel]() {
                // Code to turn OFF the LED
                // For example, set GPIO pin to LOW
                ledStatusLabel->setText("LED Status: OFF");

                Uart* uart = Uart::getInstance();
                QSerialPort* serialPort = uart->getSerialPort();
                char delimiter1[2] = "*";


                QByteArray packet1;

                packet1.append("OFF");
                packet1.append(delimiter1);
                packet1.append("\r");


                qDebug() << "packet1 :"<<  packet1 ;




                if (serialPort->isOpen() && serialPort->isWritable()) {
                    qint64 bytesWritten = serialPort->write(packet1);
                    if (bytesWritten == -1) {
                        qDebug() << "Error: Failed to write data to serial port";
                    } else {
                        qDebug() << bytesWritten << "bytes written to serial port";
                    }
                } else {
                    qDebug() << "Error: Serial port is not open or not writable";
                }

            });

            // Connect the signals and slots for relay control
            QObject::connect(relayOnButton, &QPushButton::clicked, [relayStatusLabel]() {
                // Code to turn ON the relay
                // For example, set GPIO pin to HIGH
                relayStatusLabel->setText("Relay Status: ON");
            });

            QObject::connect(relayOffButton, &QPushButton::clicked, [relayStatusLabel]() {
                // Code to turn OFF the relay
                // For example, set GPIO pin to LOW
                relayStatusLabel->setText("Relay Status: OFF");
            });


            // Connect the signals and slots for Motor control
            QObject::connect(MotorOnButton, &QPushButton::clicked, [MotorStatusLabel]() {
                // Code to turn ON the relay
                // For example, set GPIO pin to HIGH
                MotorStatusLabel->setText("Motor Status: ON");
            });

            QObject::connect(MotorOffButton, &QPushButton::clicked, [MotorStatusLabel]() {
                // Code to turn OFF the relay
                // For example, set GPIO pin to LOW
                MotorStatusLabel->setText("Motor Status: OFF");
            });

        }


};

#endif // RUNMODE_H
