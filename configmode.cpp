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

}

void ConfigMode::returnDashboard()
{
    Dashboard *dashboard = new Dashboard();
    QSettings settings("configSelection", QSettings::IniFormat);
    QAction *action = new QAction(this);

    QString actionUART4 = action->text();
    settings.setValue("actionUART4" , actionUART4);
    qDebug() << "selected uart:" << actionUART4;
//    qDebug() << "configselected:" << TimingConfig;
    dashboard->show();
    this->hide();
}


void ConfigMode::addActionToMenu(QString menuItem, QString actionName)
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

      connect (action ,&QAction::triggered , this , &ConfigMode::showUART4config);
    }
      else if(action->text()=="&UART5") {
          connect (action ,&QAction::triggered , this , &ConfigMode::showUART5config);
      }
      else if(action->text()=="&USART1") {
          connect (action ,&QAction::triggered , this , &ConfigMode::showUSART1config);
      }
      else if(action->text()=="&USART2") {
          connect (action ,&QAction::triggered , this , &ConfigMode::showUSART2config);
      }
      else if(action->text()=="SPI1") {
          connect (action ,&QAction::triggered , this , &ConfigMode::showSPI1config);
      }
      else if(action->text()=="&SPI2") {
          connect (action ,&QAction::triggered , this , &ConfigMode::showSPI2config);
      }
      else if(action->text()=="&SPI3") {
          connect (action ,&QAction::triggered , this , &ConfigMode::showSPI3config);
      }
      else if(action->text()=="I2C1") {
          connect (action ,&QAction::triggered , this , &ConfigMode::showI2C1config);
      }
      else if(action->text()=="&I2C2") {
          connect (action ,&QAction::triggered , this , &ConfigMode::showI2C2config);
      }
      else if(action->text()=="ADC1") {
          connect (action ,&QAction::triggered , this , &ConfigMode::showADC1config);
      }
      else if(action->text()=="&ADC3") {
          connect (action ,&QAction::triggered , this , &ConfigMode::showADC3config);
      }



      qDebug() << "selected option:" << action->text();







}

ConfigMode::~ConfigMode()
{
    delete ui;
}
