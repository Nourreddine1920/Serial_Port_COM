#include "dashboard.h"
#include "ui_dashboard.h"
#include <QIcon>

Dashboard::Dashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("IPs Configurations ");

    auto *quit = new QAction("&Quit", this);

    // Checkable UART Configurations
    auto *UART4 = new QAction("UART4", this);
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

    // Checkable ADC Configurations
    QAction *ADC1 = new QAction("ADC1", this);
    ADC1->setCheckable(true);


    QAction *ADC2 = new QAction("&ADC2", this);
    ADC2->setCheckable(true);

    QAction *ADC3 = new QAction("&ADC3", this);
    ADC3->setCheckable(true);



    // Checkable DAC Configurations
    QAction *DAC1 = new QAction("DAC1", this);
    DAC1->setCheckable(true);



    // Checkable Input Capture Mode Configurations
    QAction *InputCaptureMode = new QAction("Input Capture Mode" , this);
    InputCaptureMode->setCheckable(true);








    QMenu *UART = menuBar()->addMenu("&UART");
    QMenu *SPI = menuBar()->addMenu("&SPI");
    QMenu *I2C = menuBar()->addMenu("&I2C");
    QMenu *ADC = menuBar()->addMenu("&ADC");
    QMenu *DAC = menuBar()->addMenu("&DAC");
    QMenu *TIMER = menuBar()->addMenu("&Frequency Mesure");
    QFont font = menuBar()->font();
    // Create a QFont object and set its bold property to true
    font.setBold(true);
    menuBar()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight);
    menuBar()->setLayout(layout);
    QLabel *logoLabel = new QLabel(menuBar());
    QPixmap logoPixmap(":/logo-actia.png");  // Replace with your own logo image file
    logoLabel->setPixmap(logoPixmap);
    logoLabel->setScaledContents(true);
    //QAction *logoAction = new QAction(menuBar());



    QString style = "\
            QMenuBar {\
                background-color: #868482;\
                spacing: 50px;\
            }\
            QMenuBar::item {\
                background-color: transparent;\
                padding: 15px ;\
                width : 500px;\
                margin: 2px;\
                border: 5px;\
                font : Helvetica gras 20px;\
                color: #FFFFFF;\
            }\
            QMenuBar::item:selected {\
                background-color:#328930;\
            }\
            QMenu {\
                background-color: #444444;\
                border: none;\
                padding: 6px 10px;\
            }\
            QMenu::item {\
                background-color: transparent;\
                padding: 4px 20px;\
                margin: 0px;\
                border: none;\
                color: #FFFFFF;\
            }\
            QMenu::item:selected {\
                background-color: #328930;\
            }";

    menuBar()->setStyleSheet(style);
    font.setPointSize(font.pointSize() + 6); // increase by 2 points
    font.setPixelSize(20);
    font.setPointSizeF(10);
    QSizePolicy policy = UART->sizePolicy();
    policy.setHorizontalStretch(10); // increase by a factor of 2

    UART->setSizePolicy(policy);
    UART->setStyleSheet("font: Arial 15px; color: white; background-color: #868482;");
    SPI->setStyleSheet("font: Arial 15px; color: white; background-color: #868482;");
    I2C->setStyleSheet("font: Arial 15px; color: white; background-color: #868482;");
    ADC->setStyleSheet("font: Arial 15px; color: white; background-color: #868482;");
    DAC->setStyleSheet("font: Arial 15px; color: white; background-color: #868482;");
    TIMER->setStyleSheet("font: Arial 15px; color: white; background-color: #868482;");

    menuBar()->setFont(font);
    UART->setFont(font);
    // Available UART IPs
    QSettings settings("MyCompany", "MyApp" , this);


    UART->addAction(UART4);
    UART->addSeparator();
    //UART->setIcon(QIcon::fromTheme("document-open"));
    //UART->setIcon(style()->standardIcon(QStyle::SP_FileDialogContentsView));



    UART->addAction(UART5);
    UART->addSeparator();

    UART->addAction(UART7);
    UART->addSeparator();

    UART->addAction(UART8);
    UART->addSeparator();

    UART->addAction(UART9);
    UART->addSeparator();


    UART->addAction(USART1);
    UART->addSeparator();

    UART->addAction(USART2);
    UART->addSeparator();

    UART->addAction(USART6);
    UART->addSeparator();

    UART->addAction(USART10);
    UART->addSeparator();

    TIMER->addAction(InputCaptureMode);
    UART->addSeparator();


    // Connect to the UART configurations
    connect(UART4, &QAction::triggered, this, &Dashboard::UARTConfig);
    connect(UART5, &QAction::triggered, this, &Dashboard::UARTConfig);
    connect(UART7, &QAction::triggered, this, &Dashboard::UARTConfig);
    connect(UART8, &QAction::triggered, this, &Dashboard::UARTConfig);

    connect(UART9, &QAction::triggered, this, &Dashboard::UARTConfig);

    connect(USART1, &QAction::triggered, this, &Dashboard::UARTConfig);

    connect(USART2, &QAction::triggered, this, &Dashboard::UARTConfig);

    connect(USART6, &QAction::triggered, this, &Dashboard::UARTConfig);

    connect(USART10, &QAction::triggered, this, &Dashboard::UARTConfig);


    // Available SPI IPs
    SPI->addAction(SPI1);
    SPI->addSeparator();

    SPI->addAction(SPI2);
    SPI->addSeparator();

    SPI->addAction(SPI3);
    SPI->addSeparator();

    SPI->addAction(SPI4);
    SPI->addSeparator();

    SPI->addAction(SPI5);
    SPI->addSeparator();


    SPI->addAction(SPI6);
    SPI->addSeparator();



    // Connect to the SPI configurations
    connect(SPI1, &QAction::triggered, this, &Dashboard::SPIConfig);
    connect(SPI2, &QAction::triggered, this, &Dashboard::SPIConfig);
    connect(SPI3, &QAction::triggered, this, &Dashboard::SPIConfig);
    connect(SPI4, &QAction::triggered, this, &Dashboard::SPIConfig);

    connect(SPI5, &QAction::triggered, this, &Dashboard::SPIConfig);

    connect(SPI6, &QAction::triggered, this, &Dashboard::SPIConfig);


    // Available I2C IPs
    I2C->addAction(I2C1);
    I2C->addSeparator();

    I2C->addAction(I2C2);
    I2C->addSeparator();

    I2C->addAction(I2C3);
    I2C->addSeparator();

    I2C->addAction(I2C4);
    I2C->addSeparator();

    I2C->addAction(I2C5);
    I2C->addSeparator();




    // Connect to the I2C configurations
    connect(I2C1, &QAction::triggered, this, &Dashboard::I2CConfig);
    connect(I2C2, &QAction::triggered, this, &Dashboard::I2CConfig);
    connect(I2C3, &QAction::triggered, this, &Dashboard::I2CConfig);
    connect(I2C4, &QAction::triggered, this, &Dashboard::I2CConfig);

    connect(I2C5, &QAction::triggered, this, &Dashboard::I2CConfig);


    // Available ADC IPs
    ADC->addAction(ADC1);
    ADC->addSeparator();

    ADC->addAction(ADC2);
    ADC->addSeparator();

    ADC->addAction(ADC3);
    ADC->addSeparator();




    // Connect to the SPI configurations
    connect(ADC1, &QAction::triggered, this, &Dashboard::ADCConfig);
    connect(ADC2, &QAction::triggered, this, &Dashboard::ADCConfig);
    connect(ADC3, &QAction::triggered, this, &Dashboard::ADCConfig);


    // Available DAC IPs
    DAC->addAction(DAC1);
    DAC->addSeparator();


    // Connect to the DAC configurations
    connect(DAC1, &QAction::triggered, this, &Dashboard::DACConfig);


    connect(quit, &QAction::triggered, qApp, QApplication::quit);
}

Dashboard::~Dashboard()
{
    delete ui;
}
