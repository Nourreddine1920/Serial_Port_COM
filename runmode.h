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
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

        auto textBrowser = new QTextBrowser(widget);
        auto label = new QLabel("Send SPI Command:", widget);
        auto lineEdit = new QLineEdit(widget);
        auto button1 = new QPushButton("Send", widget);
        auto modeLabel = new QLabel("Mode:", widget);
        auto modeRadio1 = new QRadioButton("Mode 0", widget);
        auto modeRadio2 = new QRadioButton("Mode 1", widget);
        auto modeRadio3 = new QRadioButton("Mode 2", widget);
        auto modeRadio4 = new QRadioButton("Mode 3", widget);
        auto csCheckBox = new QCheckBox("Chip Select", widget);
        auto otherPinCheckBox = new QCheckBox("Other Pin", widget);

        // Create a vertical layout for the text browser, message input, and buttons
        auto layout = new QVBoxLayout(widget);
        layout->addWidget(textBrowser);
        layout->addWidget(label);
        layout->addWidget(lineEdit);

        auto buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(button1);
        layout->addLayout(buttonLayout);

        auto optionsLayout = new QGridLayout();
        optionsLayout->addWidget(modeLabel, 0, 0);
        optionsLayout->addWidget(modeRadio1, 0, 1);
        optionsLayout->addWidget(modeRadio2, 0, 2);
        optionsLayout->addWidget(modeRadio3, 1, 1);
        optionsLayout->addWidget(modeRadio4, 1, 2);
        optionsLayout->addWidget(csCheckBox, 2, 0);
        optionsLayout->addWidget(otherPinCheckBox, 2, 1);
        layout->addLayout(optionsLayout);

        // Set some styling properties for the text browser, message input, and buttons
        textBrowser->setStyleSheet("QTextBrowser { background-color: #f0f0f0; }");
        lineEdit->setStyleSheet("QLineEdit { background-color: #ffffff; }");
        button1->setStyleSheet("QPushButton { background-color: #33b5e5; color: white; }");

        // Connect the "send message" button to a slot
        connect(button1, &QPushButton::clicked, [=]() {
            QString message = lineEdit->text();
            textBrowser->append(message);
            lineEdit->clear();
        });

        // Set the layout for the widget
        widget->setLayout(layout);

    }

};

#endif // RUNMODE_H
