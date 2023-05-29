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

    QWidget* Starting = new QWidget(this);


    QImage backgroundImage("C:/Users/nawledbr/Documents/Serial_Port_COM/startingapplication.png");

    // Création d'un label pour afficher l'image
//    QWidget window;

    QLabel* backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap::fromImage(backgroundImage));

    // Configuration de la position et de la taille du label d'arrière-plan
    backgroundLabel->setGeometry(0, 0, width(), height());
    backgroundLabel->setScaledContents(true); // Adapter l'image à la taille du label

    // Assurez-vous que le label d'arrière-plan est en dessous des autres widgets
    backgroundLabel->lower();

    // Create buttons for sending and receiving data
    QPushButton* receiveButton = new QPushButton("START APPLICATION");

    // Create a layout for the widget
    QVBoxLayout* layout = new QVBoxLayout(Starting);
    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(receiveButton);
//    layout->addLayout(buttonLayout);

    layout->addStretch();

    // Add the horizontal layout with the buttons to the bottom of the vertical layout
    layout->addLayout(buttonLayout);

    layout->setAlignment(Starting, Qt::AlignCenter);


//    layout->setAlignment(Qt::AlignCenter);

    // Set the layout of the window
    setLayout(layout);


    // Add a stretch to push the buttons to the bottom of the vertical layout

//    titleLabel->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");
//                iconLabel->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");


    QString styleSheet2 =
        "QPushButton {"
        "    background-color: white;"
        "    border: none;"
        "    color: #0000cd;"
        "    padding: 3px 3px;"
        "    text-align: center;"
        "    text-decoration: none;"
        "    font-size: 16px;"
        "    margin: 4px 2px;"
        "}"
        ""
        "QPushButton:hover {"
        "    background-color: #32CD32			;"
        "}";


    receiveButton->setStyleSheet(styleSheet2);


//    titleLabel->setAlignment(Qt::AlignCenter);


    // Add the title label and the icon to the main layout
    Starting->resize(400,300);

    connect(receiveButton, &QPushButton::clicked, [=]() {
        MainWindow *LoadingScreen = new MainWindow;
        LoadingScreen->show();
        this->hide();
        //qApp->processEvents(QEventLoop::EventLoopExec);
        LoadingScreen->start_Loading();
        //passer à l'ecran uart

        //dashboard->show();
        Uartscreen->show();
        this->hide();


    });
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

