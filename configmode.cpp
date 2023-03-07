#include "configmode.h"
#include "ui_configmode.h"
#include "dashboard.h"
#include <QIcon>
#include <QCheckBox>
#include <QWidgetAction>
#include <QToolButton>

ConfigMode::ConfigMode(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigMode)
{
    ui->setupUi(this);

    QWidget::setWindowTitle("ConfigMode");

    //-------------------------IPs Configurations-------------------------//

    // Checkable UART Configurations
    auto *UART4 = new QAction("UART4", this);
    //QAction *action = new QAction("Checkable Action", menuBar());

//    UART4->setCheckable(true);


    QAction *UART5 = new QAction("&UART5", this);
//    UART5->setCheckable(true);

    QAction *UART7 = new QAction("&UART7", this);
//    UART7->setCheckable(true);

    QAction *UART8 = new QAction("&UART8", this);
//    UART8->setCheckable(true);

    QAction *UART9 = new QAction("&UART9", this);
//    UART9->setCheckable(true);

    QAction *USART1 = new QAction("&USART1", this);
//    USART1->setCheckable(true);


    QAction *USART2 = new QAction("&USART2", this);
//    USART2->setCheckable(true);

    QAction *USART6 = new QAction("&USART6", this);
//    USART6->setCheckable(true);

    QAction *USART10 = new QAction("&USART10", this);
//    USART10->setCheckable(true);



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


    // Checkable GPIO Mode Configurations

    QAction *GPIO_OUTPUT = new QAction("GPIO_OUTPUT" , this);
    GPIO_OUTPUT->setCheckable(true);

    QAction *GPIO_INPUT = new QAction("GPIO_INPUT" , this);
    GPIO_INPUT->setCheckable(true);


    // Create a QToolButton for the "Connect" button
    QToolButton *connectButton = new QToolButton(this);
    connectButton->setIcon(QIcon("C:/Users/nawledbr/Documents/Serial_Port_COM/send.png"));
    connectButton->setText(tr("&Send Configs"));
    connectButton->setStyleSheet("font: Helvetica gras 20px; padding: 18px; width: 500px;");
    connectButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    // Connect the QToolButton's clicked() signal to a slot that will open the new UI
//    connect(connectButton, &QToolButton::clicked, this, &Dashboard::showConfigMode);

    QToolButton *returnButton = new QToolButton(this);
    returnButton->setIcon(QIcon("C:/Users/nawledbr/Documents/Serial_Port_COM/back.png"));
    returnButton->setText(tr("&Return"));
    returnButton->setStyleSheet("font: Helvetica gras 20px; padding: 18px; width: 500px;");
    returnButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    connect(returnButton, &QToolButton::clicked, this, &ConfigMode::returnDashboard);





    QMenu *UART = menuBar()->addMenu("&UART");
    QCheckBox *checkBox = new QCheckBox();

    QWidgetAction *action = new QWidgetAction(menuBar());
    action->setDefaultWidget(checkBox);

    //-------------------------Styling the meny Bar -------------------------//


    QMenu *SPI = menuBar()->addMenu("&SPI");
    QMenu *I2C = menuBar()->addMenu("&I2C");
    QMenu *ADC = menuBar()->addMenu("&ADC");
    QMenu *DAC = menuBar()->addMenu("&DAC");
    QMenu *TIMER = menuBar()->addMenu("&Frequency Mesure");
    QMenu *GPIO = menuBar()->addMenu("&GPIO");
    // Add the QToolButton to the menu bar
    menuBar()->setCornerWidget(connectButton, Qt::TopRightCorner);
    menuBar()->setCornerWidget(returnButton , Qt::TopLeftCorner);

    QFont font = menuBar()->font();
    // Create a QFont object and set its bold property to true
    font.setBold(true);
    menuBar()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight);
    menuBar()->setLayout(layout);
    // Create a QPixmap with your logo image
    // Create a logo QLabel and set its style sheet
//    QLabel *logo = new QLabel(this);
//    logo->setPixmap(QPixmap("C:/Users/nawledbr/Documents/Serial_Port_COM/images/logo-actia.png").scaledToHeight(30));
//    logo->setObjectName("logo");





