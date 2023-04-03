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


        label->setStyleSheet("font: bold 15px; color: black;");
        lineEdit->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
        button1->setStyleSheet(styleSheet2);
        button2->setStyleSheet(styleSheet2);


        // Connect the "send message" button to a slot
        connect(button1, &QPushButton::clicked, [=]() {
            QString message = lineEdit->text();
            textBrowser->setStyleSheet("QTextBrowser { background-color: #E3E0DF; }");
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
        layout->addWidget(sendButton);
        layout->addWidget(receiveButton);

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


        sendDataLabel->setStyleSheet("font: bold 13px; color: black;");
        receivedDataLabel->setStyleSheet("font: bold 13px; color: black;");
        // Create a label widget and set its font to Noto Sans
//        QFont font("Noto Sans");
        DataOrderLabel->setFont(font);
        BitOrderLabel->setFont(font);

        DataOrderLabel->setStyleSheet("font: bold 13px; color: black;");
        BitOrderLabel->setStyleSheet("font: bold 13px; color: black;");

        sendDataEdit->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

        dataOrderCombo->setStyleSheet("font-weight: bold; border: 1px solid 868482; color:#899499; background-color: white;");
        bitOrderCombo->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: #899499; background-color: white;");

        sendButton->setStyleSheet(styleSheet2);
        receiveButton->setStyleSheet(styleSheet2);

        receivedDataBrowser->setStyleSheet("QTextBrowser { background-color: #E3E0DF; }");
        receivedDataBrowser->setTextColor(Qt::darkGreen);




//        spiWidget->setStyleSheet("QWidget { background-color: #f0f0f0; }"
//                                 "QLineEdit, QTextBrowser { background-color: white; border: 1px solid #ccc; }"
//                                 "QPushButton { background-color: #33b5e5; color: white; }");

        // Connect the buttons to their corresponding functions
        connect(sendButton, &QPushButton::clicked, this, [sendDataEdit, receivedDataBrowser](){
            QString sendData = sendDataEdit->text();
            // Code to send data using the SPI interface
            QString receivedData = "Received data";
            receivedDataBrowser->append(sendData);
        });
        connect(receiveButton, &QPushButton::clicked, this, [receivedDataBrowser](){
            // Code to receive data using the SPI interface
            QString receivedData = "Showing data";
            receivedDataBrowser->append(receivedData);
        });

    }

};

#endif // RUNMODE_H
