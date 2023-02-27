#include "dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("IPs Configurations ");

    auto *quit = new QAction("&Quit", this);

    // Checkable UART Configurations
    QAction *UART4 = new QAction("UART4", this);
    UART4->setCheckable(true);


    QAction *UART5 = new QAction("&UART5", this);
    UART5->setCheckable(true);

    QAction *UART7 = new QAction("&UART7", this);
    UART7->setCheckable(true);

    QAction *UART8 = new QAction("&UART8", this);
    UART8->setCheckable(true);

    QAction *UART9 = new QAction("&UART9", this);
    UART9->setCheckable(true);

    QAction *USART1 = new QAction("&USART1", this);
    USART1->setCheckable(true);


    QAction *USART2 = new QAction("&USART2", this);
    USART2->setCheckable(true);

    QAction *USART6 = new QAction("&USART6", this);
    USART6->setCheckable(true);

    QAction *USART10 = new QAction("&USART10", this);
    USART10->setCheckable(true);



    // Checkable SPI Configurations
    QAction *SPI1 = new QAction("SPI1", this);
    SPI1->setCheckable(true);


    QAction *SPI2 = new QAction("&SPI2", this);
    SPI2->setCheckable(true);

    QAction *SPI3 = new QAction("&SPI3", this);
    SPI3->setCheckable(true);

    QAction *SPI4 = new QAction("&SPI4", this);
    SPI4->setCheckable(true);

    QAction *SPI5 = new QAction("&SPI5", this);
    SPI5->setCheckable(true);

    QAction *SPI6 = new QAction("&SPI6", this);
    SPI6->setCheckable(true);

    // Checkable I2C Configurations
    QAction *I2C1 = new QAction("I2C1", this);
    I2C1->setCheckable(true);


    QAction *I2C2 = new QAction("&I2C2", this);
    I2C2->setCheckable(true);

    QAction *I2C3 = new QAction("&I2C3", this);
    I2C3->setCheckable(true);

    QAction *I2C4 = new QAction("&I2C4", this);
    I2C4->setCheckable(true);

    QAction *I2C5 = new QAction("&I2C5", this);
    I2C5->setCheckable(true);







    QMenu *UART = menuBar()->addMenu("&UART Selection");
    QMenu *SPI = menuBar()->addMenu("&SPI Selection");
    QMenu *I2C = menuBar()->addMenu("&I2C Selection");
    QMenu *ADC = menuBar()->addMenu("&ADC Selection");
    QMenu *DAC = menuBar()->addMenu("&DAC Selection");
    QMenu *TIMER = menuBar()->addMenu("&TIMER Selection");
    QFont font = menuBar()->font();
    font.setPointSize(font.pointSize() + 6); // increase by 2 points
    font.setPixelSize(20);
    font.setPointSizeF(10);
    QSizePolicy policy = UART->sizePolicy();
    policy.setHorizontalStretch(20); // increase by a factor of 2
    UART->setSizePolicy(policy);
    menuBar()->setFont(font);
    UART->setFont(font);
    // Available UART IPs
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

    // Connect to the UART configurations
    connect(UART4, &QAction::triggered, this, &Dashboard::openWidget);
    connect(UART5, &QAction::triggered, this, &Dashboard::openWidget);
    connect(UART7, &QAction::triggered, this, &Dashboard::openWidget);
    connect(UART8, &QAction::triggered, this, &Dashboard::openWidget);

    connect(UART9, &QAction::triggered, this, &Dashboard::openWidget);

    connect(USART1, &QAction::triggered, this, &Dashboard::openWidget);

    connect(USART2, &QAction::triggered, this, &Dashboard::openWidget);

    connect(USART6, &QAction::triggered, this, &Dashboard::openWidget);

    connect(USART10, &QAction::triggered, this, &Dashboard::openWidget);


    // Available SPI IPs
    SPI->addAction(SPI1);
    SPI->addAction(SPI2);
    SPI->addAction(SPI3);
    SPI->addAction(SPI4);
    SPI->addAction(SPI5);

    SPI->addAction(SPI6);


    // Connect to the SPI configurations
    connect(SPI1, &QAction::triggered, this, &Dashboard::openWidget);
    connect(SPI2, &QAction::triggered, this, &Dashboard::openWidget);
    connect(SPI3, &QAction::triggered, this, &Dashboard::openWidget);
    connect(SPI4, &QAction::triggered, this, &Dashboard::openWidget);

    connect(SPI5, &QAction::triggered, this, &Dashboard::openWidget);

    connect(SPI6, &QAction::triggered, this, &Dashboard::openWidget);


    // Available I2C IPs
    I2C->addAction(I2C1);
    I2C->addAction(I2C2);
    I2C->addAction(I2C3);
    I2C->addAction(I2C4);
    I2C->addAction(I2C5);



    // Connect to the SPI configurations
    connect(I2C1, &QAction::triggered, this, &Dashboard::openWidget);
    connect(I2C2, &QAction::triggered, this, &Dashboard::openWidget);
    connect(I2C3, &QAction::triggered, this, &Dashboard::openWidget);
    connect(I2C4, &QAction::triggered, this, &Dashboard::openWidget);

    connect(I2C5, &QAction::triggered, this, &Dashboard::openWidget);





    connect(quit, &QAction::triggered, qApp, QApplication::quit);
}

Dashboard::~Dashboard()
{
    delete ui;
}
