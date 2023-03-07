#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    QWidget::setWindowTitle("Welcome Page");

    setStyleSheet("QWidget {"
                  "    background-color: #f0f0f0;"
                  "}");

    QString styleSheet =
        "QLabel {"
        "    background-color: #4CAF50;"
        "    border: none;"
        "    color: white;"
        "    padding: 15px 32px;"
        "    text-align: center;"
        "    text-decoration: none;"
        "    display: inline-block;"
        "    font-size: 20px;"
        "    margin: 4px 2px;"
        "    cursor: pointer;"
        "    border-radius: 10px;"
        "}"
        ""
        "QPushButton:hover {"
        "    background-color: #3e8e41;"
        "}";

    ui->label_titre->setStyleSheet(styleSheet);

    //setFixedSize(width(), height());

    ui->progressBar->setMinimum(1);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setRange(1,100);

    // Set stylesheet for progress bar
       QString styleSheet1 =
           "QProgressBar {"
           "    border: 2px solid grey;"
           "    border-radius: 5px;"
           "    background-color: #f0f0f0;"
           "    height: 20px;"
           "}"
           ""
           "QProgressBar::chunk {"
           "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #50C878, stop:1 #328930);"
           "    border-radius: 5px;"
           "}";
       ui->progressBar->setStyleSheet(styleSheet1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::start_Loading()
{
for (int value = ui->progressBar->minimum();value<= ui->progressBar->maximum();value++){
QThread::msleep(10);
ui->progressBar->setValue(value);
ui->label_value->setText(QString::number(value)+"%");
qApp->processEvents(QEventLoop::EventLoopExec);

}
this->hide();

}
