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
    padding: 7px; /* Espacement intérieur */\
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


  qDebug() << "selected option:" << action->text();
  QMenu* contextMenu = new QMenu(this);
  QAction* deleteAction = new QAction("Delete IP", this);
  QAction* checkOrderAction = new QAction("Order sequence", this);

  // Ajout des actions au menu contextuel
  contextMenu->addAction(deleteAction);
  contextMenu->addAction(checkOrderAction);


  connect(deleteAction, &QAction::triggered, [=]() {
  QListWidgetItem* selectedItem = ui->listWidget->currentItem();
  if (selectedItem) {
  QString itemText = selectedItem->text();
  delete selectedItem;

  // Masquer le widget associé en fonction de l'élément supprimé
  if (itemText == "ADC1") {
  ui->ADCwidget->hide();
  } else if (itemText == "DAC_OUT1") {
  ui->DACwidget->hide();
  } else if (itemText == "Input Capture Mode") {
  ui->TIMERwidget->hide();
  } else if (itemText == "I2C1") {
  ui->I2Cwidget->hide();
  } else if (itemText == "GPIO_OUTPUT") {
  ui->GPIOwidget->hide();
  }
  }
  });
  // Configuration du menu contextuel pour la liste widget
  ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
//  connect(ui->listWidget, &QListWidget::customContextMenuRequested, [contextMenu](const QPoint& pos) {
//  contextMenu->exec(pos);
//  });


  // Connexion du signal du menu contextuel
  connect(ui->listWidget, &QListWidget::customContextMenuRequested, [=](const QPoint& pos) {
  QListWidgetItem* selectedItem = ui->listWidget->itemAt(pos);
  if (selectedItem) {
  QPoint globalPos = ui->listWidget->mapToGlobal(pos);
  contextMenu->exec(globalPos);
  contextMenu->hide();
  }
  });
  if (action->text()=="UART4"){
   QSettings settings ("configSelection.txt" , QSettings::IniFormat);
   settings.setValue("actionUART4" , action->text());
   QString ActionConfig = settings.value("actionUART4" , action->text()).toString();

   qDebug() << "actionUART4:" << ActionConfig;
   connect(action, &QAction::triggered, [=]() {

       ui->listWidget->addItem(action->text());



   });

}
  else if(action->text()=="&UART5") {
      connect(action, &QAction::triggered, [=]() {

          ui->listWidget->addItem(action->text());

      });
  }
  else if(action->text()=="&USART1") {
      connect(action, &QAction::triggered, [=]() {

          ui->listWidget->addItem(action->text());

      });
  }
  else if(action->text()=="&USART2") {
      connect(action, &QAction::triggered, [=]() {

          ui->listWidget->addItem(action->text());

      });
  }
  else if(action->text()=="SPI1") {
      connect(action, &QAction::triggered, [=]() {

          ui->listWidget->addItem(action->text());

      });
  }
  else if(action->text()=="&SPI2") {
      connect(action, &QAction::triggered, [=]() {

          ui->listWidget->addItem(action->text());

      });

  }
  else if(action->text()=="&SPI3") {
      connect(action, &QAction::triggered, [=]() {

          ui->listWidget->addItem(action->text());

      });
  }
  else if(action->text()=="I2C1") {
      connect(action, &QAction::triggered, [=]() {

          ui->listWidget->addItem(action->text());

          showI2Cexec();

          QFont font("Segoe UI", 10); // Police Arial avec une taille de 12 points


//          ui->listWidget->currentItem()->setFont(font);
//          ui->I2Cwidget->show(); // Afficher le widget correspondant
//          ui->I2Cwidget->raise(); // Amener le widget à l'avant-plan



      });
  }
  else if(action->text()=="&I2C2") {
      connect(action, &QAction::triggered, [=]() {

          ui->listWidget->addItem(action->text());

      });

  }
  else if(action->text()=="ADC1") {
      connect(action, &QAction::triggered, [=]() {

          ui->listWidget->addItem(action->text());

          showADCexec();



//          ui->ADCwidget->show(); // Afficher le widget correspondant
//          ui->ADCwidget->raise(); // Amener le widget à l'avant-plan


      });

  }
  else if(action->text()=="&ADC3") {
      connect(action, &QAction::triggered, [=]() {

          ui->listWidget->addItem(action->text());

      });

  }
  else if(action->text()=="DAC_OUT1") {
      connect(action, &QAction::triggered, [=]() {

          ui->listWidget->addItem(action->text());
          showDACexec();
//          ui->DACwidget->show(); // Afficher le widget correspondant
//          ui->DACwidget->raise(); // Amener le widget à l'avant-plan


      });

  }
  else if(action->text()=="DAC_OUT2") {
      connect(action, &QAction::triggered, [=]() {

          ui->listWidget->addItem(action->text());

      });

  }
  else if(action->text()=="GPIO_OUTPUT") {
      connect(action, &QAction::triggered, [=]() {

          ui->listWidget->addItem(action->text());

          showGPIOexec();

//          ui->GPIOwidget->show(); // Afficher le widget correspondant
//          ui->GPIOwidget->raise(); // Amener le widget à l'avant-plan


      });

  }
  else if(action->text()=="&GPIO_INPUT") {
      connect(action, &QAction::triggered, [=]() {

          ui->listWidget->addItem(action->text());

      });

  }
  else if(action->text()=="Input Capture Mode") {
      connect(action, &QAction::triggered, [=]() {

          ui->listWidget->addItem(action->text());

          showTIMERexec();

//          ui->TIMERwidget->show(); // Afficher le widget correspondant
//          ui->TIMERwidget->raise(); // Amener le widget à l'avant-plan


      });
  }





  if (action->text() == "ADC1") {
  ui->ADCwidget->show(); // Afficher le widget correspondant
  ui->ADCwidget->raise(); // Amener le widget à l'avant-plan
  } else if (action->text() == "DAC_OUT1") {
  ui->DACwidget->show();
  ui->DACwidget->raise();
  } else if (action->text() == "Input Capture Mode") {
  ui->TIMERwidget->show();
  ui->TIMERwidget->raise();
  } else if (action->text() == "I2C1") {
  ui->I2Cwidget->show();
  ui->I2Cwidget->raise();
  } else if (action->text() == "GPIO_OUTPUT") {
  ui->GPIOwidget->show();
  ui->GPIOwidget->raise();
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



void sequenceApplication::showADCexec(){

    Uart* uart = Uart::getInstance();
    QSerialPort* serialPort = uart->getSerialPort();

//    setCentralWidget(ui->ADCwidget);

    QVBoxLayout* adcLayout = new QVBoxLayout(ui->ADCwidget);

    // Create a QLabel to display the ADC device address
    QLabel* deviceAddressLabel = new QLabel("ADC Device Address:", ui->ADCwidget);
    QLabel* Adcvalue = new QLabel("Get value:", ui->ADCwidget);

    QLineEdit* deviceAddressLineEdit = new QLineEdit(ui->ADCwidget);
    QLineEdit* AdcvalueLineEdit = new QLineEdit(ui->ADCwidget);

    deviceAddressLineEdit->setPlaceholderText("Enter the device address");
    AdcvalueLineEdit->setPlaceholderText("Digital value");


    QString styleSheet2 =
        "QPushButton {"
        "    background-color: gray;"
        "    border: none;"
        "    color: white;"
        "    padding: 3px 3px;"
        "    text-align: center;"
        "    text-decoration: none;"
        "    font-size: 14px;"
        "    margin: 4px 2px;"
        "    border-radius: 10px;"
        "}"
        ""
        "QPushButton:hover {"
        "    background-color: #3e8e41;"
        "}";
    QFont font("Segoe UI", 10); // Police Arial avec une taille de 12 points
    deviceAddressLabel->setFont(font);
    deviceAddressLabel->setFont(font);


    deviceAddressLabel->setStyleSheet("font: bold 13px; color: #328930;");
    Adcvalue->setStyleSheet("font: bold 13px; color: #328930;");
    // Create a label widget and set its font to Noto Sans
//        QFont font("Noto Sans");

    deviceAddressLineEdit->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
    AdcvalueLineEdit->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


    // Create a QComboBox to select the ADC channel

    // Create a QPushButton to initiate the ADC read operation
//    QPushButton* readButton = new QPushButton("Read", ui->ADCwidget);
//    QPushButton* writeButton = new QPushButton("Write", ui->ADCwidget);

    // Create a QTextBrowser to display the ADC read data

    // Add the components to the layout
    adcLayout->addWidget(deviceAddressLabel);
    adcLayout->addWidget(deviceAddressLineEdit);
    adcLayout->addWidget(Adcvalue);
    adcLayout->addWidget(AdcvalueLineEdit);



//    adcLayout->addWidget(channelLabel);
//    adcLayout->addWidget(channelComboBox);
//    adcLayout->addWidget(dataTextBrowser);
//    auto buttonLayout = new QHBoxLayout();
//    buttonLayout->addWidget(writeButton);
//    buttonLayout->addWidget(readButton);
//    adcLayout->addLayout(buttonLayout);





                  }


void sequenceApplication::showGPIOexec(){

    Uart* uart = Uart::getInstance();
    QSerialPort* serialPort = uart->getSerialPort();


    QVBoxLayout* gpioOutputLayout = new QVBoxLayout(ui->GPIOwidget);

    // Create a QLabel to display the status of the LED
    QLabel* ledStatusLabel = new QLabel("LED Status: OFF/ON", ui->GPIOwidget);
    QString styleSheet2 =
              "QPushButton {"
              "    background-color: gray;"
              "    border: none;"
              "    color: white;"
              "    padding: 3px 3px;"
              "    text-align: center;"
              "    text-decoration: none;"
              "    font-size: 14px;"
              "    margin: 4px 2px;"
              "    border-radius: 10px;"
              "}"
              ""
              "QPushButton:hover {"
              "    background-color: #3e8e41;"
              "}";
             QFont font("Segoe UI", 10); // Police Arial avec une taille de 12 points
            ledStatusLabel->setFont(font);


            ledStatusLabel->setStyleSheet("font: bold 13px; color: #328930;");
            gpioOutputLayout->addWidget(ledStatusLabel);


                  }

void sequenceApplication::showI2Cexec(){

    Uart* uart = Uart::getInstance();
    QSerialPort* serialPort = uart->getSerialPort();


    QVBoxLayout* I2CLayout = new QVBoxLayout(ui->I2Cwidget);

    // Create a QLabel to display the status of the LED
    QLabel* ledStatusLabel = new QLabel("Temperature and Humidity values", ui->I2Cwidget);
    QTextBrowser* dataTextBrowser = new QTextBrowser(ui->I2Cwidget);


    QString styleSheet2 =
              "QPushButton {"
              "    background-color: gray;"
              "    border: none;"
              "    color: white;"
              "    padding: 3px 3px;"
              "    text-align: center;"
              "    text-decoration: none;"
              "    font-size: 14px;"
              "    margin: 4px 2px;"
              "    border-radius: 10px;"
              "}"
              ""
              "QPushButton:hover {"
              "    background-color: #3e8e41;"
              "}";
          QFont font("Segoe UI", 10); // Police Arial avec une taille de 12 points
          ledStatusLabel->setFont(font);


          ledStatusLabel->setStyleSheet("font: bold 13px; color: #328930;");

          dataTextBrowser->setStyleSheet("QTextBrowser { background-color: #E3E0DF; }");
          font.setBold(true);
          dataTextBrowser->setFont(font);

    // Add the components to the layout
    I2CLayout->addWidget(ledStatusLabel);
    I2CLayout->addWidget(dataTextBrowser);

}


void sequenceApplication::showDACexec(){

    Uart* uart = Uart::getInstance();
    QSerialPort* serialPort = uart->getSerialPort();


    QVBoxLayout* DAClayout = new QVBoxLayout(ui->DACwidget);

    QLabel* deviceAddressLabel = new QLabel("Digital value:", ui->DACwidget);
    QLabel* Adcvalue = new QLabel("Get value:", ui->DACwidget);

    QLineEdit* deviceAddressLineEdit = new QLineEdit(ui->DACwidget);
    QLineEdit* AdcvalueLineEdit = new QLineEdit(ui->DACwidget);

    deviceAddressLineEdit->setPlaceholderText("Enter the device address");
    AdcvalueLineEdit->setPlaceholderText("Digital value");


    QString styleSheet2 =
              "QPushButton {"
              "    background-color: gray;"
              "    border: none;"
              "    color: white;"
              "    padding: 3px 3px;"
              "    text-align: center;"
              "    text-decoration: none;"
              "    font-size: 14px;"
              "    margin: 4px 2px;"
              "    border-radius: 10px;"
              "}"
              ""
              "QPushButton:hover {"
              "    background-color: #3e8e41;"
              "}";
          QFont font("Segoe UI", 10); // Police Arial avec une taille de 12 points
          Adcvalue->setFont(font);
          deviceAddressLabel->setFont(font);


          deviceAddressLabel->setStyleSheet("font: bold 13px; color: #328930;");
          Adcvalue->setStyleSheet("font: bold 13px; color: #328930;");
          // Create a label widget and set its font to Noto Sans
  //        QFont font("Noto Sans");

          AdcvalueLineEdit->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
          deviceAddressLineEdit->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


    // Add the components to the layout
    DAClayout->addWidget(deviceAddressLabel);
    DAClayout->addWidget(deviceAddressLineEdit);
    DAClayout->addWidget(Adcvalue);
    DAClayout->addWidget(AdcvalueLineEdit);




                  }

void sequenceApplication::showTIMERexec(){

    Uart* uart = Uart::getInstance();
    QSerialPort* serialPort = uart->getSerialPort();


    QVBoxLayout* TIMERlayout = new QVBoxLayout(ui->TIMERwidget);

    QLabel* deviceAddressLabel = new QLabel("Timer clock:", ui->TIMERwidget);
    QLabel* Adcvalue = new QLabel("Get Frequency:", ui->TIMERwidget);

    QLineEdit* deviceAddressLineEdit = new QLineEdit(ui->TIMERwidget);
    QLineEdit* AdcvalueLineEdit = new QLineEdit(ui->TIMERwidget);

    deviceAddressLineEdit->setPlaceholderText("Enter the device address");
    AdcvalueLineEdit->setPlaceholderText("Digital value");


    QString styleSheet2 =
              "QPushButton {"
              "    background-color: gray;"
              "    border: none;"
              "    color: white;"
              "    padding: 3px 3px;"
              "    text-align: center;"
              "    text-decoration: none;"
              "    font-size: 14px;"
              "    margin: 4px 2px;"
              "    border-radius: 10px;"
              "}"
              ""
              "QPushButton:hover {"
              "    background-color: #3e8e41;"
              "}";
          QFont font("Segoe UI", 10); // Police Arial avec une taille de 12 points
          Adcvalue->setFont(font);
          deviceAddressLabel->setFont(font);


          deviceAddressLabel->setStyleSheet("font: bold 13px; color: #328930;");
          Adcvalue->setStyleSheet("font: bold 13px; color: #328930;");
          // Create a label widget and set its font to Noto Sans
  //        QFont font("Noto Sans");
          AdcvalueLineEdit->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
          deviceAddressLineEdit->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


    // Add the components to the layout
    TIMERlayout->addWidget(deviceAddressLabel);
    TIMERlayout->addWidget(deviceAddressLineEdit);
    TIMERlayout->addWidget(Adcvalue);
    TIMERlayout->addWidget(AdcvalueLineEdit);




                  }
sequenceApplication::~sequenceApplication()
{
    delete ui;
}
