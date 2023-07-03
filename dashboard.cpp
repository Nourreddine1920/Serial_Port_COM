#include "dashboard.h"
#include "ui_dashboard.h"
#include <QIcon>
#include <QCheckBox>
#include <QWidgetAction>
#include <QToolButton>
#include "configmode.h"
#include <QProcess>
#include <QStatusBar>


QStringList Dashboard::selectedUartOptionsStatic; // initialisation de la variable statique
QStringList Dashboard::selectedI2COptionsStatic; // initialisation de la variable statique
QStringList Dashboard::selectedSPIOptionsStatic; // initialisation de la variable statique
QStringList Dashboard::selectedADCOptionsStatic; // initialisation de la variable statique
QStringList Dashboard::selectedDACOptionsStatic; // initialisation de la variable statique
QStringList Dashboard::selectedGPIOOptionsStatic; // initialisation de la variable statique
QStringList Dashboard::selectedTIMEROptionsStatic; // initialisation de la variable statique

Dashboard::Dashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("IPs Configurations ");
    // Create a status bar
    QStatusBar *statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
    setFixedSize(width(), height());

    // Create a QLabel for the footer text
    QLabel *footerLabel = new QLabel("© 2023 - ACTIA Engineering Services", this);
    footerLabel->setStyleSheet("background-color: #D3D3D3	; color: #36454F	;");
    footerLabel->setAlignment(Qt::AlignCenter);

    // Set the gray background color
    QPalette palette = footerLabel->palette();
