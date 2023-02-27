#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    QWidget::setWindowTitle("Welcome Page");


    setFixedSize(width(), height());

    ui->progressBar->setMinimum(1);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setRange(1,100);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::start_Loading()
{
for (int value = ui->progressBar->minimum();value<= ui->progressBar->maximum();value++){
QThread::msleep(30);
ui->progressBar->setValue(value);
ui->label_value->setText(QString::number(value)+"%");
qApp->processEvents(QEventLoop::EventLoopExec);

}
this->hide();

}
