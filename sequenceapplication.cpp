#include "sequenceapplication.h"
#include "ui_sequenceapplication.h"
#include "runmode.h"
#include "ui_runmode.h"
#include "dashboard.h"
#include <QIcon>
#include <QCheckBox>
#include <QWidgetAction>
#include <QToolButton>
#include"uart.h"
#include "configmode.h"
#include <QStatusBar>


sequenceApplication::sequenceApplication(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sequenceApplication)
{
    ui->setupUi(this);

    QWidget::setWindowTitle("Sequence Application");
    // Create a status bar
    QStatusBar *statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    // Create a QLabel for the footer text
    QLabel *footerLabel = new QLabel("© 2023 - ACTIA Engineering Services", this);
    footerLabel->setStyleSheet("background-color: #D3D3D3; color: #36454F;");
    footerLabel->setAlignment(Qt::AlignCenter);
    // Appliquer le style au QListWidget
    QString listStyle = "\
    QListWidget {\
    background-color: #D3D3D3; /* Couleur de fond */\
    color: #000000; /* Couleur du texte */\
    border: 1px solid #C0C0C0; /* Bordure */\
    }\
    QListWidget::item {\
    background-color: #FFFFFF; /* Couleur de fond des éléments */\
    padding: 5px; /* Espacement intérieur */\
    }\
    QListWidget::item:selected {\
    background-color: #328930; /* Couleur de fond des éléments sélectionnés */\
    color: #FFFFFF; /* Couleur du texte des éléments sélectionnés */\
    }";

    ui->listWidget->setStyleSheet(listStyle);



    // Set the gray background color
    QPalette palette = footerLabel->palette();
//    palette.setColor(QPalette::Background, QColor(200, 200, 200)); // Adjust the color as desired
    footerLabel->setAutoFillBackground(true);
    footerLabel->setPalette(palette);

    // Add the QLabel to the status bar
    statusBar->addWidget(footerLabel, 1);

    // Set the status bar properties
    statusBar->setSizeGripEnabled(false); // Optional: Disable the size grip handle on the status bar
    Uart* uart = Uart::getInstance();
    QSerialPort* serialPort = uart->getSerialPort();




    // Create a QToolButton for the "Connect" button
    QToolButton *connectButton = new QToolButton(this);
    connectButton->setIcon(QIcon("C:/Users/nawledbr/Documents/Serial_Port_COM/debug1.png"));
    connectButton->setText(tr("&Run Configs"));
    connectButton->setStyleSheet("font: Helvetica gras 20px; padding: 18px; width: 500px;");
    connectButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    // Connect the QToolButton's clicked() signal to a slot that will open the new UI
//    connect(connectButton, &QToolButton::clicked, this, &sequenceApplication::sendRUNframe);

    QToolButton *returnButton = new QToolButton(this);
    returnButton->setIcon(QIcon("C:/Users/nawledbr/Documents/Serial_Port_COM/back-arrow.png"));
    returnButton->setText(tr("&Return"));
    returnButton->setStyleSheet("font: Helvetica gras 20px; padding: 18px; width: 500px;");
    returnButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    connect(returnButton, &QToolButton::clicked, this, &sequenceApplication::returnDashboard);





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



    connect(action, &QAction::triggered, this, &sequenceApplication::onSubMenuSelected);

//    QString menuItem;

//    connect(menuItem, &QAction::triggered, this, &sequenceApplication::onSubMenuItemSelected);

}

