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







    connect(UART4, &QAction::triggered, this, [=]() {

        QSettings settings("UARTConfig.txt", QSettings::IniFormat);

        // create the list widget
        QListWidget* configList = new QListWidget(this);
        configList->clear();
        settings.beginGroup("UART4Configs");

        QString baudrate;
        QString Parity;
        QString stopBits;
        QString DataBits;
        QString FlowControl;

        QString BaudrateConfig = settings.value("Baudrate" , baudrate).toString();
        QString ParityConfig = settings.value("Parity" , Parity).toString();
        QString stopBitsConfig = settings.value("stopBits" , stopBits).toString();
        QString DataBitsConfig = settings.value("DataBits" , DataBits).toString();
        QString FlowControlConfig = settings.value("FlowControl" , FlowControl).toString();



        QListWidgetItem* titleItem = new QListWidgetItem(tr("UART4 Configurations"), configList);

        QListWidgetItem* baudRateItem = new QListWidgetItem(tr("•  Baud Rate     :     ") +BaudrateConfig , configList);
        QListWidgetItem* ParityItem = new QListWidgetItem(tr("•  Parity       :  ") +ParityConfig , configList);
        QListWidgetItem* stopBitsItem = new QListWidgetItem(tr("•  stopBits     :    ") +stopBitsConfig , configList);
        QListWidgetItem* DataBitsItem = new QListWidgetItem(tr("•  DataBits     :    ") +DataBitsConfig , configList);
        QListWidgetItem* FlowControlItem = new QListWidgetItem(tr("•  FlowControl    :    ") +FlowControlConfig , configList);


        // Set the font and style sheet for the title label
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 18);

        titleItem->setFont(font);
        titleItem->setTextAlignment(Qt::TopLeftCorner);
        QBrush gray(Qt::gray);
        QBrush white(Qt::white);

        titleItem->setBackground(gray);
        titleItem->setForeground(white);

        baudRateItem->setFont(QFont("Helvetica", 13));
        baudRateItem->setTextAlignment(Qt::TopLeftCorner);
        ParityItem->setFont(QFont("Helvetica", 13));
        ParityItem->setTextAlignment(Qt::TopLeftCorner);
        stopBitsItem->setFont(QFont("Helvetica", 13));
        stopBitsItem->setTextAlignment(Qt::TopLeftCorner);
        DataBitsItem->setFont(QFont("Helvetica", 13));
        DataBitsItem->setTextAlignment(Qt::TopLeftCorner);
        FlowControlItem->setFont(QFont("Helvetica", 13));
        FlowControlItem->setTextAlignment(Qt::TopLeftCorner);


        configList->setSpacing(15);
        configList->addItem(titleItem);

        configList->addItem(baudRateItem);
        configList->addItem(ParityItem);
        configList->addItem(stopBitsItem);
        configList->addItem(DataBitsItem);
        configList->addItem(FlowControlItem);



        configList->show();

        qDebug() << "baudrate:" << baudRateItem;
        qDebug() << "Parity:" << ParityItem;
        settings.endGroup();

        // Create Layout form
        QFormLayout* layout = new QFormLayout(this);

        // Create a QLabel for "DAC configurations" and center it horizontally
        QLabel* titleLabel = new QLabel("UART4 configurations", this);

        // Load the icon image
        QPixmap icon("C:/Users/nawledbr/Documents/Serial_Port_COM/config7.png");

        // Create a QLabel for the icon and set its size
        QLabel* iconLabel = new QLabel(this);
        iconLabel->setPixmap(icon.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        iconLabel->setFixedSize(30, 30);

        QHBoxLayout* titleLayout = new QHBoxLayout();
        titleLayout->addWidget(iconLabel);
        titleLayout->addWidget(titleLabel);
        titleLayout->setSpacing(10); // Set the spacing between the icon and the title label


        // create a widget to hold the list and add it to a layout
        QWidget* centralWidget = new QWidget(this);
        QHBoxLayout* layout1 = new QHBoxLayout(centralWidget);
        layout1->addWidget(configList);
        layout1->setAlignment(Qt::AlignHCenter);
        layout->addRow(titleLayout);
        layout->addRow(layout1);



//        configList->setStyleSheet("background-color: white; font-size: 14px;");
        configList->setStyleSheet("background-color: white; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



//        layout1->addRow(configList);
//        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
//                                  "QListWidget::item { padding: 5px; }"
//                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


        // set the central widget of the main window to the layout
        setCentralWidget(centralWidget);
    });
    connect(UART5, &QAction::triggered, this, [=]() {

        QSettings settings("UARTConfig.txt", QSettings::IniFormat);

        // create the list widget

        settings.beginGroup("UART5Configs");

        QString baudrate;
        QString Parity;
        QString BaudrateConfig = settings.value("Baudrate" , baudrate).toString();
        QString ParityConfig = settings.value("Parity" , Parity).toString();
        settings.endGroup();

        QFormLayout* layout = new QFormLayout(this);

        // Create a QLabel for "DAC configurations" and center it horizontally
        QLabel* titleLabel = new QLabel("UART5 configurations", this);

        // Load the icon image
        QPixmap icon("C:/Users/nawledbr/Documents/Serial_Port_COM/config7.png");

        // Create a QLabel for the icon and set its size
        QLabel* iconLabel = new QLabel(this);
        iconLabel->setPixmap(icon.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        iconLabel->setFixedSize(30, 30);

        // Create a QHBoxLayout to hold the icon and the title label
        QHBoxLayout* titleLayout = new QHBoxLayout();
        titleLayout->addWidget(iconLabel);
        titleLayout->addWidget(titleLabel);
        titleLayout->setSpacing(10); // Set the spacing between the icon and the title label

        // Set the font and style sheet for the title label
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 15);

        // Set the font and style sheet for the label
        titleLabel->setFont(font);
        iconLabel->setFont(font);

        titleLabel->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");
//                iconLabel->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");

        titleLabel->setAlignment(Qt::AlignCenter);


        // Add the title label and the icon to the main layout
        layout->addRow(titleLayout);


       // Create the baud rate label and combo box

       QLabel* baudRateLabel = new QLabel(tr("Baud Rate"), this);
       baudRateLabel->setText(BaudrateConfig);




       baudRateLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");

       layout->addRow(baudRateLabel);



//        QListWidgetItem* baudRateItem = new QListWidgetItem("Baud Rate: " +BaudrateConfig , configList);
//        QListWidgetItem* ParityItem = new QListWidgetItem("Parity: " +ParityConfig , configList);



//        qDebug() << "baudrate:" << baudRateItem;
//        qDebug() << "Parity:" << ParityItem;


    });

    connect(USART1, &QAction::triggered, this, [=]() {

        QSettings settings("UARTConfig.txt", QSettings::IniFormat);

        // create the list widget
        QListWidget* configList = new QListWidget(this);
        configList->clear();
        settings.beginGroup("USART1Configs");

        QString baudrate;
        QString Parity;
        QString stopBits;
        QString DataBits;
        QString FlowControl;

        QString BaudrateConfig = settings.value("Baudrate" , baudrate).toString();
        QString ParityConfig = settings.value("Parity" , Parity).toString();
        QString stopBitsConfig = settings.value("stopBits" , stopBits).toString();
        QString DataBitsConfig = settings.value("DataBits" , DataBits).toString();
        QString FlowControlConfig = settings.value("FlowControl" , FlowControl).toString();



        QListWidgetItem* titleItem = new QListWidgetItem(tr("USART1 Configurations"), configList);

        QListWidgetItem* baudRateItem = new QListWidgetItem(tr("•  Baud Rate     :     ") +BaudrateConfig , configList);
        QListWidgetItem* ParityItem = new QListWidgetItem(tr("•  Parity       :  ") +ParityConfig , configList);
        QListWidgetItem* stopBitsItem = new QListWidgetItem(tr("•  stopBits     :    ") +stopBitsConfig , configList);
        QListWidgetItem* DataBitsItem = new QListWidgetItem(tr("•  DataBits     :    ") +DataBitsConfig , configList);
        QListWidgetItem* FlowControlItem = new QListWidgetItem(tr("•  FlowControl    :    ") +FlowControlConfig , configList);


        // Set the font and style sheet for the title label
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 18);

        titleItem->setFont(font);
        titleItem->setTextAlignment(Qt::TopLeftCorner);
        QBrush gray(Qt::gray);
        QBrush white(Qt::white);

        titleItem->setBackground(gray);
        titleItem->setForeground(white);

        baudRateItem->setFont(QFont("Helvetica", 13));
        baudRateItem->setTextAlignment(Qt::TopLeftCorner);
        ParityItem->setFont(QFont("Helvetica", 13));
        ParityItem->setTextAlignment(Qt::TopLeftCorner);
        stopBitsItem->setFont(QFont("Helvetica", 13));
        stopBitsItem->setTextAlignment(Qt::TopLeftCorner);
        DataBitsItem->setFont(QFont("Helvetica", 13));
        DataBitsItem->setTextAlignment(Qt::TopLeftCorner);
        FlowControlItem->setFont(QFont("Helvetica", 13));
        FlowControlItem->setTextAlignment(Qt::TopLeftCorner);


        configList->setSpacing(15);
        configList->addItem(titleItem);

        configList->addItem(baudRateItem);
        configList->addItem(ParityItem);
        configList->addItem(stopBitsItem);
        configList->addItem(DataBitsItem);
        configList->addItem(FlowControlItem);


        configList->show();

        qDebug() << "baudrate:" << baudRateItem;
        qDebug() << "Parity:" << ParityItem;
        settings.endGroup();

        // Create Layout form
        QFormLayout* layout = new QFormLayout(this);

        // Create a QLabel for "DAC configurations" and center it horizontally
        QLabel* titleLabel = new QLabel("UART4 configurations", this);

        // Load the icon image
        QPixmap icon("C:/Users/nawledbr/Documents/Serial_Port_COM/config7.png");

        // Create a QLabel for the icon and set its size
        QLabel* iconLabel = new QLabel(this);
        iconLabel->setPixmap(icon.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        iconLabel->setFixedSize(30, 30);

        QHBoxLayout* titleLayout = new QHBoxLayout();
        titleLayout->addWidget(iconLabel);
        titleLayout->addWidget(titleLabel);
        titleLayout->setSpacing(10); // Set the spacing between the icon and the title label


        // create a widget to hold the list and add it to a layout
        QWidget* centralWidget = new QWidget(this);
        QHBoxLayout* layout1 = new QHBoxLayout(centralWidget);
        layout1->addWidget(configList);
        layout1->setAlignment(Qt::AlignHCenter);
        layout->addRow(titleLayout);
        layout->addRow(layout1);



//        configList->setStyleSheet("background-color: white; font-size: 14px;");
        configList->setStyleSheet("background-color: white; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



//        layout1->addRow(configList);
//        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
//                                  "QListWidget::item { padding: 5px; }"
//                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


        // set the central widget of the main window to the layout
        setCentralWidget(centralWidget);
    });

    connect(USART2, &QAction::triggered, this, [=]() {

        QSettings settings("UARTConfig.txt", QSettings::IniFormat);

        // create the list widget
        QListWidget* configList = new QListWidget(this);
        configList->clear();
        settings.beginGroup("USART2Configs");

        QString baudrate;
        QString Parity;
        QString stopBits;
        QString DataBits;
        QString FlowControl;

        QString BaudrateConfig = settings.value("Baudrate" , baudrate).toString();
        QString ParityConfig = settings.value("Parity" , Parity).toString();
        QString stopBitsConfig = settings.value("stopBits" , stopBits).toString();
        QString DataBitsConfig = settings.value("DataBits" , DataBits).toString();
        QString FlowControlConfig = settings.value("FlowControl" , FlowControl).toString();



        QListWidgetItem* titleItem = new QListWidgetItem(tr("USART2 Configurations"), configList);


        QListWidgetItem* baudRateItem = new QListWidgetItem(tr("•  Baud Rate     :     ") +BaudrateConfig , configList);
        QListWidgetItem* ParityItem = new QListWidgetItem(tr("•  Parity       :  ") +ParityConfig , configList);
        QListWidgetItem* stopBitsItem = new QListWidgetItem(tr("•  stopBits     :    ") +stopBitsConfig , configList);
        QListWidgetItem* DataBitsItem = new QListWidgetItem(tr("•  DataBits     :    ") +DataBitsConfig , configList);
        QListWidgetItem* FlowControlItem = new QListWidgetItem(tr("•  FlowControl    :    ") +FlowControlConfig , configList);


        // Set the font and style sheet for the title label
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 18);

        titleItem->setFont(font);
        titleItem->setTextAlignment(Qt::TopLeftCorner);
        QBrush gray(Qt::gray);
        QBrush white(Qt::white);

        titleItem->setBackground(gray);
        titleItem->setForeground(white);

        baudRateItem->setFont(QFont("Helvetica", 13));
        baudRateItem->setTextAlignment(Qt::TopLeftCorner);
        ParityItem->setFont(QFont("Helvetica", 13));
        ParityItem->setTextAlignment(Qt::TopLeftCorner);
        stopBitsItem->setFont(QFont("Helvetica", 13));
        stopBitsItem->setTextAlignment(Qt::TopLeftCorner);
        DataBitsItem->setFont(QFont("Helvetica", 13));
        DataBitsItem->setTextAlignment(Qt::TopLeftCorner);
        FlowControlItem->setFont(QFont("Helvetica", 13));
        FlowControlItem->setTextAlignment(Qt::TopLeftCorner);


        configList->setSpacing(15);
        configList->addItem(titleItem);

        configList->addItem(baudRateItem);
        configList->addItem(ParityItem);
        configList->addItem(stopBitsItem);
        configList->addItem(DataBitsItem);
        configList->addItem(FlowControlItem);



        configList->show();

        settings.endGroup();

        // Create Layout form
        QFormLayout* layout = new QFormLayout(this);

        // Create a QLabel for "DAC configurations" and center it horizontally
        QLabel* titleLabel = new QLabel("UART4 configurations", this);

        // Load the icon image
        QPixmap icon("C:/Users/nawledbr/Documents/Serial_Port_COM/config7.png");

        // Create a QLabel for the icon and set its size
        QLabel* iconLabel = new QLabel(this);
        iconLabel->setPixmap(icon.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        iconLabel->setFixedSize(30, 30);

        QHBoxLayout* titleLayout = new QHBoxLayout();
        titleLayout->addWidget(iconLabel);
        titleLayout->addWidget(titleLabel);
        titleLayout->setSpacing(10); // Set the spacing between the icon and the title label


        // create a widget to hold the list and add it to a layout
        QWidget* centralWidget = new QWidget(this);
        QHBoxLayout* layout1 = new QHBoxLayout(centralWidget);
        layout1->addWidget(configList);
        layout1->setAlignment(Qt::AlignHCenter);
        layout->addRow(titleLayout);
        layout->addRow(layout1);



//        configList->setStyleSheet("background-color: white; font-size: 14px;");
        configList->setStyleSheet("background-color: white; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



//        layout1->addRow(configList);
//        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
//                                  "QListWidget::item { padding: 5px; }"
//                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


        // set the central widget of the main window to the layout
        setCentralWidget(centralWidget);
    });
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

    connect(SPI1, &QAction::triggered, this, [=]() {

        QSettings settings("SPIConfig.txt", QSettings::IniFormat);

        // create the list widget
        QListWidget* configList = new QListWidget(this);
        configList->clear();
        settings.beginGroup("SPI1Configs");

        QString Mode;
        QString NSS;
        QString Frameformat;
        QString Datasize;
        QString Firstbit;

        QString ModeConfig = settings.value("Mode Selected" , Mode).toString();
        QString NSSConfig = settings.value("NSS" , NSS).toString();
        QString FrameformatConfig = settings.value("Frameformat" , Frameformat).toString();
        QString DatasizeConfig = settings.value("Datasize" , Datasize).toString();
        QString FirstbitConfig = settings.value("Firstbit" , Firstbit).toString();


        QListWidgetItem* titleItem = new QListWidgetItem(tr("SPI1 Configurations"), configList);


        QListWidgetItem* ModeItem = new QListWidgetItem(tr("Mode Selected: ") +ModeConfig , configList);
        QListWidgetItem* NSSItem = new QListWidgetItem(tr("NSS: ") +NSSConfig , configList);
        QListWidgetItem* FrameformatItem = new QListWidgetItem(tr("Frameformat: ") +FrameformatConfig , configList);
        QListWidgetItem* DatasizeItem = new QListWidgetItem(tr("Datasize: ") +DatasizeConfig , configList);
        QListWidgetItem* FirstbitItem = new QListWidgetItem(tr("Firstbit: ") +FirstbitConfig , configList);



        // Set the font and style sheet for the title label
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 18);

        titleItem->setFont(font);
        titleItem->setTextAlignment(Qt::TopLeftCorner);
        QBrush gray(Qt::gray);
        QBrush white(Qt::white);

        titleItem->setBackground(gray);
        titleItem->setForeground(white);

        ModeItem->setFont(QFont("Helvetica", 12));
        ModeItem->setTextAlignment(Qt::AlignCenter);
        NSSItem->setFont(QFont("Helvetica", 12));
        NSSItem->setTextAlignment(Qt::AlignCenter);
        FrameformatItem->setFont(QFont("Helvetica", 12));
        FrameformatItem->setTextAlignment(Qt::AlignCenter);
        DatasizeItem->setFont(QFont("Helvetica", 12));
        DatasizeItem->setTextAlignment(Qt::AlignCenter);
        FirstbitItem->setFont(QFont("Helvetica", 12));
        FirstbitItem->setTextAlignment(Qt::AlignCenter);


        configList->setSpacing(15);
        configList->addItem(titleItem);

        configList->addItem(ModeItem);
        configList->addItem(NSSItem);
        configList->addItem(FrameformatItem);
        configList->addItem(DatasizeItem);
        configList->addItem(FirstbitItem);



        configList->show();

        settings.endGroup();

        // Create Layout form
        QFormLayout* layout = new QFormLayout(this);

        // Create a QLabel for "DAC configurations" and center it horizontally
        QLabel* titleLabel = new QLabel("UART4 configurations", this);

        // Load the icon image
        QPixmap icon("C:/Users/nawledbr/Documents/Serial_Port_COM/config7.png");

        // Create a QLabel for the icon and set its size
        QLabel* iconLabel = new QLabel(this);
        iconLabel->setPixmap(icon.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        iconLabel->setFixedSize(30, 30);

        QHBoxLayout* titleLayout = new QHBoxLayout();
        titleLayout->addWidget(iconLabel);
        titleLayout->addWidget(titleLabel);
        titleLayout->setSpacing(10); // Set the spacing between the icon and the title label


        // create a widget to hold the list and add it to a layout
        QWidget* centralWidget = new QWidget(this);
        QHBoxLayout* layout1 = new QHBoxLayout(centralWidget);
        layout1->addWidget(configList);
        layout1->setAlignment(Qt::AlignHCenter);
        layout->addRow(titleLayout);
        layout->addRow(layout1);



//        configList->setStyleSheet("background-color: white; font-size: 14px;");
        configList->setStyleSheet("background-color: white; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



//        layout1->addRow(configList);
//        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
//                                  "QListWidget::item { padding: 5px; }"
//                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


        // set the central widget of the main window to the layout
        setCentralWidget(centralWidget);
    });


    connect(SPI2, &QAction::triggered, this, [=]() {

        QSettings settings("SPIConfig.txt", QSettings::IniFormat);

        // create the list widget
        QListWidget* configList = new QListWidget(this);
        configList->clear();
        settings.beginGroup("SPI2Configs");

        QString Mode;
        QString NSS;
        QString Frameformat;
        QString Datasize;
        QString Firstbit;

        QString ModeConfig = settings.value("Mode" , Mode).toString();
        QString NSSConfig = settings.value("NSS" , NSS).toString();
        QString FrameformatConfig = settings.value("Frameformat" , Frameformat).toString();
        QString DatasizeConfig = settings.value("Datasize" , Datasize).toString();
        QString FirstbitConfig = settings.value("Firstbit" , Firstbit).toString();


        QListWidgetItem* titleItem = new QListWidgetItem(tr("SPI2 Configurations"), configList);


        QListWidgetItem* ModeItem = new QListWidgetItem(tr("Mode Selected: ") +ModeConfig , configList);
        QListWidgetItem* NSSItem = new QListWidgetItem(tr("NSS: ") +NSSConfig , configList);
        QListWidgetItem* FrameformatItem = new QListWidgetItem(tr("Frameformat: ") +FrameformatConfig , configList);
        QListWidgetItem* DatasizeItem = new QListWidgetItem(tr("Datasize: ") +DatasizeConfig , configList);
        QListWidgetItem* FirstbitItem = new QListWidgetItem(tr("Firstbit: ") +FirstbitConfig , configList);


        // Set the font and style sheet for the title label
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 18);

        titleItem->setFont(font);
        titleItem->setTextAlignment(Qt::TopLeftCorner);
        QBrush gray(Qt::gray);
        QBrush white(Qt::white);

        titleItem->setBackground(gray);
        titleItem->setForeground(white);

        ModeItem->setFont(QFont("Helvetica", 12));
        ModeItem->setTextAlignment(Qt::AlignCenter);
        NSSItem->setFont(QFont("Helvetica", 12));
        NSSItem->setTextAlignment(Qt::AlignCenter);
        FrameformatItem->setFont(QFont("Helvetica", 12));
        FrameformatItem->setTextAlignment(Qt::AlignCenter);
        DatasizeItem->setFont(QFont("Helvetica", 12));
        DatasizeItem->setTextAlignment(Qt::AlignCenter);
        FirstbitItem->setFont(QFont("Helvetica", 12));
        FirstbitItem->setTextAlignment(Qt::AlignCenter);


        configList->setSpacing(15);
        configList->addItem(titleItem);

        configList->addItem(ModeItem);
        configList->addItem(NSSItem);
        configList->addItem(FrameformatItem);
        configList->addItem(DatasizeItem);
        configList->addItem(FirstbitItem);


        configList->show();

        settings.endGroup();

//        ModeItem->set("font: bold 15px; color: black; background-color: white;");


        // Create Layout form
        QFormLayout* layout = new QFormLayout(this);

        // Create a QLabel for "DAC configurations" and center it horizontally
        QLabel* titleLabel = new QLabel("UART4 configurations", this);

        // Load the icon image
        QPixmap icon("C:/Users/nawledbr/Documents/Serial_Port_COM/config7.png");

        // Create a QLabel for the icon and set its size
        QLabel* iconLabel = new QLabel(this);
        iconLabel->setPixmap(icon.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        iconLabel->setFixedSize(30, 30);

        QHBoxLayout* titleLayout = new QHBoxLayout();
        titleLayout->addWidget(iconLabel);
        titleLayout->addWidget(titleLabel);
        titleLayout->setSpacing(10); // Set the spacing between the icon and the title label


        // create a widget to hold the list and add it to a layout
        QWidget* centralWidget = new QWidget(this);
        QHBoxLayout* layout1 = new QHBoxLayout(centralWidget);
        layout1->addWidget(configList);
        layout1->setAlignment(Qt::AlignHCenter);
        layout->addRow(titleLayout);
        layout->addRow(layout1);



//        configList->setStyleSheet("background-color: white; font-size: 14px;");
        configList->setStyleSheet("background-color: white; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



//        layout1->addRow(configList);
//        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
//                                  "QListWidget::item { padding: 5px; }"
//                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


        // set the central widget of the main window to the layout
        setCentralWidget(centralWidget);
    });


    connect(SPI3, &QAction::triggered, this, [=]() {

        QSettings settings("SPIConfig.txt", QSettings::IniFormat);

        // create the list widget
        QListWidget* configList = new QListWidget(this);
        configList->clear();
        settings.beginGroup("SPIConfigs");

        QString Mode;
        QString NSS;
        QString Frameformat;
        QString Datasize;
        QString Firstbit;

        QString ModeConfig = settings.value("Mode" , Mode).toString();
        QString NSSConfig = settings.value("NSS" , NSS).toString();
        QString FrameformatConfig = settings.value("Frameformat" , Frameformat).toString();
        QString DatasizeConfig = settings.value("Datasize" , Datasize).toString();
        QString FirstbitConfig = settings.value("Firstbit" , Firstbit).toString();



        QListWidgetItem* titleItem = new QListWidgetItem(tr("SPI3 Configurations"), configList);

        QListWidgetItem* ModeItem = new QListWidgetItem(tr("Mode: ") +ModeConfig , configList);
        QListWidgetItem* NSSItem = new QListWidgetItem(tr("NSS: ") +NSSConfig , configList);
        QListWidgetItem* FrameformatItem = new QListWidgetItem(tr("Frameformat: ") +FrameformatConfig , configList);
        QListWidgetItem* DatasizeItem = new QListWidgetItem(tr("Datasize: ") +DatasizeConfig , configList);
        QListWidgetItem* FirstbitItem = new QListWidgetItem(tr("Firstbit: ") +FirstbitConfig , configList);


//        QPixmap icon("C:/Users/nawledbr/Documents/Serial_Port_COM/config7.png");

//        // Create a QLabel for the icon and set its size
//        QLabel* iconLabel = new QLabel(this);
//        iconLabel->setPixmap(icon.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
//        iconLabel->setFixedSize(30, 30);

        // Set the font and style sheet for the title label
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 18);

        titleItem->setFont(font);
        titleItem->setTextAlignment(Qt::TopLeftCorner);
        QBrush gray(Qt::gray);
        QBrush white(Qt::white);

        titleItem->setBackground(gray);
        titleItem->setForeground(white);

        ModeItem->setFont(QFont("Helvetica", 12));
        ModeItem->setTextAlignment(Qt::AlignCenter);
        NSSItem->setFont(QFont("Helvetica", 12));
        NSSItem->setTextAlignment(Qt::AlignCenter);
        FrameformatItem->setFont(QFont("Helvetica", 12));
        FrameformatItem->setTextAlignment(Qt::AlignCenter);
        DatasizeItem->setFont(QFont("Helvetica", 12));
        DatasizeItem->setTextAlignment(Qt::AlignCenter);
        FirstbitItem->setFont(QFont("Helvetica", 12));
        FirstbitItem->setTextAlignment(Qt::AlignCenter);


        configList->setSpacing(15);
        configList->addItem(titleItem);

        configList->addItem(ModeItem);
        configList->addItem(NSSItem);
        configList->addItem(FrameformatItem);
        configList->addItem(DatasizeItem);
        configList->addItem(FirstbitItem);

        configList->show();

        settings.endGroup();

        // Create Layout form
        QFormLayout* layout = new QFormLayout(this);

        // Create a QLabel for "DAC configurations" and center it horizontally
        QLabel* titleLabel = new QLabel("UART4 configurations", this);

        // Load the icon image
        QPixmap icon("C:/Users/nawledbr/Documents/Serial_Port_COM/config7.png");

        // Create a QLabel for the icon and set its size
        QLabel* iconLabel = new QLabel(this);
        iconLabel->setPixmap(icon.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        iconLabel->setFixedSize(30, 30);

        QHBoxLayout* titleLayout = new QHBoxLayout();
        titleLayout->addWidget(iconLabel);
        titleLayout->addWidget(titleLabel);
        titleLayout->setSpacing(10); // Set the spacing between the icon and the title label


        // create a widget to hold the list and add it to a layout
        QWidget* centralWidget = new QWidget(this);
        QHBoxLayout* layout1 = new QHBoxLayout(centralWidget);
        layout1->addWidget(configList);
        layout1->setAlignment(Qt::AlignHCenter);
        layout->addRow(titleLayout);
        layout->addRow(layout1);



        configList->setStyleSheet("background-color: #E3E0DF; font-size: 14px; border: 2px solid #ccc; padding: 5px;text-align: center;");
//        configList->setFixedHeight(450);
//        configList->setFixedWidth(550);




//        layout1->addRow(configList);
//        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
//                                  "QListWidget::item { padding: 5px; }"
//                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


        // set the central widget of the main window to the layout
        setCentralWidget(centralWidget);
    });

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

    connect(I2C1, &QAction::triggered, this, [=]() {

        QSettings settings("I2CConfig.txt", QSettings::IniFormat);

        // create the list widget
        QListWidget* configList = new QListWidget(this);
        configList->clear();
        settings.beginGroup("I2C1Configs");

        QString Timing;
        QString Speed;
        QString Frequency;
        QString Rise;
        QString Fall;
        QString Converter;
        QString AnalogFilter;



        QString TimingConfig = settings.value("Timing" , Timing).toString();
        QString SpeedConfig = settings.value("Speed" , Speed).toString();
        QString FrequencyConfig = settings.value("Frequency" , Frequency).toString();
        QString RiseConfig = settings.value("Rise" , Rise).toString();
        QString FallConfig = settings.value("Fall" , Fall).toString();
        QString ConverterConfig = settings.value("Converter" , Converter).toString();
        QString AnalogFilterConfig = settings.value("AnalogFilter" , AnalogFilter).toString();



        QListWidgetItem* titleItem = new QListWidgetItem(tr("I2C1 Configurations"), configList);


        QListWidgetItem* TimingItem = new QListWidgetItem(tr("•  Timing     :     ") +TimingConfig , configList);
        QListWidgetItem* SpeedItem = new QListWidgetItem(tr("•  Speed       :  ") +SpeedConfig , configList);
        QListWidgetItem* FrequencyItem = new QListWidgetItem(tr("•  Frequency     :    ") +FrequencyConfig , configList);
        QListWidgetItem* RiseItem = new QListWidgetItem(tr("•  Rise     :    ") +RiseConfig , configList);
        QListWidgetItem* FallItem = new QListWidgetItem(tr("•  Fall    :    ") +FallConfig , configList);
        QListWidgetItem* ConverterItem = new QListWidgetItem(tr("•  Converter    :    ") +ConverterConfig , configList);
        QListWidgetItem* AnalogFilterItem = new QListWidgetItem(tr("•  AnalogFilter    :    ") +AnalogFilterConfig , configList);


        // Set the font and style sheet for the title label
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 18);

        titleItem->setFont(font);
        titleItem->setTextAlignment(Qt::TopLeftCorner);
        QBrush gray(Qt::gray);
        QBrush white(Qt::white);

        titleItem->setBackground(gray);
        titleItem->setForeground(white);

        TimingItem->setFont(QFont("Helvetica", 13));
        TimingItem->setTextAlignment(Qt::TopLeftCorner);
        SpeedItem->setFont(QFont("Helvetica", 13));
        SpeedItem->setTextAlignment(Qt::TopLeftCorner);
        FrequencyItem->setFont(QFont("Helvetica", 13));
        FrequencyItem->setTextAlignment(Qt::TopLeftCorner);
        RiseItem->setFont(QFont("Helvetica", 13));
        RiseItem->setTextAlignment(Qt::TopLeftCorner);
        FallItem->setFont(QFont("Helvetica", 13));
        FallItem->setTextAlignment(Qt::TopLeftCorner);
        ConverterItem->setFont(QFont("Helvetica", 13));
        ConverterItem->setTextAlignment(Qt::TopLeftCorner);
        AnalogFilterItem->setFont(QFont("Helvetica", 13));
        AnalogFilterItem->setTextAlignment(Qt::TopLeftCorner);


        configList->setSpacing(15);
        configList->addItem(titleItem);

        configList->addItem(TimingItem);
        configList->addItem(SpeedItem);
        configList->addItem(FrequencyItem);
        configList->addItem(RiseItem);
        configList->addItem(FallItem);
        configList->addItem(ConverterItem);
        configList->addItem(AnalogFilterItem);




        configList->show();

        settings.endGroup();

        // Create Layout form
        QFormLayout* layout = new QFormLayout(this);

        // Create a QLabel for "DAC configurations" and center it horizontally
        QLabel* titleLabel = new QLabel("UART4 configurations", this);

        // Load the icon image
        QPixmap icon("C:/Users/nawledbr/Documents/Serial_Port_COM/config7.png");

        // Create a QLabel for the icon and set its size
        QLabel* iconLabel = new QLabel(this);
        iconLabel->setPixmap(icon.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        iconLabel->setFixedSize(30, 30);

        QHBoxLayout* titleLayout = new QHBoxLayout();
        titleLayout->addWidget(iconLabel);
        titleLayout->addWidget(titleLabel);
        titleLayout->setSpacing(10); // Set the spacing between the icon and the title label


        // create a widget to hold the list and add it to a layout
        QWidget* centralWidget = new QWidget(this);
        QHBoxLayout* layout1 = new QHBoxLayout(centralWidget);
        layout1->addWidget(configList);
        layout1->setAlignment(Qt::AlignHCenter);
        layout->addRow(titleLayout);
        layout->addRow(layout1);



//        configList->setStyleSheet("background-color: white; font-size: 14px;");
        configList->setStyleSheet("background-color: white; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



//        layout1->addRow(configList);
//        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
//                                  "QListWidget::item { padding: 5px; }"
//                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


        // set the central widget of the main window to the layout
        setCentralWidget(centralWidget);
    });


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
