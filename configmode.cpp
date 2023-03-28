#include "configmode.h"
#include "ui_configmode.h"
#include "dashboard.h"
#include <QIcon>
#include <QCheckBox>
#include <QWidgetAction>
#include <QToolButton>
#include"uart.h"

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
    connect(connectButton, &QToolButton::clicked, this, &ConfigMode::sendframe);

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
      else if(action->text()=="DAC_OUT1") {
          connect (action ,&QAction::triggered , this , &ConfigMode::showDACOUT1config);
      }
      else if(action->text()=="DAC_OUT2") {
          connect (action ,&QAction::triggered , this , &ConfigMode::showDACOUT2config);
      }
      else if(action->text()=="GPIO_OUTPUT") {
          connect (action ,&QAction::triggered , this , &ConfigMode::showGPIOOUTPUTconfig);
      }
      else if(action->text()=="&GPIO_INPUT") {
          connect (action ,&QAction::triggered , this , &ConfigMode::showGPIOINPUTconfig);
      }
      else if(action->text()=="Input Capture Mode") {
          connect (action ,&QAction::triggered , this , &ConfigMode::showFrequencyMesureconfig);
      }



      qDebug() << "selected option:" << action->text();







}

    void ConfigMode::sendframe()
     {



          Uart* uart = Uart::getInstance();
         QSerialPort* serialPort = uart->getSerialPort();

         QList<QMenu*> menus = menuBar()->findChildren<QMenu*>();
         QSettings settings("UARTConfig.txt", QSettings::IniFormat);
          QSettings settingsSPI("SPIConfig.txt", QSettings::IniFormat);
          char delimiter2[2] = ",";
          char delimiter1[2] = "|";

          QByteArray packet;

          QByteArray DelimPacket;



          QByteArray packet1;

          QByteArray packet2;
          QByteArray packet3;


          bool uart4Found = false;
          bool uart5Found = false;
          bool spi1Found = false;
          bool spi2Found = false;



          packet.clear();  // clear the existing packet to start fresh
          packet1.clear();  // clear the existing packet to start fresh
          packet2.clear();  // clear the existing packet to start fresh





         for (auto menu : menus) {
         // if (menu->title() == "Devices") { // Change "Devices" to the name of the menu that contains the devices
         QList<QAction*> actions = menu->actions();

         for (auto action : actions) {
         QString deviceName = action->text();


         qDebug() << " aaaa:" << deviceName;


//        packet.clear();  // clear the existing packet to start fresh


        if (deviceName.startsWith("UART4")) {

            qDebug() << " device:" << deviceName;

            uart4Found = true;



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
         settings.endGroup();
         qDebug() << " stopBits:" << stopBitsConfig;

         // Define the message ID and payload
         uint8_t messageIPID = 0x01;

         uint8_t messageBaudID = 0x02;
         uint8_t messageParityID = 0x03;
         uint8_t messageStopID = 0x04;
         uint8_t messageDataID = 0x05;
         uint8_t messageFlowID = 0x06;

         QByteArray dataBaud = BaudrateConfig.toUtf8();
         QByteArray dataparity = ParityConfig.toUtf8();
         QByteArray datastop = stopBitsConfig.toUtf8();
         QByteArray databits = DataBitsConfig.toUtf8();
         QByteArray dataflow = FlowControlConfig.toUtf8();

    //     // Create a message packet
//             packet.append(messageIPID);
//             packet.append(delimiter1);


             packet.append(messageBaudID);
             packet.append(delimiter1);

             packet.append(dataBaud);

             packet.append(delimiter1);
             packet.append(messageParityID);
             packet.append(delimiter1);

             packet.append(dataparity);

             packet.append(delimiter1);
             packet.append(messageStopID);
             packet.append(delimiter1);

             packet.append(datastop);
             packet.append(delimiter1);

             packet.append(messageDataID);
             packet.append(delimiter1);

             packet.append(databits);
             packet.append(delimiter1);

             packet.append(messageFlowID);
             packet.append(delimiter1);

             packet.append(dataflow);
             packet.append(delimiter2);


//             serialPort->write(packet);


}
//        else if ((!deviceName.startsWith("&UART")) && (!deviceName.startsWith("UART4"))) {
//            // Create a message packet containing only a comma
//            qDebug() << "cccc" << !deviceName.startsWith("UART4");
//            qDebug() << "In else block";
////            packet.clear();  // clear the existing packet to start fresh
//            if (!packet.contains(",")) {

//               packet.append(",");
//            }        }

//        packet1.clear();  // clear the existing packet to start fresh

        if (deviceName.startsWith("&UART5")) {

             qDebug() << "check" << deviceName.startsWith("&UART5");
            qDebug() << " device:" << deviceName;

            uart5Found = true;


            settings.beginGroup("UART5Configs");

            QString baudrate1;
            QString Parity1;
            QString stopBits1;
            QString DataBits1;
            QString FlowControl1;

            QString BaudrateConfig1 = settings.value("Baudrate" , baudrate1).toString();
            QString ParityConfig1 = settings.value("Parity" , Parity1).toString();
            QString stopBitsConfig1 = settings.value("stopBits" , stopBits1).toString();
            QString DataBitsConfig1 = settings.value("DataBits" , DataBits1).toString();
            QString FlowControlConfig1 = settings.value("FlowControl" , FlowControl1).toString();
            settings.endGroup();


            // Define the message ID and payload
            uint8_t messageIPID1 = 0x01;

            uint8_t messageBaudID1 = 0x1;
            uint8_t messageParityID1 = 0x03;
            uint8_t messageStopID1 = 0x04;
            uint8_t messageDataID1 = 0x05;
            uint8_t messageFlowID1 = 0x06;

            QByteArray dataBaud1 = BaudrateConfig1.toUtf8();
            QByteArray dataparity1 = ParityConfig1.toUtf8();
            QByteArray datastop1 = stopBitsConfig1.toUtf8();
            QByteArray databits1 = DataBitsConfig1.toUtf8();
            QByteArray dataflow1 = FlowControlConfig1.toUtf8();



        //    QByteArray checking = "\n";


        //    QByteArray payloadData = "This is my payload data";

            // Create a message packet
        //    packet.append(messageIPID);
        //    packet.append(delimiter);

//            packet1.append(delimiter2);

            packet1.append(messageBaudID1);
            packet1.append(delimiter1);

            packet1.append(dataBaud1);

            packet1.append(delimiter1);
            packet1.append(messageParityID1);
            packet1.append(delimiter1);

            packet1.append(dataparity1);

            packet1.append(delimiter1);
            packet1.append(messageStopID1);
            packet1.append(delimiter1);

            packet1.append(datastop1);
            packet1.append(delimiter1);

            packet1.append(messageDataID1);
            packet1.append(delimiter1);

            packet1.append(databits1);
            packet1.append(delimiter1);

            packet1.append(messageFlowID1);
            packet1.append(delimiter1);

            packet1.append(dataflow1);
            packet1.append(delimiter2);



//            serialPort->write(packet1);
        }

//        else if (deviceName.startsWith("&UART")){
//            // Create a message packet containing only a comma
//            qDebug() << "In else block";
////            packet.clear();  // clear the existing packet to start fresh
//            if (!packet1.contains(",")) {

//               packet1.append(",");
//            }
//        }

//        packet2.clear();  // clear the existing packet to start fresh

        if (deviceName.startsWith("SPI1")) {

            qDebug() << " device:" << deviceName;

            spi1Found = true;


            settingsSPI.beginGroup("SPI1Configs");

            QString Mode;
            QString NSS;
            QString DataSize;
            QString FirstBit;

            QString ModeConfig1 = settingsSPI.value("Mode" , Mode).toString();
            QString NSSConfig1 = settingsSPI.value("NSS" , NSS).toString();
            QString DataSizeConfig1 = settingsSPI.value("DataSize" , DataSize).toString();
            QString FirstBitConfig1 = settingsSPI.value("FirstBit" , FirstBit).toString();
            settingsSPI.endGroup();


            qDebug() << " Mode:" << ModeConfig1;

            // Define the message ID and payload
    //        uint8_t messageIPID1 = 0x01;
    //        char delimiter1[2] = "|";

            uint8_t messageModeID = 0x8;
            uint8_t messageNSSID = 0x03;
            uint8_t messageDataSizeID = 0x04;
            uint8_t messageFirstBitID = 0x05;

            QByteArray dataMode = ModeConfig1.toUtf8();
            QByteArray dataNSS = NSSConfig1.toUtf8();
            QByteArray dataSize = DataSizeConfig1.toUtf8();
            QByteArray dataFirstbits = FirstBitConfig1.toUtf8();



        //    QByteArray checking = "\n";


        //    QByteArray payloadData = "This is my payload data";

            // Create a message packet
        //    packet.append(messageIPID);
        //    packet.append(delimiter);
//            packet2.append(delimiter2);


            packet2.append(messageModeID);
            packet2.append(delimiter1);

            packet2.append(dataMode);

            packet2.append(delimiter1);
            packet2.append(messageNSSID);
            packet2.append(delimiter1);

            packet2.append(dataNSS);

            packet2.append(delimiter1);
            packet2.append(messageDataSizeID);
            packet2.append(delimiter1);

            packet2.append(dataSize);
            packet2.append(delimiter1);

            packet2.append(messageFirstBitID);
            packet2.append(delimiter1);

            packet2.append(dataFirstbits);
            packet2.append(delimiter2);


//            serialPort->write(packet2);

        }


        if (deviceName.startsWith("&SPI2")) {

            qDebug() << " device:" << deviceName;

            spi2Found = true;


            settingsSPI.beginGroup("SPI2Configs");

            QString Mode;
            QString NSS;
            QString DataSize;
            QString FirstBit;

            QString ModeConfig1 = settingsSPI.value("Mode" , Mode).toString();
            QString NSSConfig1 = settingsSPI.value("NSS" , NSS).toString();
            QString DataSizeConfig1 = settingsSPI.value("DataSize" , DataSize).toString();
            QString FirstBitConfig1 = settingsSPI.value("FirstBit" , FirstBit).toString();
            settingsSPI.endGroup();


            qDebug() << " Mode:" << ModeConfig1;

            // Define the message ID and payload
    //        uint8_t messageIPID1 = 0x01;
    //        char delimiter1[2] = "|";

            uint8_t messageModeID = 0x9;
            uint8_t messageNSSID = 0x03;
            uint8_t messageDataSizeID = 0x04;
            uint8_t messageFirstBitID = 0x05;

            QByteArray dataMode = ModeConfig1.toUtf8();
            QByteArray dataNSS = NSSConfig1.toUtf8();
            QByteArray dataSize = DataSizeConfig1.toUtf8();
            QByteArray dataFirstbits = FirstBitConfig1.toUtf8();



        //    QByteArray checking = "\n";


        //    QByteArray payloadData = "This is my payload data";

            // Create a message packet
        //    packet.append(messageIPID);
        //    packet.append(delimiter);
//            packet2.append(delimiter2);


            packet3.append(messageModeID);
            packet3.append(delimiter1);

            packet3.append(dataMode);

            packet3.append(delimiter1);
            packet3.append(messageNSSID);
            packet3.append(delimiter1);

            packet3.append(dataNSS);

            packet3.append(delimiter1);
            packet3.append(messageDataSizeID);
            packet3.append(delimiter1);

            packet3.append(dataSize);
            packet3.append(delimiter1);

            packet3.append(messageFirstBitID);
            packet3.append(delimiter1);

            packet3.append(dataFirstbits);
            packet3.append(delimiter2);


//            serialPort->write(packet2);

        }



//        else if (deviceName.startsWith("&SPI")){
//            if (!packet2.contains(",")) {
////                packet2.clear();  // clear the existing packet to start fresh

//                packet2.append(",");
//            }

//        }
//        qDebug() << " bbbbbbbbbbbb:" << deviceName;


//        }
//        else if (deviceName.startsWith("")) {
//            // Create a message packet containing only a comma
////          packet.clear();  // clear the existing packet to start fresh
////          packet1.clear();  // clear the existing packet to start fresh

////                packet2.clear();  // clear the existing packet to start fresh
//            if (packet.contains(",")) {

//                packet.append(",");

//            }
//            if (packet1.contains(",")) {
//                packet1.append(",");


//            }
//            if (packet2.contains(",")) {
//                packet2.append(",");


//            }


//        }


//        if (deviceName!="UART4"){

//                if (packet.contains(",")) {

//                    packet.clear();  // clear the existing packet to start fresh


//                    packet.append(",");

//                }

//        }


//        if (deviceName!="&UART5"){

//                if (packet1.contains(",")) {
//                    packet1.clear();  // clear the existing packet to start fresh

//                    packet1.append(",");

//                }

//         }

//        if (deviceName!="SPI1"){

//                if (packet2.contains(",")) {

//                    packet2.clear();  // clear the existing packet to start fresh


//                    packet2.append(",");

//                }

//         }


//        serialPort->write(packet);
//        serialPort->write(packet1);

//        serialPort->write(packet2);



        }}

         if (!uart4Found) {
         packet.append(delimiter2);
//         serialPort->write(packet);
         }

         if (!uart5Found) {
         packet1.append(delimiter2);
//         serialPort->write(packet1);
         }
         if (!spi1Found) {
         packet2.append(delimiter2);
//         serialPort->write(packet2);
         }

         if (!spi2Found) {
         packet3.append(delimiter2);
//         serialPort->write(packet2);
         }

         QByteArray concatenated = packet + packet1 + packet2 + packet3;

        concatenated.append("\n");
         qint64 bytesWritten = serialPort->write(concatenated);

         qDebug() << "concatenated" << concatenated;


         if (bytesWritten == -1) {
                 qDebug() << "Failed to write to serial port";
             } else if (bytesWritten != concatenated.size()) {
                 qDebug() << "Failed to write all bytes to serial port";
             } else {
                 qDebug() << "Data sent successfully";
             }




         qDebug() << " packet:" << packet;
         qDebug() << " packet1:" << packet1;
         qDebug() << " packet2:" << packet2;
         qDebug() << " packet3:" << packet3;

         qDebug() << " delimpacket:" << DelimPacket;





     }

ConfigMode::~ConfigMode()
{
    delete ui;
}