void sequenceApplication::returnDashboard()
{
    ConfigMode *configmode = new ConfigMode();
    QSettings settings("configSelection", QSettings::IniFormat);
    QAction *action = new QAction(this);

    QString actionUART4 = action->text();
    settings.setValue("actionUART4" , actionUART4);
    qDebug() << "selected uart:" << actionUART4;
//    qDebug() << "configselected:" << TimingConfig;

    QSet<QString> addedUartOptions;
        QSet<QString> addedI2COptions;
        QSet<QString> addedSPIOptions;
        QSet<QString> addedADCOptions;
        QSet<QString> addedDACOptions;
        QSet<QString> addedGPIOOptions;
        QSet<QString> addedTIMEROptions;


        // Parcourir chaque élément sélectionné
        for (int i = 0; i < Dashboard::selectedUartOptionsStatic.size(); i++) {
            QString uartOption = Dashboard::selectedUartOptionsStatic.at(i);
            if (!addedUartOptions.contains(uartOption)) {
                  configmode->addActionToMenu("&UART", uartOption);
                  addedUartOptions.insert(uartOption);


                   }




        }






        for (int i = 0; i < Dashboard::selectedI2COptionsStatic.size(); i++) {
            QString I2COption = Dashboard::selectedI2COptionsStatic.at(i);
            // Vérifier si l'élément a déjà été ajouté pour I2C
                  if (!addedI2COptions.contains(I2COption)) {
                      configmode->addActionToMenu("&I2C", I2COption);
                      addedI2COptions.insert(I2COption);
                  }
        }
        for (int i = 0; i < Dashboard::selectedSPIOptionsStatic.size(); i++) {
            QString SPIOption = Dashboard::selectedSPIOptionsStatic.at(i);
                  if (!addedSPIOptions.contains(SPIOption)) {
                      configmode->addActionToMenu("&SPI", SPIOption);
                      addedSPIOptions.insert(SPIOption);
                  }
        }

        for (int i = 0; i < Dashboard::selectedADCOptionsStatic.size(); i++) {
            QString ADCOption = Dashboard::selectedADCOptionsStatic.at(i);
            if (!addedADCOptions.contains(ADCOption)) {
               configmode->addActionToMenu("&ADC", ADCOption);
                addedADCOptions.insert(ADCOption);
            }

        }

        for (int i = 0; i < Dashboard::selectedDACOptionsStatic.size(); i++) {
            QString DACOption = Dashboard::selectedDACOptionsStatic.at(i);
            if (!addedDACOptions.contains(DACOption)) {
               configmode->addActionToMenu("&DAC", DACOption);
                addedDACOptions.insert(DACOption);
            }
        }

        for (int i = 0; i < Dashboard::selectedGPIOOptionsStatic.size(); i++) {
            QString GPIOOption = Dashboard::selectedGPIOOptionsStatic.at(i);
            if (!addedGPIOOptions.contains(GPIOOption)) {
               configmode->addActionToMenu("&GPIO", GPIOOption);
                addedGPIOOptions.insert(GPIOOption);
            }
        }

        for (int i = 0; i < Dashboard::selectedTIMEROptionsStatic.size(); i++) {
            QString TIMEROption = Dashboard::selectedTIMEROptionsStatic.at(i);
            if (!addedTIMEROptions.contains(TIMEROption)) {
              configmode->addActionToMenu("&Frequency Mesure", TIMEROption);
                addedTIMEROptions.insert(TIMEROption);
            }

        }
    configmode->show();
    this->hide();
}
void sequenceApplication::addActionToMenu(QString menuItem, QString actionName)
{
// Recherche du menu correspondant au menuItem
QList<QMenu *> menus = menuBar()->findChildren<QMenu *>();
QMenu *menu = nullptr;
for (auto m : menus) {
    if (m->title() == menuItem) {
        menu = m;
        break;
    }
}


// Création du sous-menu s'il n'existe pas
  if (menu) {

      menu->addSeparator();
  }

  // Ajout de l'action dans le sous-menu
  QAction *action = new QAction(actionName, this);
  menu->addAction(action);

  if (action->text()=="UART4"){
   QSettings settings ("configSelection.txt" , QSettings::IniFormat);
   settings.setValue("actionUART4" , action->text());
   QString ActionConfig = settings.value("actionUART4" , action->text()).toString();

   qDebug() << "actionUART4:" << ActionConfig;

//  connect (action ,&QAction::triggered , this , &Runmode::showUART4Run);
//}
//  else if(action->text()=="&UART5") {
//      connect (action ,&QAction::triggered , this , &Runmode::showUART5Run);
//  }
//  else if(action->text()=="&USART1") {
////      connect (action ,&QAction::triggered , this , &ConfigMode::showUSART1config);
//  }
//  else if(action->text()=="&USART2") {
////      connect (action ,&QAction::triggered , this , &ConfigMode::showUSART2config);
//  }
//  else if(action->text()=="SPI1") {
//      connect (action ,&QAction::triggered , this , &Runmode::showSPI1Run);
//  }
//  else if(action->text()=="&SPI2") {
//      connect (action ,&QAction::triggered , this , &Runmode::showSPI2Run);
//  }
//  else if(action->text()=="&SPI3") {
////      connect (action ,&QAction::triggered , this , &ConfigMode::showSPI3config);
//  }
//  else if(action->text()=="I2C1") {
//      connect (action ,&QAction::triggered , this , &Runmode::showI2C1Run);
//  }
//  else if(action->text()=="&I2C2") {
////      connect (action ,&QAction::triggered , this , &ConfigMode::showI2C2config);
//  }
//  else if(action->text()=="ADC1") {
//      connect (action ,&QAction::triggered , this , &Runmode::showADC1Run);
//  }
//  else if(action->text()=="&ADC3") {
////      connect (action ,&QAction::triggered , this , &ConfigMode::showADC3config);
//  }
//  else if(action->text()=="DAC_OUT1") {
//      connect (action ,&QAction::triggered , this , &Runmode::showDACOUT1Run);
//  }
//  else if(action->text()=="DAC_OUT2") {
////      connect (action ,&QAction::triggered , this , &ConfigMode::showDACOUT2config);
//  }
//  else if(action->text()=="GPIO_OUTPUT") {
//      connect (action ,&QAction::triggered , this , &Runmode::showGPIOOUTPUTRun);
//  }
//  else if(action->text()=="&GPIO_INPUT") {
////      connect (action ,&QAction::triggered , this , &ConfigMode::showGPIOINPUTconfig);
//  }
//  else if(action->text()=="Input Capture Mode") {
//      connect (action ,&QAction::triggered , this , &Runmode::showFrequencyMesureRun);
//  }



  qDebug() << "selected option:" << action->text();







}
}

void sequenceApplication::onSubMenuSelected()
{
QAction* selectedAction = qobject_cast<QAction*>(sender());
if (selectedAction)
{
QString selectedItemText = selectedAction->text();
QListWidgetItem* listItem = new QListWidgetItem(selectedItemText);
selectedItemsListWidget->addItem(listItem);
qDebug() << "selected option:" <<listItem;

}
}
sequenceApplication::~sequenceApplication()
{
    delete ui;
}
