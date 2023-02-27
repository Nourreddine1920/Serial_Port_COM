#include "starting_screen.h"
#include "ui_starting_screen.h"
#include "mainwindow.h"
#include"uart.h"

starting_screen::starting_screen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::starting_screen)
{
    ui->setupUi(this);
    // Initialize uart_connection object
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
    //qApp->processEvents(QEventLoop::EventLoopExec);
    LoadingScreen->start_Loading();
    //passer à l'ecran uart

    Uartscreen->show();
    this->hide();

}

