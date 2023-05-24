#include "starting_screen.h"
#include "ui_starting_screen.h"
#include "mainwindow.h"
#include"uart.h"

#include"dashboard.h"

starting_screen::starting_screen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::starting_screen)
{
    ui->setupUi(this);
    // Initialize uart_connection object



//    QImage backgroundImage("C:/Users/nawledbr/Documents/Serial_Port_COM/xcubellll.png");

//    // Création d'un label pour afficher l'image
////    QWidget window;

//    QLabel* backgroundLabel = new QLabel(this);
//    backgroundLabel->setPixmap(QPixmap::fromImage(backgroundImage));

//    // Configuration de la position et de la taille du label d'arrière-plan
//    backgroundLabel->setGeometry(0, 0, width(), height());
//    backgroundLabel->setScaledContents(true); // Adapter l'image à la taille du label

//    // Assurez-vous que le label d'arrière-plan est en dessous des autres widgets
//    backgroundLabel->lower();

    QString styleSheet =
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    border: none;"
        "    color: white;"
        "    padding: 15px 32px;"
        "    text-align: center;"
        "    text-decoration: none;"
        "    font-size: 20px;"
        "    margin: 4px 2px;"
        "    border-radius: 10px;"
        "}"
        ""
        "QPushButton:hover {"
        "    background-color: #3e8e41;"
        "}";
    ui->pushButton_startapplication->setStyleSheet(styleSheet);
    QWidget::setWindowTitle("Welcome Page");


    setFixedSize(width(), height());
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

