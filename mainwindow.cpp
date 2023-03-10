#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFontDatabase>

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
            "font-family:Helvetica;"
        "    background-color: #E3E0DF;"
        "    border: none;"
        "    color: Black;"
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

    // Set the font and style sheet for the title label
    QFontDatabase fontDatabase;
    QStringList fontFamilies = fontDatabase.families();

    // Choose the first available font as the best font
    QString bestFont = fontFamilies.first();

    // Create a font object with the best font and size
    QFont font(bestFont, 30);
    QFont font1(bestFont, 15);

    // Set the font and style sheet for the label
    ui->label_titre->setFont(font);

    ui->label_titre->setStyleSheet("font-weight: bold; font-size: 30px; color: darkGreen; background-color:  #E3E0DF; ");

    ui->label_titre->setAlignment(Qt::AlignCenter);

    ui->label_titre->setFont(font);

    // Set the font and style sheet for the label

    ui->label_value->setStyleSheet("font-weight: bold; color: darkGreen; background-color: white; ");

    ui->label_value->setAlignment(Qt::AlignCenter);

    ui->label_value->setFont(font1);


//    ui->label_titre->setStyleSheet(styleSheet);
//    ui->label_value->setStyleSheet(styleSheet);



    //setFixedSize(width(), height());

    ui->progressBar->setMinimum(1);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setRange(1,100);

    // Set stylesheet for progress bar
       QString styleSheet1 =
           "QProgressBar {"
           "    border: 2px solid #E3E0DF;"
           "    border-radius: 5px;"
           "    background-color: #f0f0f0;"
           "    height: 20px;"
           "}"
           ""
           "QProgressBar::chunk {"
           "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #50C878, stop:1 #00A36C);"
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
QThread::msleep(30);
ui->progressBar->setValue(value);
ui->label_value->setText(QString::number(value)+"%");
qApp->processEvents(QEventLoop::EventLoopExec);

}
this->hide();

}