//    palette.setColor(QPalette::Background, QColor(200, 200, 200)); // Adjust the color as desired
    footerLabel->setAutoFillBackground(true);
    footerLabel->setPalette(palette);

    // Add the QLabel to the status bar
    statusBar->addWidget(footerLabel, 1);

    // Set the status bar properties
    statusBar->setSizeGripEnabled(false); // Optional: Disable the size grip handle on the status bar

    //-------------------------IPs Configurations-------------------------//

    // Checkable UART Configurations
    auto *UART4 = new QAction("UART4", this);
  // QAction *action = new QAction("Checkable Action", menuBar());

    UART4->setCheckable(true);
    if (selectedUartOptionsStatic.contains("UART4")) {
        UART4->setChecked(true);
    }

    if(! selectedUartOptionsStatic.contains("UART4"))
    {
        QSettings settings("UARTConfig.txt", QSettings::IniFormat);
        settings.beginGroup("UART4");
        QStringList cles = settings.childKeys();
        for(const QString &cle : cles){
            settings.remove(cle);

        }
        settings.endGroup();


    }







    QAction *UART5 = new QAction("&UART5", this);
    UART5->setCheckable(true);
    if (selectedUartOptionsStatic.contains("&UART5")) {
        UART5->setChecked(true);
    }
    if(! selectedUartOptionsStatic.contains("&UART5"))
    {
        QSettings settings("UARTConfig.txt", QSettings::IniFormat);
        settings.beginGroup("UART5");
        QStringList cles = settings.childKeys();
        for(const QString &cle : cles){
            settings.remove(cle);
        }
        settings.endGroup();


    }




    QAction *UART7 = new QAction("&UART7", this);
    UART7->setCheckable(true);
    if (selectedUartOptionsStatic.contains("&UART7")) {
        UART7->setChecked(true);
    }




    QAction *UART8 = new QAction("&UART8", this);
    UART8->setCheckable(true);
    if (selectedUartOptionsStatic.contains("&UART8")) {
        UART8->setChecked(true);
    }






    QAction *UART9 = new QAction("&UART9", this);
    UART9->setCheckable(true);
    if (selectedUartOptionsStatic.contains("&UART9")) {
        UART9->setChecked(true);
    }

    QAction *USART1 = new QAction("&USART1", this);
    USART1->setCheckable(true);
    if (selectedUartOptionsStatic.contains("&USART1")) {
        USART1->setChecked(true);
    }
    if(! selectedUartOptionsStatic.contains("&SUART1"))
    {
        QSettings settings("UARTConfig.txt", QSettings::IniFormat);
        settings.beginGroup("USART1");
        QStringList cles = settings.childKeys();
        for(const QString &cle : cles){
            settings.remove(cle);
        }
        settings.endGroup();


    }



    QAction *USART2 = new QAction("&USART2", this);
   USART2->setCheckable(true);
   if (selectedUartOptionsStatic.contains("&USART2")) {
       USART2->setChecked(true);
   }
   if(! selectedUartOptionsStatic.contains("&USART2"))
   {
       QSettings settings("UARTConfig.txt", QSettings::IniFormat);
       settings.beginGroup("USART2");
       QStringList cles = settings.childKeys();
       for(const QString &cle : cles){
           settings.remove(cle);
       }
       settings.endGroup();


   }

    QAction *USART6 = new QAction("&USART6", this);
    USART6->setCheckable(true);
    if (selectedUartOptionsStatic.contains("&USART6")) {
        USART6->setChecked(true);
    }

    QAction *USART10 = new QAction("&USART10", this);
    USART10->setCheckable(true);
    if (selectedUartOptionsStatic.contains("&USART10")) {
        USART10->setChecked(true);
    }






    // Checkable SPI Configurations
    QAction *SPI1 = new QAction("SPI1", this);
    SPI1->setCheckable(true);
    if (selectedSPIOptionsStatic.contains("SPI1")) {
        SPI1->setChecked(true);
    }
    if(! selectedSPIOptionsStatic.contains("SPI1"))
    {
        QSettings settings("SPIConfig.txt", QSettings::IniFormat);
        settings.beginGroup("SPI1");
        QStringList cles = settings.childKeys();
        for(const QString &cle : cles){
            settings.remove(cle);
        }
        settings.endGroup();


    }



    QAction *SPI2 = new QAction("&SPI2", this);
    SPI2->setCheckable(true);
    if (selectedSPIOptionsStatic.contains("&SPI2")) {
        SPI2->setChecked(true);
    }

    if(! selectedSPIOptionsStatic.contains("&SPI2"))
    {
        QSettings settings("SPIConfig.txt", QSettings::IniFormat);
        settings.beginGroup("SPI2");
        QStringList cles = settings.childKeys();
        for(const QString &cle : cles){
            settings.remove(cle);
        }
        settings.endGroup();


    }

    QAction *SPI3 = new QAction("&SPI3", this);
    SPI3->setCheckable(true);
    if (selectedSPIOptionsStatic.contains("&SPI3")) {
        SPI3->setChecked(true);
    }


    QAction *SPI4 = new QAction("&SPI4", this);
    SPI4->setCheckable(true);
    if (selectedSPIOptionsStatic.contains("&SPI4")) {
        SPI4->setChecked(true);
    }


    QAction *SPI5 = new QAction("&SPI5", this);
    SPI5->setCheckable(true);
    if (selectedSPIOptionsStatic.contains("&SPI5")) {
        SPI5->setChecked(true);
    }


    QAction *SPI6 = new QAction("&SPI6", this);
    SPI6->setCheckable(true);
    if (selectedSPIOptionsStatic.contains("&SPI6")) {
        SPI6->setChecked(true);
    }


    // Checkable I2C Configurations
    QAction *I2C1 = new QAction("I2C1", this);
    I2C1->setCheckable(true);
    if (selectedI2COptionsStatic.contains("I2C1")) {
        I2C1->setChecked(true);
    }
    if(! selectedI2COptionsStatic.contains("I2C1"))
    {
        QSettings settings("I2CConfig.txt", QSettings::IniFormat);
        settings.beginGroup("I2C1");
        QStringList cles = settings.childKeys();
        for(const QString &cle : cles){
            settings.remove(cle);
        }
        settings.endGroup();


    }



    QAction *I2C2 = new QAction("&I2C2", this);
    I2C2->setCheckable(true);
    if (selectedI2COptionsStatic.contains("&I2C2")) {
        I2C2->setChecked(true);
    }
    if(! selectedI2COptionsStatic.contains("&I2C2"))
    {
        QSettings settings("I2CConfig.txt", QSettings::IniFormat);
        settings.beginGroup("I2C2");
        QStringList cles = settings.childKeys();
        for(const QString &cle : cles){
            settings.remove(cle);
        }
        settings.endGroup();
}




    QAction *I2C3 = new QAction("&I2C3", this);
    I2C3->setCheckable(true);
    if (selectedI2COptionsStatic.contains("&I2C3")) {
        I2C3->setChecked(true);
    }

    QAction *I2C4 = new QAction("&I2C4", this);
    I2C4->setCheckable(true);
    if (selectedI2COptionsStatic.contains("&I2C4")) {
        I2C4->setChecked(true);
    }

    QAction *I2C5 = new QAction("&I2C5", this);
    I2C5->setCheckable(true);
    if (selectedI2COptionsStatic.contains("&I2C5")) {
        I2C5->setChecked(true);
    }

    // Checkable ADC Configurations
    QAction *ADC1 = new QAction("ADC1", this);
    ADC1->setCheckable(true);
    if (selectedADCOptionsStatic.contains("ADC1")) {
        ADC1->setChecked(true);
    }
    if(! selectedADCOptionsStatic.contains("ADC1"))
    {
        QSettings settings("ADCConfig.txt", QSettings::IniFormat);
        settings.beginGroup("ADC1");
        QStringList cles = settings.childKeys();
        for(const QString &cle : cles){
            settings.remove(cle);
        }
        settings.endGroup();

}



    QAction *ADC2 = new QAction("&ADC2", this);
    ADC2->setCheckable(true);
    if (selectedADCOptionsStatic.contains("&ADC2")) {
        ADC2->setChecked(true);
    }


    QAction *ADC3 = new QAction("&ADC3", this);
    ADC3->setCheckable(true);
    if (selectedADCOptionsStatic.contains("&ADC3")) {
        ADC3->setChecked(true);
    }
    if(! selectedADCOptionsStatic.contains("&ADC3"))
    {
        QSettings settings("ADCConfig.txt", QSettings::IniFormat);
        settings.beginGroup("ADC3");
        QStringList cles = settings.childKeys();
        for(const QString &cle : cles){
            settings.remove(cle);
        }
        settings.endGroup();

}


    // Checkable DAC Configurations
    QAction *DAC_OUT1 = new QAction("DAC_OUT1", this);
    DAC_OUT1->setCheckable(true);
    if (selectedDACOptionsStatic.contains("DAC_OUT1")) {
        DAC_OUT1->setChecked(true);
    }

    if(! selectedDACOptionsStatic.contains("DAC_OUT1"))
    {
        QSettings settings("DACConfig.txt", QSettings::IniFormat);
        settings.beginGroup("DAC1");
        QStringList cles = settings.childKeys();
        for(const QString &cle : cles){
            settings.remove(cle);
        }
        settings.endGroup();
    }
    QAction *DAC_OUT2 = new QAction("DAC_OUT2", this);
    DAC_OUT2->setCheckable(true);
    if (selectedDACOptionsStatic.contains("DAC_OUT2")) {
        DAC_OUT2->setChecked(true);
    }




    // Checkable Input Capture Mode Configurations
    QAction *InputCaptureMode = new QAction("Input Capture Mode" , this);
    InputCaptureMode->setCheckable(true);
    if (selectedTIMEROptionsStatic.contains("Input Capture Mode")) {
       InputCaptureMode->setChecked(true);
    }
    if(! selectedTIMEROptionsStatic.contains("Input Capture Mode"))
      {
          QSettings settings("FrequencyMesureConfig.txt", QSettings::IniFormat);
          settings.beginGroup("Mesure_Frequency");
          QStringList cles = settings.childKeys();
          for(const QString &cle : cles){
              settings.remove(cle);
          }
          settings.endGroup();

}

    // Checkable GPIO Mode Configurations

    QAction *GPIO_OUTPUT = new QAction("GPIO_OUTPUT" , this);
    GPIO_OUTPUT->setCheckable(true);
    if (selectedGPIOOptionsStatic.contains("GPIO_OUTPUT")) {
       GPIO_OUTPUT->setChecked(true);
    }
    if(! selectedADCOptionsStatic.contains("GPIO_OUTPUT"))
      {
          QSettings settings("GPIOConfig.txt", QSettings::IniFormat);
          settings.beginGroup("GPIO_OUTPUT");
          QStringList cles = settings.childKeys();
          for(const QString &cle : cles){
              settings.remove(cle);
          }
          settings.endGroup();
    }

    QAction *GPIO_INPUT = new QAction("&GPIO_INPUT" , this);
    GPIO_INPUT->setCheckable(true);
    if (selectedGPIOOptionsStatic.contains("&GPIO_INPUT")) {
       GPIO_INPUT->setChecked(true);
    }

    if(! selectedADCOptionsStatic.contains("GPIO_INPUT"))
      {
          QSettings settings("GPIOConfig.txt", QSettings::IniFormat);
          settings.beginGroup("GPIO_INPUT");
          QStringList cles = settings.childKeys();
          for(const QString &cle : cles){
              settings.remove(cle);
          }
          settings.endGroup();
    }

    // Create a QToolButton for the "Connect" button
    QToolButton *connectButton = new QToolButton(this);
    connectButton->setIcon(QIcon("C:/Users/nawledbr/Documents/Serial_Port_COM/download.png"));
    connectButton->setText(tr("&Connect"));
    connectButton->setStyleSheet("font: Helvetica gras 20px; padding: 18px; width: 500px;");
    connectButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    // Connect the QToolButton's clicked() signal to a slot that will open the new UI
    connect(connectButton, &QToolButton::clicked, this, &Dashboard::showConfigMode);








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






            // Create a QString with your menu bar and QToolButton styles
            QString style = "\
                QMenuBar {\
                    background-color: #868482;\
                    spacing: 20px;\
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
    connect(UART4, &QAction::triggered, this, &Dashboard::UART4Config);
    connect(UART5, &QAction::triggered, this, &Dashboard::UART5Config);
    connect(UART7, &QAction::triggered, this, &Dashboard::UARTConfig);
    connect(UART8, &QAction::triggered, this, &Dashboard::UARTConfig);

    connect(UART9, &QAction::triggered, this, &Dashboard::UARTConfig);

    connect(USART1, &QAction::triggered, this, &Dashboard::USART1Config);

    connect(USART2, &QAction::triggered, this, &Dashboard::USART2Config);

    connect(USART6, &QAction::triggered, this, &Dashboard::UARTConfig);

    connect(USART10, &QAction::triggered, this,&Dashboard::UARTConfig);


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
    connect(SPI1, &QAction::triggered, this, &Dashboard::SPI1Config);
    connect(SPI2, &QAction::triggered, this, &Dashboard::SPI2Config);
    connect(SPI3, &QAction::triggered, this, &Dashboard::SPIConfig);
    connect(SPI4, &QAction::triggered, this, &Dashboard::SPIConfig);

    connect(SPI5, &QAction::triggered, this, &Dashboard::SPIConfig);

    connect(SPI6, &QAction::triggered, this, &Dashboard::SPIConfig);

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
    connect(I2C1, &QAction::triggered, this, &Dashboard::I2C1Config);
    connect(I2C2, &QAction::triggered, this, &Dashboard::I2C2Config);
    connect(I2C3, &QAction::triggered, this, &Dashboard::I2CConfig);
    connect(I2C4, &QAction::triggered, this, &Dashboard::I2CConfig);

    connect(I2C5, &QAction::triggered, this, &Dashboard::I2CConfig);


    //-------------------------Connect to the ADC configurations-------------------------//


    ADC->addAction(ADC1);
    ADC->addSeparator();

    ADC->addAction(ADC2);
    ADC->addSeparator();

    ADC->addAction(ADC3);
    ADC->addSeparator();




    connect(ADC1, &QAction::triggered, this, &Dashboard::ADC1Config);
    connect(ADC2, &QAction::triggered, this, &Dashboard::ADCConfig);
    connect(ADC3, &QAction::triggered, this, &Dashboard::ADC3Config);


    //-------------------------Connect to the DAC configurations-------------------------//


    DAC->addAction(DAC_OUT1);
    DAC->addSeparator();
    DAC->addAction(DAC_OUT2);
    DAC->addSeparator();


    connect(DAC_OUT1, &QAction::triggered, this, &Dashboard::DACOUT1Config);
    connect(DAC_OUT2, &QAction::triggered, this, &Dashboard::DACOUT2Config);


    //-------------------------Connect to the GPIO configurations-------------------------//


    GPIO->addAction(GPIO_OUTPUT);
    GPIO->addSeparator();
    GPIO->addAction(GPIO_INPUT);
    GPIO->addSeparator();


    connect(GPIO_OUTPUT, &QAction::triggered, this, &Dashboard::GPIOOUPUTConfig);
    connect(GPIO_INPUT, &QAction::triggered, this, &Dashboard::GPIOINPUTConfig);


    //-------------------------Connect to the TIMER configurations-------------------------//

    TIMER->addAction(InputCaptureMode);
    TIMER->addSeparator();

    // Connect to the TIMER configurations
    connect(InputCaptureMode, &QAction::triggered, this, &Dashboard::FrequencyMesureConfig);



    //--------------------------Different IP selection for ConfigMode UI----------------------//

        connect(UART4, &QAction::triggered, this, &Dashboard::onUartOptionSelected);
        connect(UART5, &QAction::triggered, this, &Dashboard::onUartOptionSelected);
        connect(UART7, &QAction::triggered, this, &Dashboard::onUartOptionSelected);
        connect(UART8, &QAction::triggered, this, &Dashboard::onUartOptionSelected);
        connect(UART9, &QAction::triggered, this, &Dashboard::onUartOptionSelected);
        connect(USART1, &QAction::triggered, this, &Dashboard::onUartOptionSelected);
        connect(USART2, &QAction::triggered, this, &Dashboard::onUartOptionSelected);
        connect(USART6, &QAction::triggered, this, &Dashboard::onUartOptionSelected);
        connect(USART10, &QAction::triggered, this, &Dashboard::onUartOptionSelected);

        connect(I2C1, &QAction::triggered, this, &Dashboard::onI2COptionSelected);
        connect(I2C2, &QAction::triggered, this, &Dashboard::onI2COptionSelected);
        connect(I2C3, &QAction::triggered, this, &Dashboard::onI2COptionSelected);
        connect(I2C4, &QAction::triggered, this, &Dashboard::onI2COptionSelected);
        connect(I2C5, &QAction::triggered, this, &Dashboard::onI2COptionSelected);



       connect(SPI1, &QAction::triggered, this, &Dashboard::onSPIOptionSelected);
       connect(SPI2, &QAction::triggered, this, &Dashboard::onSPIOptionSelected);
       connect(SPI3, &QAction::triggered, this, &Dashboard::onSPIOptionSelected);
       connect(SPI4, &QAction::triggered, this, &Dashboard::onSPIOptionSelected);
       connect(SPI5, &QAction::triggered, this, &Dashboard::onSPIOptionSelected);
       connect(SPI6, &QAction::triggered, this, &Dashboard::onSPIOptionSelected);

       connect(ADC1, &QAction::triggered, this, &Dashboard::onADCOptionSelected);
       connect(ADC2, &QAction::triggered, this, &Dashboard::onADCOptionSelected);
       connect(ADC3, &QAction::triggered, this, &Dashboard::onADCOptionSelected);

       connect(DAC_OUT1, &QAction::triggered, this, &Dashboard::onDACOptionSelected);
       connect(DAC_OUT2, &QAction::triggered, this, &Dashboard::onDACOptionSelected);


      connect(GPIO_OUTPUT, &QAction::triggered, this, &Dashboard::onGPIOOptionSelected);
      connect(GPIO_INPUT, &QAction::triggered, this, &Dashboard::onGPIOOptionSelected);

      connect(InputCaptureMode, &QAction::triggered, this, &Dashboard::onTIMEROptionSelected);




}


