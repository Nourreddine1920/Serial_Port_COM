#include "dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("IPs Configurations ");

    auto *quit = new QAction("&Quit", this);
    QAction *UART4 = new QAction("UART4", this);
    UART4->setCheckable(true);

    //auto *UART4 = new QAction("&UART4", this);
    auto *UART5 = new QAction("&UART5", this);
    auto *UART7 = new QAction("&UART7", this);
    auto *UART8 = new QAction("&UART8", this);
    auto *UART9 = new QAction("&UART9", this);
    auto *USART1 = new QAction("&USART1", this);

    auto *USART2 = new QAction("&USART2", this);
    auto *USART6 = new QAction("&USART6", this);
    auto *USART10 = new QAction("&USART10", this);




    QMenu *UART = menuBar()->addMenu("&UART Selection");
    QMenu *SPI = menuBar()->addMenu("&SPI Selection");
    QMenu *I2C = menuBar()->addMenu("&I2C Selection");
    QMenu *ADC = menuBar()->addMenu("&ADC Selection");
    QMenu *DAC = menuBar()->addMenu("&DAC Selection");
    QMenu *TIMER = menuBar()->addMenu("&TIMER Selection");
    QFont font = menuBar()->font();
    font.setPointSize(font.pointSize() + 2); // increase by 2 points
    font.setPixelSize(20);
    font.setPointSizeF(10);
    QSizePolicy policy = UART->sizePolicy();
    policy.setHorizontalStretch(20); // increase by a factor of 2
    UART->setSizePolicy(policy);
    menuBar()->setFont(font);
    UART->setFont(font);

    UART->addAction(UART4);
    UART->addAction(UART5);
    UART->addAction(UART7);
    UART->addAction(UART8);
    UART->addAction(UART9);

    UART->addAction(USART1);
    UART->addAction(USART2);
    UART->addAction(USART6);
    UART->addAction(USART10);
    TIMER->addAction(USART1);
    connect(UART4, &QAction::triggered, this, &Dashboard::openWidget);
    connect(quit, &QAction::triggered, qApp, QApplication::quit);
}

Dashboard::~Dashboard()
{
    delete ui;
}
