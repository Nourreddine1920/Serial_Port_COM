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


private slots :
    void showUART4Run(){
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

        auto textBrowser = new QTextBrowser(widget);
        auto label = new QLabel("Enter your message:", widget);
        auto lineEdit = new QLineEdit(widget);
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
        layout->addWidget(textBrowser);
        layout->addWidget(label);
        layout->addWidget(lineEdit);

        auto buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(button1);
        buttonLayout->addWidget(button2);
        layout->addLayout(buttonLayout);

        // Set some styling properties for the text browser, message input, and buttons
//        lineEdit->setStyleSheet("QLineEdit { background-color: #ffffff; }");
//        button1->setStyleSheet("QPushButton { background-color: #33b5e5; color: white; }");
//        button2->setStyleSheet("QPushButton { background-color: #33b5e5; color: white; }");

        QFont font("Segoe UI");
        label->setFont(font);
        label->setStyleSheet("font: bold 13px; color: #328930;");
        lineEdit->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
        button1->setStyleSheet(styleSheet2);
        button2->setStyleSheet(styleSheet2);
        textBrowser->setStyleSheet("QTextBrowser { background-color: #E3E0DF; }");


        // Connect the "send message" button to a slot
        connect(button1, &QPushButton::clicked, [=]() {
            QString message = lineEdit->text();
//            textBrowser->setStyleSheet("QTextBrowser { background-color: #E3E0DF; }");
            textBrowser->setTextColor(Qt::darkGreen);

            textBrowser->append(message);
            lineEdit->clear();
        });

        // Set the layout for the widget
        widget->setLayout(layout);



    }


    void showSPI1Run(){
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
        QFont font("Segoe UI");
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




//        spiWidget->setStyleSheet("QWidget { background-color: #f0f0f0; }"
//                                 "QLineEdit, QTextBrowser { background-color: white; border: 1px solid #ccc; }"
//                                 "QPushButton { background-color: #33b5e5; color: white; }");

        // Connect the buttons to their corresponding functions
        connect(sendButton, &QPushButton::clicked, this, [sendDataEdit, receivedDataBrowser](){
            QString sendData = sendDataEdit->text();
            // Code to send data using the SPI interface
            QString receivedData = "Received data";
            receivedDataBrowser->setTextColor(Qt::BlankCursor);

            receivedDataBrowser->append(sendData);
        });
        connect(receiveButton, &QPushButton::clicked, this, [receivedDataBrowser](){
            // Code to receive data using the SPI interface
            QString receivedData = "Showing data";
            receivedDataBrowser->setTextColor(Qt::darkRed);

            receivedDataBrowser->append(receivedData);
        });

    }

    void showI2C1Run(){
        // Create a widget for I2C
        // Create a widget for I2C
        QWidget* i2cWidget = new QWidget();
        setCentralWidget(i2cWidget);

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
        buttonLayout->addWidget(readButton);
        buttonLayout->addWidget(writeButton);
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
        QFont font("Segoe UI");

        readButton->setStyleSheet(styleSheet2);
        writeButton->setStyleSheet(styleSheet2);
        dataLineEdit->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
        dataTextBrowser->setStyleSheet("QTextBrowser { background-color: #E3E0DF; }");
        registerLabel->setStyleSheet("font: bold 13px; color: #328930;");
        dataLabel->setStyleSheet("font: bold 13px; color: #328930;");
        deviceAddressLabel->setStyleSheet("font: bold 13px; color: #328930;");
        registerComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color:#899499; background-color: white;");
        // Set the layout for the widget
        i2cWidget->setLayout(i2cLayout);

        // Connect the signals and slots
        QObject::connect(readButton, &QPushButton::clicked, [deviceAddressLineEdit, registerComboBox, dataTextBrowser]() {
            // Read data from the selected I2C register
            QString deviceAddress = deviceAddressLineEdit->text();
            QString registerName = registerComboBox->currentText();
            // Code to read data from I2C and update dataTextBrowser with the result

            dataTextBrowser->setTextColor(Qt::darkRed);


            dataTextBrowser->append("No Data Coming");

        });

        QObject::connect(writeButton, &QPushButton::clicked, [deviceAddressLineEdit, registerComboBox, dataLineEdit, dataTextBrowser]() {
            // Write data to the selected I2C register
            QString deviceAddress = deviceAddressLineEdit->text();
            QString registerName = registerComboBox->currentText();
            QString data = dataLineEdit->text();

            dataTextBrowser->setTextColor(Qt::BlankCursor);


            dataTextBrowser->append(deviceAddress);
            dataTextBrowser->append(registerName);
            dataTextBrowser->append(data);

            // Code to write data to I2C and update dataTextBrowser with the result
        });

    }

    void showADC1Run(){
        // Create a widget for ADC IP
        QWidget* adcWidget = new QWidget();
        setCentralWidget(adcWidget);

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

        // Create a QTextBrowser to display the ADC read data
        QTextBrowser* dataTextBrowser = new QTextBrowser(adcWidget);

        // Add the components to the layout
        adcLayout->addWidget(deviceAddressLabel);
        adcLayout->addWidget(deviceAddressLineEdit);
        adcLayout->addWidget(channelLabel);
        adcLayout->addWidget(channelComboBox);
        adcLayout->addWidget(dataTextBrowser);
        adcLayout->addWidget(readButton);

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

        readButton->setStyleSheet(styleSheet2);
        deviceAddressLineEdit->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
        dataTextBrowser->setStyleSheet("QTextBrowser { background-color: #E3E0DF; }");
        channelLabel->setStyleSheet("font: bold 13px; color: #328930;");
        deviceAddressLabel->setStyleSheet("font: bold 13px; color: #328930;");
        channelComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color:#899499; background-color: white;");


        // Set the layout for the widget
        adcWidget->setLayout(adcLayout);

        // Connect the signals and slots
        QObject::connect(readButton, &QPushButton::clicked, [deviceAddressLineEdit, channelComboBox, dataTextBrowser]() {
            // Read data from the selected ADC channel
            QString deviceAddress = deviceAddressLineEdit->text();
            QString channel = channelComboBox->currentText();
            // Code to read data from ADC and update dataTextBrowser with the result

            dataTextBrowser->setTextColor(Qt::darkRed);


            dataTextBrowser->append("No Data Coming");

        });

    }

};

#endif // RUNMODE_H