void Dashboard::showConfigMode()
{
    ConfigMode *configMode = new ConfigMode();
    QSet<QString> addedUartOptions;
        QSet<QString> addedI2COptions;
        QSet<QString> addedSPIOptions;
        QSet<QString> addedADCOptions;
        QSet<QString> addedDACOptions;
        QSet<QString> addedGPIOOptions;
        QSet<QString> addedTIMEROptions;


        // Parcourir chaque élément sélectionné
        for (int i = 0; i < selectedUartOptionsStatic.size(); i++) {
            QString uartOption = selectedUartOptionsStatic.at(i);
            if (!addedUartOptions.contains(uartOption)) {
                  configMode->addActionToMenu("&UART", uartOption);
                  addedUartOptions.insert(uartOption);


                   }




        }






        for (int i = 0; i < selectedI2COptionsStatic.size(); i++) {
            QString I2COption = selectedI2COptionsStatic.at(i);
            // Vérifier si l'élément a déjà été ajouté pour I2C
                  if (!addedI2COptions.contains(I2COption)) {
                      configMode->addActionToMenu("&I2C", I2COption);
                      addedI2COptions.insert(I2COption);
                  }
        }
        for (int i = 0; i < selectedSPIOptionsStatic.size(); i++) {
            QString SPIOption = selectedSPIOptionsStatic.at(i);
                  if (!addedSPIOptions.contains(SPIOption)) {
                      configMode->addActionToMenu("&SPI", SPIOption);
                      addedSPIOptions.insert(SPIOption);
                  }
        }

        for (int i = 0; i < selectedADCOptionsStatic.size(); i++) {
            QString ADCOption = selectedADCOptionsStatic.at(i);
            if (!addedADCOptions.contains(ADCOption)) {
               configMode->addActionToMenu("&ADC", ADCOption);
                addedADCOptions.insert(ADCOption);
            }

        }

        for (int i = 0; i < selectedDACOptionsStatic.size(); i++) {
            QString DACOption = selectedDACOptionsStatic.at(i);
            if (!addedDACOptions.contains(DACOption)) {
               configMode->addActionToMenu("&DAC", DACOption);
                addedDACOptions.insert(DACOption);
            }
        }

        for (int i = 0; i < selectedGPIOOptionsStatic.size(); i++) {
            QString GPIOOption = selectedGPIOOptionsStatic.at(i);
            if (!addedGPIOOptions.contains(GPIOOption)) {
               configMode->addActionToMenu("&GPIO", GPIOOption);
                addedGPIOOptions.insert(GPIOOption);
            }
        }

        for (int i = 0; i < selectedTIMEROptionsStatic.size(); i++) {
            QString TIMEROption = selectedTIMEROptionsStatic.at(i);
            if (!addedTIMEROptions.contains(TIMEROption)) {
              configMode->addActionToMenu("&Frequency Mesure", TIMEROption);
                addedTIMEROptions.insert(TIMEROption);
            }

        }



//        QString program = "C:/Program Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI.exe"; // Chemin vers le programme cubeprogrammer


//        //         Commande pour l'écriture du fichier
//                QStringList writeArguments;
//                writeArguments << "-c" << "port=swd" << "-w" << "C:/Users/nawledbr/Desktop/testBins/read.bin" << "0x08000000";
//                QProcess writeProcess;
//                writeProcess.start(program, writeArguments);
//        //        writeProcess.startDetached(program, writeArguments);

//                writeProcess.waitForFinished(-1);

//                if (writeProcess.exitStatus() == QProcess::NormalExit && writeProcess.exitCode() == 0)
//                {
//                QStringList startArguments;
//                startArguments << "-c" << "port=swd" << "--start" << "0x08000000";
//                QProcess startProcess;
//                startProcess.start(program, startArguments);
//                startProcess.startDetached(program, startArguments);

//                startProcess.waitForFinished(-1);

//                // Vérifier si la commande s'est terminée avec succès
//                if (startProcess.exitStatus() == QProcess::NormalExit && startProcess.exitCode() == 0)
//                {
//                // Passer à la page "Run Mode"


//        //            /******************************* getting notification ***************************************/



//                    QString styleSheet = "\
//                        QMessageBox {\
//                            background-color: #D3D3D3;\
//                            color: #263238;\
//                            font-family:Fantasy ;\
//                            font-size: 12px;\
//                        }\
//                        \
//                        QMessageBox QLabel {\
//                            color: #000000	;\
//                        }\
//                        \
//                        QMessageBox QPushButton {\
//                            background-color: #4CAF50;\
//                            border: 1px solid #388E3C;\
//                            color: #FFFFFF;\
//                            padding: 5px;\
//                            min-width: 70px;\
//                        }\
//                        \
//                        QMessageBox QPushButton:hover {\
//                            background-color: #388E3C;\
//                        }";


//                            QMessageBox msgBox;
//                            msgBox.setWindowTitle("Runnig Program");
//                            msgBox.setStyleSheet(styleSheet);
//                            msgBox.setIcon(QMessageBox::Information);
//                            msgBox.setText("Start Program achieved successfully !");
//                            msgBox.exec();




                    configMode->show();
                    this->hide();

//        // ...
//        }
//        }

//        else{
//                    QString styleSheet = "\
//                        QMessageBox {\
//                            background-color: #D3D3D3;\
//                            color: #263238;\
//                            font-family:Fantasy ;\
//                            font-size: 12px;\
//                        }\
//                        \
//                        QMessageBox QLabel {\
//                            color: #000000	;\
//                        }\
//                        \
//                        QMessageBox QPushButton {\
//                            background-color: #4CAF50;\
//                            border: 1px solid #388E3C;\
//                            color: #FFFFFF;\
//                            padding: 5px;\
//                            min-width: 70px;\
//                        }\
//                        \
//                        QMessageBox QPushButton:hover {\
//                            background-color: #388E3C;\
//                        }";


//                            QMessageBox msgBox;
//                            msgBox.setWindowTitle("Runnig Program");
//                            msgBox.setStyleSheet(styleSheet);
//                            msgBox.setIcon(QMessageBox::Information);
//                            msgBox.setText("Start Program Occured an error ! there is another program running on the board ");
//                            msgBox.exec();

//                }


}
void Dashboard::onUartOptionSelected()
{

 QAction *action = qobject_cast<QAction *>(sender());
       if (action) {
        QString uartOption = action->text();
        // Vérifier si l'option UART est déjà sélectionnée
        if ( selectedUartOptionsStatic.contains(uartOption)) {
            // Si elle est déjà sélectionnée, la retirer de la liste et décocher l'action
             selectedUartOptionsStatic.removeOne(uartOption);
            action->setChecked(false);

        } else {
            // Si elle n'est pas déjà sélectionnée, l'ajouter à la liste et cocher l'action
             selectedUartOptionsStatic.append(uartOption);
            action->setChecked(true);

        }

       }


}
void Dashboard::onI2COptionSelected()
{
   QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        QString I2COption = action->text();

        if ( selectedI2COptionsStatic.contains(I2COption)) {

             selectedI2COptionsStatic.removeOne(I2COption);
            action->setChecked(false);

        } else {

             selectedI2COptionsStatic.append(I2COption);
            action->setChecked(true);

        }

    }
}

