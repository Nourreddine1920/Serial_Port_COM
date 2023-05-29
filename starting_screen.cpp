#include "starting_screen.h"
#include "ui_starting_screen.h"
#include "mainwindow.h"
#include"uart.h"
#include <QPushButton>

#include"dashboard.h"

starting_screen::starting_screen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::starting_screen)
{
    ui->setupUi(this);
    // Initialize uart_connection object

//    QWidget* Starting = new QWidget(this);

    QImage backgroundImage("C:/Users/nawledbr/Documents/Serial_Port_COM/startingapplication.png");

    QLabel* backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap::fromImage(backgroundImage));
    backgroundLabel->setGeometry(0, 0, width(), height());
    backgroundLabel->setScaledContents(true);
    backgroundLabel->lower();

//    QPushButton* receiveButton = new QPushButton("START APPLICATION");

//    QVBoxLayout* layout = new QVBoxLayout(Starting);
//    auto buttonLayout = new QHBoxLayout();
//    buttonLayout->addStretch(); // Ajouter un espace flexible avant le bouton
//    buttonLayout->addWidget(receiveButton);
//    buttonLayout->addStretch(); // Ajouter un autre espace flexible après le bouton

//    layout->addStretch();
//    layout->addLayout(buttonLayout);
//    layout->setAlignment(buttonLayout, Qt::AlignCenter);

    QString styleSheet2 =
    "QPushButton {"
    " background-color: #F9F6EE;"
    " border: none;"
    " color: #36454F;"
    " padding: 3px 3px;"
    " text-align: center;"
    " text-decoration: none;"
    " font-size: 20px;"
    " margin: 4px 2px;"
    "}"
    ""
    "QPushButton:hover {"
    " background-color: #32CD32;"
    "}";

//    receiveButton->setStyleSheet(styleSheet2);
    ui->pushButton_startapplication->setStyleSheet(styleSheet2);

//    Starting->setLayout(layout);
//    Starting->resize(400, 300);

//    connect(receiveButton, &QPushButton::clicked, [=]() {
//        MainWindow *LoadingScreen = new MainWindow;
//        LoadingScreen->show();
//        this->hide();
//        //qApp->processEvents(QEventLoop::EventLoopExec);
//        LoadingScreen->start_Loading();
//        //passer à l'ecran uart

//        //dashboard->show();
//        Uartscreen->show();
//        this->hide();


//    });
    Uartscreen=new Uart(this);
}

starting_screen::~starting_screen()
{
    delete ui;
}

void starting_screen::on_pushButton_startapplication_clicked()
{

    MainWindow *LoadingScreen = new MainWindow;
    LoadingScreen->show();
    this->hide();
    //qApp->processEvents(QEventLoop::EventLoopExec);
    LoadingScreen->start_Loading();
    //passer à l'ecran uart

    //dashboard->show();
    Uartscreen->show();
    this->hide();



//    Dashboard* dashboard = new Dashboard();
//    dashboard->show();
//    this->hide();


}