//    QString style = "\
//            QMenuBar {\
//                background-color: #868482;\
//                spacing: 20px;\
//            }\
//            QMenuBar::item {\
//                background-color: transparent;\
//                padding: 15px ;\
//                width : 500px;\
//                margin: 2px;\
//                border: 5px;\
//                font : Helvetica gras 20px;\
//                color: #FFFFFF;\
//            }\
//            QMenuBar::item:selected {\
//                background-color:#328930;\
//            }\
//            QMenu {\
//                background-color: #444444;\
//                border: none;\
//                padding: 6px 10px;\
//            }\
//            QMenu::item {\
//                background-color: transparent;\
//                padding: 4px 20px;\
//                margin: 0px;\
//                border: none;\
//                color: #FFFFFF;\
//            }\
//            QMenu::item:selected {\
//                background-color: #328930;\
//            }";

            // Create a QString with your menu bar and QToolButton styles
            QString style = "\
                QMenuBar {\
                    background-color: #868482;\
                    spacing: 7px;\
                }\
                QMenuBar::item {\
                    background-color: transparent;\
                    padding: 18px;\
                    width: 500px;\
                    margin: 2px;\
                    border: 5px;\
                    font: Helvetica gras 20px;\
                    color: #FFFFFF;\
                }\
                QMenuBar::item:selected {\
                    background-color: #328930;\
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
                }\
                QToolButton {\
                    background-color: transparent;\
                    border: none;\
                    padding: 10px 15px;\
                    font: Helvetica gras 20px;\
                    color: #FFFFFF;\
                }\
                QToolButton:hover {\
                    background-color: #328930;\
                    border-radius: 5px;\
                }\
                QToolButton:pressed {\
                    background-color: #2C7A2C;\
                }\
                QToolButton::menu-indicator {\
                    image: none;\
                }\
                QToolButton::menu-button {\
                    width: 24px;\
                    height: 24px;\
                }";

            // Set the style sheet for the menu bar and button
            menuBar()->setStyleSheet(style);
            connectButton->setStyleSheet(style);
            returnButton->setStyleSheet(style);


//    menuBar()->setStyleSheet(style);
//    logo->setStyleSheet(style);
    // Add the logo to the menu bar


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
    GPIO->setStyleSheet("font: Arial 15px; color: white; background-color: #868482;");


    menuBar()->setFont(font);
    UART->setFont(font);

    //-------------------------Connect to the UART configurations-------------------------//

    UART->addAction(UART4);
    //UART->addAction(action);

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






    // Connect to the UART configurations
//    connect(UART4, &QAction::triggered, this, &Dashboard::UART4Config);
//    connect(UART5, &QAction::triggered, this, &Dashboard::UART5Config);
//    connect(UART7, &QAction::triggered, this, &Dashboard::UARTConfig);
//    connect(UART8, &QAction::triggered, this, &Dashboard::UARTConfig);

//    connect(UART9, &QAction::triggered, this, &Dashboard::UARTConfig);

//    connect(USART1, &QAction::triggered, this, &Dashboard::USART1Config);

//    connect(USART2, &QAction::triggered, this, &Dashboard::USART2Config);

//    connect(USART6, &QAction::triggered, this, &Dashboard::UARTConfig);

//    connect(USART10, &QAction::triggered, this,&Dashboard::UARTConfig);


    //-------------------------Connect to the SPI configurations-------------------------//

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
//    connect(SPI1, &QAction::triggered, this, &Dashboard::SPI1Config);
//    connect(SPI2, &QAction::triggered, this, &Dashboard::SPI2Config);
//    connect(SPI3, &QAction::triggered, this, &Dashboard::SPIConfig);
//    connect(SPI4, &QAction::triggered, this, &Dashboard::SPIConfig);

//    connect(SPI5, &QAction::triggered, this, &Dashboard::SPIConfig);

//    connect(SPI6, &QAction::triggered, this, &Dashboard::SPIConfig);

    //-------------------------Connect to the I2C configurations-------------------------//

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
//    connect(I2C1, &QAction::triggered, this, &Dashboard::I2C1Config);
//    connect(I2C2, &QAction::triggered, this, &Dashboard::I2C2Config);
//    connect(I2C3, &QAction::triggered, this, &Dashboard::I2CConfig);
//    connect(I2C4, &QAction::triggered, this, &Dashboard::I2CConfig);

//    connect(I2C5, &QAction::triggered, this, &Dashboard::I2CConfig);


    //-------------------------Connect to the ADC configurations-------------------------//


    ADC->addAction(ADC1);
    ADC->addSeparator();

    ADC->addAction(ADC2);
    ADC->addSeparator();

    ADC->addAction(ADC3);
    ADC->addSeparator();




//    connect(ADC1, &QAction::triggered, this, &Dashboard::ADC1Config);
//    connect(ADC2, &QAction::triggered, this, &Dashboard::ADCConfig);
//    connect(ADC3, &QAction::triggered, this, &Dashboard::ADC3Config);


    //-------------------------Connect to the DAC configurations-------------------------//


    DAC->addAction(DAC1);
    DAC->addSeparator();


//    connect(DAC1, &QAction::triggered, this, &Dashboard::DACConfig);


    //-------------------------Connect to the GPIO configurations-------------------------//


    GPIO->addAction(GPIO_OUTPUT);
    GPIO->addSeparator();
    GPIO->addAction(GPIO_INPUT);
    GPIO->addSeparator();


//    connect(GPIO_OUTPUT, &QAction::triggered, this, &Dashboard::GPIOOUPUTConfig);
//    connect(GPIO_INPUT, &QAction::triggered, this, &Dashboard::GPIOINPUTConfig);


    //-------------------------Connect to the TIMER configurations-------------------------//

    TIMER->addAction(InputCaptureMode);
    TIMER->addSeparator();

    // Connect to the TIMER configurations
//    connect(InputCaptureMode, &QAction::triggered, this, &Dashboard::FrequencyMesureConfig);







}

void ConfigMode::returnDashboard()
{
    Dashboard *dashboard = new Dashboard();
    dashboard->show();
    this->hide();
}

ConfigMode::~ConfigMode()
{
    delete ui;
}