void Dashboard::onSPIOptionSelected()
{
   QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        QString SPIOption = action->text();
        // Vérifier si l'option UART est déjà sélectionnée
        if ( selectedSPIOptionsStatic.contains(SPIOption)) {
            // Si elle est déjà sélectionnée, la retirer de la liste et décocher l'action
             selectedSPIOptionsStatic.removeOne(SPIOption);
            action->setChecked(false);

        } else {
            // Si elle n'est pas déjà sélectionnée, l'ajouter à la liste et cocher l'action
             selectedSPIOptionsStatic.append(SPIOption);
            action->setChecked(true);

        }

    }
}

void Dashboard::onADCOptionSelected()
{
   QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        QString ADCOption = action->text();
        // Vérifier si l'option UART est déjà sélectionnée
        if ( selectedADCOptionsStatic.contains(ADCOption)) {
            // Si elle est déjà sélectionnée, la retirer de la liste et décocher l'action
             selectedADCOptionsStatic.removeOne(ADCOption);
            action->setChecked(false);

        } else {
            // Si elle n'est pas déjà sélectionnée, l'ajouter à la liste et cocher l'action
             selectedADCOptionsStatic.append(ADCOption);
            action->setChecked(true);

        }

    }
}

void Dashboard::onDACOptionSelected()
{
   QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        QString DACOption = action->text();
        // Vérifier si l'option UART est déjà sélectionnée
        if ( selectedDACOptionsStatic.contains(DACOption)) {
            // Si elle est déjà sélectionnée, la retirer de la liste et décocher l'action
             selectedDACOptionsStatic.removeOne(DACOption);
            action->setChecked(false);

        } else {
            // Si elle n'est pas déjà sélectionnée, l'ajouter à la liste et cocher l'action
             selectedDACOptionsStatic.append(DACOption);
            action->setChecked(true);

        }

    }
}
void Dashboard::onGPIOOptionSelected()
{
   QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        QString GPIOOption = action->text();
        // Vérifier si l'option UART est déjà sélectionnée
        if ( selectedGPIOOptionsStatic.contains(GPIOOption)) {
            // Si elle est déjà sélectionnée, la retirer de la liste et décocher l'action
             selectedGPIOOptionsStatic.removeOne(GPIOOption);
            action->setChecked(false);

        } else {
            // Si elle n'est pas déjà sélectionnée, l'ajouter à la liste et cocher l'action
             selectedGPIOOptionsStatic.append(GPIOOption);
            action->setChecked(true);

        }

    }
}

void Dashboard::onTIMEROptionSelected()
{
   QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        QString TIMEROption = action->text();
        // Vérifier si l'option UART est déjà sélectionnée
        if ( selectedTIMEROptionsStatic.contains(TIMEROption)) {
            // Si elle est déjà sélectionnée, la retirer de la liste et décocher l'action
             selectedTIMEROptionsStatic.removeOne(TIMEROption);
            action->setChecked(false);

        } else {
            // Si elle n'est pas déjà sélectionnée, l'ajouter à la liste et cocher l'action
             selectedTIMEROptionsStatic.append(TIMEROption);
            action->setChecked(true);

        }

    }
}

Dashboard::~Dashboard()
{
    delete ui;
}
