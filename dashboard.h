#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include<QFormLayout>
#include<QtSerialPort/QSerialPortInfo>
#include <QSpinBox>
#include <QLineEdit>
#include <QSpacerItem>
#include <QSettings>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileInfo>
#include <QFontDatabase>
#include "configmode.h"




namespace Ui {
class Dashboard;
}

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    QSettings settings  ;

    ~Dashboard();
private slots :



    void UARTConfig()
    {
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);


                // Create Layout form
                QFormLayout* layout = new QFormLayout(this);

                // Create a QLabel for "DAC configurations" and center it horizontally
                QLabel* titleLabel = new QLabel("UART configurations", this);

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
               QComboBox* baudRateComboBox = new QComboBox(this);
//               baudRateComboBox->setStyleSheet("QComboBox {"
//                                       "background-color: white;"
//                                       "border: 1px solid gray;"
//                                       "border-radius: 3px;"
//                                       "padding: 1px 18px 1px 3px;"
//                                       "min-width: 6em;"
//                                       "}"
//                                       "QComboBox::drop-down {"
//                                       "subcontrol-origin: padding;"
//                                       "subcontrol-position: top right;"
//                                       "width: 15px;"
//                                       "border-left-width: 1px;"
//                                       "border-left-color: gray;"
//                                       "border-left-style: solid;"
//                                       "border-top-right-radius: 3px;"
//                                       "border-bottom-right-radius: 3px;"
//                                       "}"
//                                       "QComboBox::down-arrow {"
//                                       "image: url(:/images/down_arrow.png);"
//                                       "}"
//                                       "QComboBox QAbstractItemView {"
//                                       "background-color: white;"
//                                       "border: 1px solid gray;"
//                                       "selection-background-color: lightgray;"
//                                       "}"
//                                       );

               QList<qint32> baudRates = info.standardBaudRates(); // What baudrates does my computer support ?
               QList<QString> stringBaudRates;
                for(int i = 0 ; i < baudRates.size() ; i++){
                    stringBaudRates.append(QString::number(baudRates.at(i)));
                }
               baudRateComboBox->addItems(stringBaudRates);

               baudRateComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
               // Set the minimum width to 100 pixels
               baudRateComboBox->setMinimumWidth(10);
               baudRateLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               baudRateComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(baudRateLabel, baudRateComboBox);



               // ----------------------- Save Baudrate configs into a file.txt-----------------------------------//


               QString BaudrateConfig = settings.value("Baudrate", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexBaudrate = baudRateComboBox->findText(BaudrateConfig);
               if (indexBaudrate != -1)
                   baudRateComboBox->setCurrentIndex(indexBaudrate);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Baudrate; // declare stopBits outside of the lambda

               connect(baudRateComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Baudrate](int indexBaudrate){
                   // Retrieve the selected option
                   QSettings settings("file.txt", QSettings::IniFormat);

                   QString Baudrate = baudRateComboBox->itemText(indexBaudrate);
                   settings.beginGroup("UARTConfigs");


                   // Store the selected option in the settings file
                   settings.setValue("Baudrate", Baudrate);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString BaudrateConfig = settings.value("Baudrate" , Baudrate).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Baudrate;
                   qDebug() << "Baudrate:" << BaudrateConfig;
               });


               // Create the parity label and combo box

               QLabel* parityLabel = new QLabel(tr("Parity"), this);
               QComboBox* parityComboBox = new QComboBox(this);
               parityComboBox->addItems(QStringList() << "None" << "Odd" << "Even");
               parityLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               parityComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(parityLabel, parityComboBox);


               // ----------------------- Save Pqrity configs into a file.txt-----------------------------------//


               QString ParityConfig = settings.value("Parity", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexParity = parityComboBox->findText(ParityConfig);
               if (indexParity != -1)
                   parityComboBox->setCurrentIndex(indexParity);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Parity; // declare stopBits outside of the lambda

               connect(parityComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Parity](int indexParity){
                   // Retrieve the selected option
                   QSettings settings("file.txt", QSettings::IniFormat);

                   QString Parity = parityComboBox->itemText(indexParity);
                   settings.beginGroup("UARTConfigs");


                   // Store the selected option in the settings file
                   settings.setValue("Parity", Parity);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ParityConfig = settings.value("Parity" , Parity).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Parity;
                   qDebug() << "Parity:" << ParityConfig;
               });





               // Create the stop bits label and combo box

               QLabel* stopBitsLabel = new QLabel(tr("Stop Bits"), this);
               QComboBox* stopBitsComboBox = new QComboBox(this);
               stopBitsComboBox->addItem("1 Bits");
               stopBitsComboBox->addItem("1,5 Bits");
               stopBitsComboBox->addItem("2 Bits");

               stopBitsLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               stopBitsComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(stopBitsLabel, stopBitsComboBox);


               // Connect the combo box to the slot

             //--------------------------- Save Stop Bits Configs into a file.txt -------------------------//

               QString stopBitsConfig = settings.value("stopBits", "").toString();
               // Set the selected option in the combo box

               int index = stopBitsComboBox->findText(stopBitsConfig);
               if (index != -1)
                   stopBitsComboBox->setCurrentIndex(index);

               QString stopBits; // declare stopBits outside of the lambda

               // Connect the combo box to the slot

               connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&stopBits](int index){
                   // Retrieve the selected option
                   QSettings settings("file.txt", QSettings::IniFormat);

                   QString stopBits = stopBitsComboBox->itemText(index);
                   settings.beginGroup("UARTConfigs");


                   // Store the selected option in the settings file
                   settings.setValue("stopBits", stopBits);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString stopBitsConfig = settings.value("stopBits" , stopBits).toString();

                   qDebug() << "selected option:" << stopBits;
                   qDebug() << "stopBits:" << stopBitsConfig;
               });












               // Create the data bits label and combo box

               QLabel* DataBitsLabel = new QLabel(tr("Data Bits"), this);
               QComboBox* DataBitsComboBox = new QComboBox(this);
               DataBitsComboBox->addItems(QStringList() << "5" << "6" << "7" << "8");
               DataBitsLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               DataBitsComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               // ----------------------- Save DataBits configs into a file.txt-----------------------------------//


               QString DataBitsConfig = settings.value("DataBits", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexDataBits = DataBitsComboBox->findText(DataBitsConfig);
               if (indexDataBits != -1)
                   DataBitsComboBox->setCurrentIndex(indexDataBits);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString DataBits; // declare stopBits outside of the lambda

               connect(DataBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&DataBits](int indexDataBits){
                   // Retrieve the selected option
                   QSettings settings("file.txt", QSettings::IniFormat);

                   QString DataBits = DataBitsComboBox->itemText(indexDataBits);
                   settings.beginGroup("UARTConfigs");


                   // Store the selected option in the settings file
                   settings.setValue("DataBits", DataBits);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString DataBitsConfig = settings.value("DataBits" , DataBits).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << DataBits;
                   qDebug() << "DataBits:" << DataBitsConfig;
               });

               // Create the flow control label and combo box

               layout->addRow(DataBitsLabel, DataBitsComboBox);
               QLabel* FlowControlLabel = new QLabel(tr("Flow Control"), this);
               QComboBox* FlowControlComboBox = new QComboBox(this);
               FlowControlComboBox->addItems(QStringList() << "No Flow Control" << "Hardware Flow Control" << "Software Flow Control " );
               FlowControlLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FlowControlComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");




               layout->addRow(FlowControlLabel, FlowControlComboBox);
               layout->setContentsMargins(0, 0, 0, 0);
               layout->setSpacing(30);


               //--------------------------- Save Stop Bits Configs into a file.txt -------------------------//

                 QString FlowControlConfig = settings.value("FlowControl", "").toString();
                 // Set the selected option in the combo box

                 int indexFlowControl = FlowControlComboBox->findText(FlowControlConfig);
                 if (indexFlowControl != -1)
                     FlowControlComboBox->setCurrentIndex(indexFlowControl);

                 QString FlowControl; // declare FlowControl outside of the lambda

                 // Connect the combo box to the slot

                 connect(FlowControlComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&FlowControl](int indexFlowControl){
                     // Retrieve the selected option
                     QSettings settings("file.txt", QSettings::IniFormat);

                     QString FlowControl = FlowControlComboBox->itemText(indexFlowControl);
                     settings.beginGroup("UARTConfigs");


                     // Store the selected option in the settings file
                     settings.setValue("FlowControl", FlowControl);
                     settings.endGroup();

                     // Retrieve the stored value and print to the console
                     QString FlowControlConfig = settings.value("FlowControl" , FlowControl).toString();

                     qDebug() << "selected option:" << FlowControl;
                     qDebug() << "FlowControl:" << FlowControlConfig;
                 });

               // Create the vertical layout and add the form layout to it
               QVBoxLayout* verticalLayout = new QVBoxLayout(this);
               verticalLayout->addStretch();
               verticalLayout->addLayout(layout);
               verticalLayout->addStretch();

               // Create the horizontal layout and add the vertical layout to it
               QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
               horizontalLayout->addStretch();
               horizontalLayout->addLayout(verticalLayout);
               horizontalLayout->addStretch();

               // Set the widget layout to the horizontal layout

               widget->setLayout(horizontalLayout);
               widget->setGeometry(500, 500, 600, 500);
               widget->setStyleSheet("QFormLayout {"
                                         "  background-color: gray;"
                                         "  border: 2px solid black;"
                                         "  padding: 10px;"
                                         "}"
                                         "QLineEdit {"
                                         "  background-color: white;"
                                         "  border: 1px solid black;"
                                         "  padding: 5px;"
                                         "}");

               QSettings settings("file.txt", QSettings::IniFormat);

               qDebug() << "Settings file path: " << settings.fileName();



               settings.beginGroup("UARTConfigs");

               settings.setValue("Baudrate",  Baudrate);
               settings.setValue("stopBits",  stopBits);
               settings.setValue("DataBits",  DataBits);
               settings.setValue("FlowControl",  FlowControl);
               settings.setValue("Parity",  Parity);

               settings.endGroup();













               // Create the QLabel and set its text and minimum height
               QLabel* footerLabel = new QLabel();
               footerLabel->setText("Footer Text");
               footerLabel->setMinimumHeight(40);



               // Add the QLabel to the QHBoxLayout and center it
               //layout->addWidget(footerLabel, 0, Qt::AlignHCenter);

               // Set the size of the QWidget
               widget->setGeometry(100, 100, 400, 300);









    }
    void UART4Config()
    {
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);


                // Create Layout form
                QFormLayout* layout = new QFormLayout(this);

                QLabel* titleLabel = new QLabel("UART4 configurations", this);

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
               QComboBox* baudRateComboBox = new QComboBox(this);
               QList<qint32> baudRates = info.standardBaudRates(); // What baudrates does my computer support ?
               QList<QString> stringBaudRates;
                for(int i = 0 ; i < baudRates.size() ; i++){
                    stringBaudRates.append(QString::number(baudRates.at(i)));
                }
               baudRateComboBox->addItems(stringBaudRates);

               baudRateComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
               // Set the minimum width to 100 pixels
               baudRateComboBox->setMinimumWidth(10);
               baudRateLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               baudRateComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(baudRateLabel, baudRateComboBox);



               // ----------------------- Save Baudrate configs into a file.txt-----------------------------------//


               QString BaudrateConfig = settings.value("Baudrate", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexBaudrate = baudRateComboBox->findText(BaudrateConfig);
               if (indexBaudrate != -1)
                   baudRateComboBox->setCurrentIndex(indexBaudrate);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Baudrate; // declare stopBits outside of the lambda

               connect(baudRateComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Baudrate](int indexBaudrate){
                   // Retrieve the selected option
                   QSettings settings("UARTConfig.txt", QSettings::IniFormat);

                   QString Baudrate = baudRateComboBox->itemText(indexBaudrate);
                   settings.beginGroup("UART4Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Baudrate", Baudrate);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString BaudrateConfig = settings.value("Baudrate" , Baudrate).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Baudrate;
                   qDebug() << "Baudrate:" << BaudrateConfig;
               });


               // Create the parity label and combo box

               QLabel* parityLabel = new QLabel(tr("Parity"), this);
               QComboBox* parityComboBox = new QComboBox(this);
               parityComboBox->addItems(QStringList() << "None" << "Odd" << "Even");
               parityLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               parityComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(parityLabel, parityComboBox);


               // ----------------------- Save Pqrity configs into a UARTConfig.txt-----------------------------------//


               QString ParityConfig = settings.value("Parity", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexParity = parityComboBox->findText(ParityConfig);
               if (indexParity != -1)
                   parityComboBox->setCurrentIndex(indexParity);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Parity; // declare stopBits outside of the lambda

               connect(parityComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Parity](int indexParity){
                   // Retrieve the selected option
                   QSettings settings("UARTConfig.txt", QSettings::IniFormat);

                   QString Parity = parityComboBox->itemText(indexParity);
                   settings.beginGroup("UART4Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Parity", Parity);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ParityConfig = settings.value("Parity" , Parity).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Parity;
                   qDebug() << "Parity:" << ParityConfig;
               });





               // Create the stop bits label and combo box

               QLabel* stopBitsLabel = new QLabel(tr("Stop Bits"), this);
               QComboBox* stopBitsComboBox = new QComboBox(this);
               stopBitsComboBox->addItem("1 Bits");
               stopBitsComboBox->addItem("1,5 Bits");
               stopBitsComboBox->addItem("2 Bits");

               stopBitsLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               stopBitsComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(stopBitsLabel, stopBitsComboBox);


               // Connect the combo box to the slot

             //--------------------------- Save Stop Bits Configs into a UARTConfig.txt -------------------------//

               QString stopBitsConfig = settings.value("stopBits", "").toString();
               // Set the selected option in the combo box

               int index = stopBitsComboBox->findText(stopBitsConfig);
               if (index != -1)
                   stopBitsComboBox->setCurrentIndex(index);

               QString stopBits; // declare stopBits outside of the lambda

               // Connect the combo box to the slot

               connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&stopBits](int index){
                   // Retrieve the selected option
                   QSettings settings("UARTConfig.txt", QSettings::IniFormat);

                   QString stopBits = stopBitsComboBox->itemText(index);
                   settings.beginGroup("UART4Configs");


                   // Store the selected option in the settings file
                   settings.setValue("stopBits", stopBits);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString stopBitsConfig = settings.value("stopBits" , stopBits).toString();

                   qDebug() << "selected option:" << stopBits;
                   qDebug() << "stopBits:" << stopBitsConfig;
               });












               // Create the data bits label and combo box

               QLabel* DataBitsLabel = new QLabel(tr("Data Bits"), this);
               QComboBox* DataBitsComboBox = new QComboBox(this);
               DataBitsComboBox->addItems(QStringList() << "5" << "6" << "7" << "8");
               DataBitsLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               DataBitsComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               // ----------------------- Save DataBits configs into a UARTConfig.txt-----------------------------------//


               QString DataBitsConfig = settings.value("DataBits", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexDataBits = DataBitsComboBox->findText(DataBitsConfig);
               if (indexDataBits != -1)
                   DataBitsComboBox->setCurrentIndex(indexDataBits);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString DataBits; // declare stopBits outside of the lambda

               connect(DataBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&DataBits](int indexDataBits){
                   // Retrieve the selected option
                   QSettings settings("UARTConfig.txt", QSettings::IniFormat);

                   QString DataBits = DataBitsComboBox->itemText(indexDataBits);
                   settings.beginGroup("UART4Configs");


                   // Store the selected option in the settings file
                   settings.setValue("DataBits", DataBits);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString DataBitsConfig = settings.value("DataBits" , DataBits).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << DataBits;
                   qDebug() << "DataBits:" << DataBitsConfig;
               });

               // Create the flow control label and combo box

               layout->addRow(DataBitsLabel, DataBitsComboBox);
               QLabel* FlowControlLabel = new QLabel(tr("Flow Control"), this);
               QComboBox* FlowControlComboBox = new QComboBox(this);
               FlowControlComboBox->addItems(QStringList() << "No Flow Control" << "Hardware Flow Control" << "Software Flow Control " );
               FlowControlLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FlowControlComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");




               layout->addRow(FlowControlLabel, FlowControlComboBox);
               layout->setContentsMargins(0, 0, 0, 0);
               layout->setSpacing(30);


               //--------------------------- Save Stop Bits Configs into a UARTConfig.txt -------------------------//

                 QString FlowControlConfig = settings.value("FlowControl", "").toString();
                 // Set the selected option in the combo box

                 int indexFlowControl = FlowControlComboBox->findText(FlowControlConfig);
                 if (indexFlowControl != -1)
                     FlowControlComboBox->setCurrentIndex(indexFlowControl);

                 QString FlowControl; // declare FlowControl outside of the lambda

                 // Connect the combo box to the slot

                 connect(FlowControlComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&FlowControl](int indexFlowControl){
                     // Retrieve the selected option
                     QSettings settings("UARTConfig.txt", QSettings::IniFormat);

                     QString FlowControl = FlowControlComboBox->itemText(indexFlowControl);
                     settings.beginGroup("UART4Configs");


                     // Store the selected option in the settings file
                     settings.setValue("FlowControl", FlowControl);
                     settings.endGroup();

                     // Retrieve the stored value and print to the console
                     QString FlowControlConfig = settings.value("FlowControl" , FlowControl).toString();

                     qDebug() << "selected option:" << FlowControl;
                     qDebug() << "FlowControl:" << FlowControlConfig;
                 });

               // Create the vertical layout and add the form layout to it
               QVBoxLayout* verticalLayout = new QVBoxLayout(this);
               verticalLayout->addStretch();
               verticalLayout->addLayout(layout);
               verticalLayout->addStretch();

               // Create the horizontal layout and add the vertical layout to it
               QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
               horizontalLayout->addStretch();
               horizontalLayout->addLayout(verticalLayout);
               horizontalLayout->addStretch();

               // Set the widget layout to the horizontal layout

               widget->setLayout(horizontalLayout);
               widget->setGeometry(500, 500, 600, 500);
               widget->setStyleSheet("QFormLayout {"
                                         "  background-color: gray;"
                                         "  border: 2px solid black;"
                                         "  padding: 10px;"
                                         "}"
                                         "QLineEdit {"
                                         "  background-color: white;"
                                         "  border: 1px solid black;"
                                         "  padding: 5px;"
                                         "}");

               QSettings settings("UARTConfig.txt", QSettings::IniFormat);

               qDebug() << "Settings file path: " << settings.fileName();



               settings.beginGroup("UART4Configs");

               settings.setValue("Baudrate",  Baudrate);
               settings.setValue("stopBits",  stopBits);
               settings.setValue("DataBits",  DataBits);
               settings.setValue("FlowControl",  FlowControl);
               settings.setValue("Parity",  Parity);

               settings.endGroup();













               // Create the QLabel and set its text and minimum height
               QLabel* footerLabel = new QLabel();
               footerLabel->setText("Footer Text");
               footerLabel->setMinimumHeight(40);



               // Add the QLabel to the QHBoxLayout and center it
               //layout->addWidget(footerLabel, 0, Qt::AlignHCenter);

               // Set the size of the QWidget
               widget->setGeometry(100, 100, 400, 300);









    }
    void UART5Config()
    {
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);


                // Create Layout form
                QFormLayout* layout = new QFormLayout(this);

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
               QComboBox* baudRateComboBox = new QComboBox(this);
               QList<qint32> baudRates = info.standardBaudRates(); // What baudrates does my computer support ?
               QList<QString> stringBaudRates;
                for(int i = 0 ; i < baudRates.size() ; i++){
                    stringBaudRates.append(QString::number(baudRates.at(i)));
                }
               baudRateComboBox->addItems(stringBaudRates);

               baudRateComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
               // Set the minimum width to 100 pixels
               baudRateComboBox->setMinimumWidth(10);
               baudRateLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               baudRateComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(baudRateLabel, baudRateComboBox);



               // ----------------------- Save Baudrate configs into a file.txt-----------------------------------//


               QString BaudrateConfig = settings.value("Baudrate", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexBaudrate = baudRateComboBox->findText(BaudrateConfig);
               if (indexBaudrate != -1)
                   baudRateComboBox->setCurrentIndex(indexBaudrate);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Baudrate; // declare stopBits outside of the lambda

               connect(baudRateComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Baudrate](int indexBaudrate){
                   // Retrieve the selected option
                   QSettings settings("UARTConfig.txt", QSettings::IniFormat);

                   QString Baudrate = baudRateComboBox->itemText(indexBaudrate);
                   settings.beginGroup("UART5Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Baudrate", Baudrate);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString BaudrateConfig = settings.value("Baudrate" , Baudrate).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Baudrate;
                   qDebug() << "Baudrate:" << BaudrateConfig;
               });


               // Create the parity label and combo box

               QLabel* parityLabel = new QLabel(tr("Parity"), this);
               QComboBox* parityComboBox = new QComboBox(this);
               parityComboBox->addItems(QStringList() << "None" << "Odd" << "Even");
               parityLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               parityComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(parityLabel, parityComboBox);


               // ----------------------- Save Pqrity configs into a UARTConfig.txt-----------------------------------//


               QString ParityConfig = settings.value("Parity", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexParity = parityComboBox->findText(ParityConfig);
               if (indexParity != -1)
                   parityComboBox->setCurrentIndex(indexParity);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Parity; // declare stopBits outside of the lambda

               connect(parityComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Parity](int indexParity){
                   // Retrieve the selected option
                   QSettings settings("UARTConfig.txt", QSettings::IniFormat);

                   QString Parity = parityComboBox->itemText(indexParity);
                   settings.beginGroup("UART5Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Parity", Parity);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ParityConfig = settings.value("Parity" , Parity).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Parity;
                   qDebug() << "Parity:" << ParityConfig;
               });





               // Create the stop bits label and combo box

               QLabel* stopBitsLabel = new QLabel(tr("Stop Bits"), this);
               QComboBox* stopBitsComboBox = new QComboBox(this);
               stopBitsComboBox->addItem("1 Bits");
               stopBitsComboBox->addItem("1,5 Bits");
               stopBitsComboBox->addItem("2 Bits");

               stopBitsLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               stopBitsComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(stopBitsLabel, stopBitsComboBox);


               // Connect the combo box to the slot

             //--------------------------- Save Stop Bits Configs into a UARTConfig.txt -------------------------//

               QString stopBitsConfig = settings.value("stopBits", "").toString();
               // Set the selected option in the combo box

               int index = stopBitsComboBox->findText(stopBitsConfig);
               if (index != -1)
                   stopBitsComboBox->setCurrentIndex(index);

               QString stopBits; // declare stopBits outside of the lambda

               // Connect the combo box to the slot

               connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&stopBits](int index){
                   // Retrieve the selected option
                   QSettings settings("UARTConfig.txt", QSettings::IniFormat);

                   QString stopBits = stopBitsComboBox->itemText(index);
                   settings.beginGroup("UART5Configs");


                   // Store the selected option in the settings file
                   settings.setValue("stopBits", stopBits);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString stopBitsConfig = settings.value("stopBits" , stopBits).toString();

                   qDebug() << "selected option:" << stopBits;
                   qDebug() << "stopBits:" << stopBitsConfig;
               });












               // Create the data bits label and combo box

               QLabel* DataBitsLabel = new QLabel(tr("Data Bits"), this);
               QComboBox* DataBitsComboBox = new QComboBox(this);
               DataBitsComboBox->addItems(QStringList() << "5" << "6" << "7" << "8");
               DataBitsLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               DataBitsComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               // ----------------------- Save DataBits configs into a UARTConfig.txt-----------------------------------//


               QString DataBitsConfig = settings.value("DataBits", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexDataBits = DataBitsComboBox->findText(DataBitsConfig);
               if (indexDataBits != -1)
                   DataBitsComboBox->setCurrentIndex(indexDataBits);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString DataBits; // declare stopBits outside of the lambda

               connect(DataBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&DataBits](int indexDataBits){
                   // Retrieve the selected option
                   QSettings settings("UARTConfig.txt", QSettings::IniFormat);

                   QString DataBits = DataBitsComboBox->itemText(indexDataBits);
                   settings.beginGroup("UART5Configs");


                   // Store the selected option in the settings file
                   settings.setValue("DataBits", DataBits);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString DataBitsConfig = settings.value("DataBits" , DataBits).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << DataBits;
                   qDebug() << "DataBits:" << DataBitsConfig;
               });

               // Create the flow control label and combo box

               layout->addRow(DataBitsLabel, DataBitsComboBox);
               QLabel* FlowControlLabel = new QLabel(tr("Flow Control"), this);
               QComboBox* FlowControlComboBox = new QComboBox(this);
               FlowControlComboBox->addItems(QStringList() << "No Flow Control" << "Hardware Flow Control" << "Software Flow Control " );
               FlowControlLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FlowControlComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");




               layout->addRow(FlowControlLabel, FlowControlComboBox);
               layout->setContentsMargins(0, 0, 0, 0);
               layout->setSpacing(30);


               //--------------------------- Save Stop Bits Configs into a UARTConfig.txt -------------------------//

                 QString FlowControlConfig = settings.value("FlowControl", "").toString();
                 // Set the selected option in the combo box

                 int indexFlowControl = FlowControlComboBox->findText(FlowControlConfig);
                 if (indexFlowControl != -1)
                     FlowControlComboBox->setCurrentIndex(indexFlowControl);

                 QString FlowControl; // declare FlowControl outside of the lambda

                 // Connect the combo box to the slot

                 connect(FlowControlComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&FlowControl](int indexFlowControl){
                     // Retrieve the selected option
                     QSettings settings("UARTConfig.txt", QSettings::IniFormat);

                     QString FlowControl = FlowControlComboBox->itemText(indexFlowControl);
                     settings.beginGroup("UART5Configs");


                     // Store the selected option in the settings file
                     settings.setValue("FlowControl", FlowControl);
                     settings.endGroup();

                     // Retrieve the stored value and print to the console
                     QString FlowControlConfig = settings.value("FlowControl" , FlowControl).toString();

                     qDebug() << "selected option:" << FlowControl;
                     qDebug() << "FlowControl:" << FlowControlConfig;
                 });

               // Create the vertical layout and add the form layout to it
               QVBoxLayout* verticalLayout = new QVBoxLayout(this);
               verticalLayout->addStretch();
               verticalLayout->addLayout(layout);
               verticalLayout->addStretch();

               // Create the horizontal layout and add the vertical layout to it
               QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
               horizontalLayout->addStretch();
               horizontalLayout->addLayout(verticalLayout);
               horizontalLayout->addStretch();

               // Set the widget layout to the horizontal layout

               widget->setLayout(horizontalLayout);
               widget->setGeometry(500, 500, 600, 500);
               widget->setStyleSheet("QFormLayout {"
                                         "  background-color: gray;"
                                         "  border: 2px solid black;"
                                         "  padding: 10px;"
                                         "}"
                                         "QLineEdit {"
                                         "  background-color: white;"
                                         "  border: 1px solid black;"
                                         "  padding: 5px;"
                                         "}");

               QSettings settings("UARTConfig.txt", QSettings::IniFormat);

               qDebug() << "Settings file path: " << settings.fileName();



               settings.beginGroup("UART5Configs");

               settings.setValue("Baudrate",  Baudrate);
               settings.setValue("stopBits",  stopBits);
               settings.setValue("DataBits",  DataBits);
               settings.setValue("FlowControl",  FlowControl);
               settings.setValue("Parity",  Parity);

               settings.endGroup();













               // Create the QLabel and set its text and minimum height
               QLabel* footerLabel = new QLabel();
               footerLabel->setText("Footer Text");
               footerLabel->setMinimumHeight(40);



               // Add the QLabel to the QHBoxLayout and center it
               //layout->addWidget(footerLabel, 0, Qt::AlignHCenter);

               // Set the size of the QWidget
               widget->setGeometry(100, 100, 400, 300);









    }
    void USART1Config()
    {
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);


                // Create Layout form
                QFormLayout* layout = new QFormLayout(this);

                QLabel* titleLabel = new QLabel("USART1 configurations", this);

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
               QComboBox* baudRateComboBox = new QComboBox(this);
               QList<qint32> baudRates = info.standardBaudRates(); // What baudrates does my computer support ?
               QList<QString> stringBaudRates;
                for(int i = 0 ; i < baudRates.size() ; i++){
                    stringBaudRates.append(QString::number(baudRates.at(i)));
                }
               baudRateComboBox->addItems(stringBaudRates);

               baudRateComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
               // Set the minimum width to 100 pixels
               baudRateComboBox->setMinimumWidth(10);
               baudRateLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               baudRateComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(baudRateLabel, baudRateComboBox);



               // ----------------------- Save Baudrate configs into a file.txt-----------------------------------//


               QString BaudrateConfig = settings.value("Baudrate", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexBaudrate = baudRateComboBox->findText(BaudrateConfig);
               if (indexBaudrate != -1)
                   baudRateComboBox->setCurrentIndex(indexBaudrate);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Baudrate; // declare stopBits outside of the lambda

               connect(baudRateComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Baudrate](int indexBaudrate){
                   // Retrieve the selected option
                   QSettings settings("UARTConfig.txt", QSettings::IniFormat);

                   QString Baudrate = baudRateComboBox->itemText(indexBaudrate);
                   settings.beginGroup("USART1Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Baudrate", Baudrate);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString BaudrateConfig = settings.value("Baudrate" , Baudrate).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Baudrate;
                   qDebug() << "Baudrate:" << BaudrateConfig;
               });


               // Create the parity label and combo box

               QLabel* parityLabel = new QLabel(tr("Parity"), this);
               QComboBox* parityComboBox = new QComboBox(this);
               parityComboBox->addItems(QStringList() << "None" << "Odd" << "Even");
               parityLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               parityComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(parityLabel, parityComboBox);


               // ----------------------- Save Pqrity configs into a UARTConfig.txt-----------------------------------//


               QString ParityConfig = settings.value("Parity", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexParity = parityComboBox->findText(ParityConfig);
               if (indexParity != -1)
                   parityComboBox->setCurrentIndex(indexParity);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Parity; // declare stopBits outside of the lambda

               connect(parityComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Parity](int indexParity){
                   // Retrieve the selected option
                   QSettings settings("UARTConfig.txt", QSettings::IniFormat);

                   QString Parity = parityComboBox->itemText(indexParity);
                   settings.beginGroup("USART1Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Parity", Parity);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ParityConfig = settings.value("Parity" , Parity).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Parity;
                   qDebug() << "Parity:" << ParityConfig;
               });





               // Create the stop bits label and combo box

               QLabel* stopBitsLabel = new QLabel(tr("Stop Bits"), this);
               QComboBox* stopBitsComboBox = new QComboBox(this);
               stopBitsComboBox->addItem("1 Bits");
               stopBitsComboBox->addItem("1,5 Bits");
               stopBitsComboBox->addItem("2 Bits");

               stopBitsLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               stopBitsComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(stopBitsLabel, stopBitsComboBox);


               // Connect the combo box to the slot

             //--------------------------- Save Stop Bits Configs into a UARTConfig.txt -------------------------//

               QString stopBitsConfig = settings.value("stopBits", "").toString();
               // Set the selected option in the combo box

               int index = stopBitsComboBox->findText(stopBitsConfig);
               if (index != -1)
                   stopBitsComboBox->setCurrentIndex(index);

               QString stopBits; // declare stopBits outside of the lambda

               // Connect the combo box to the slot

               connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&stopBits](int index){
                   // Retrieve the selected option
                   QSettings settings("UARTConfig.txt", QSettings::IniFormat);

                   QString stopBits = stopBitsComboBox->itemText(index);
                   settings.beginGroup("USART1Configs");


                   // Store the selected option in the settings file
                   settings.setValue("stopBits", stopBits);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString stopBitsConfig = settings.value("stopBits" , stopBits).toString();

                   qDebug() << "selected option:" << stopBits;
                   qDebug() << "stopBits:" << stopBitsConfig;
               });












               // Create the data bits label and combo box

               QLabel* DataBitsLabel = new QLabel(tr("Data Bits"), this);
               QComboBox* DataBitsComboBox = new QComboBox(this);
               DataBitsComboBox->addItems(QStringList() << "5" << "6" << "7" << "8");
               DataBitsLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               DataBitsComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               // ----------------------- Save DataBits configs into a UARTConfig.txt-----------------------------------//


               QString DataBitsConfig = settings.value("DataBits", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexDataBits = DataBitsComboBox->findText(DataBitsConfig);
               if (indexDataBits != -1)
                   DataBitsComboBox->setCurrentIndex(indexDataBits);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString DataBits; // declare stopBits outside of the lambda

               connect(DataBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&DataBits](int indexDataBits){
                   // Retrieve the selected option
                   QSettings settings("UARTConfig.txt", QSettings::IniFormat);

                   QString DataBits = DataBitsComboBox->itemText(indexDataBits);
                   settings.beginGroup("USART1Configs");


                   // Store the selected option in the settings file
                   settings.setValue("DataBits", DataBits);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString DataBitsConfig = settings.value("DataBits" , DataBits).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << DataBits;
                   qDebug() << "DataBits:" << DataBitsConfig;
               });

               // Create the flow control label and combo box

               layout->addRow(DataBitsLabel, DataBitsComboBox);
               QLabel* FlowControlLabel = new QLabel(tr("Flow Control"), this);
               QComboBox* FlowControlComboBox = new QComboBox(this);
               FlowControlComboBox->addItems(QStringList() << "No Flow Control" << "Hardware Flow Control" << "Software Flow Control " );
               FlowControlLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FlowControlComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");




               layout->addRow(FlowControlLabel, FlowControlComboBox);
               layout->setContentsMargins(0, 0, 0, 0);
               layout->setSpacing(30);


               //--------------------------- Save Stop Bits Configs into a UARTConfig.txt -------------------------//

                 QString FlowControlConfig = settings.value("FlowControl", "").toString();
                 // Set the selected option in the combo box

                 int indexFlowControl = FlowControlComboBox->findText(FlowControlConfig);
                 if (indexFlowControl != -1)
                     FlowControlComboBox->setCurrentIndex(indexFlowControl);

                 QString FlowControl; // declare FlowControl outside of the lambda

                 // Connect the combo box to the slot

                 connect(FlowControlComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&FlowControl](int indexFlowControl){
                     // Retrieve the selected option
                     QSettings settings("UARTConfig.txt", QSettings::IniFormat);

                     QString FlowControl = FlowControlComboBox->itemText(indexFlowControl);
                     settings.beginGroup("USART1Configs");


                     // Store the selected option in the settings file
                     settings.setValue("FlowControl", FlowControl);
                     settings.endGroup();

                     // Retrieve the stored value and print to the console
                     QString FlowControlConfig = settings.value("FlowControl" , FlowControl).toString();

                     qDebug() << "selected option:" << FlowControl;
                     qDebug() << "FlowControl:" << FlowControlConfig;
                 });

               // Create the vertical layout and add the form layout to it
               QVBoxLayout* verticalLayout = new QVBoxLayout(this);
               verticalLayout->addStretch();
               verticalLayout->addLayout(layout);
               verticalLayout->addStretch();

               // Create the horizontal layout and add the vertical layout to it
               QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
               horizontalLayout->addStretch();
               horizontalLayout->addLayout(verticalLayout);
               horizontalLayout->addStretch();

               // Set the widget layout to the horizontal layout

               widget->setLayout(horizontalLayout);
               widget->setGeometry(500, 500, 600, 500);
               widget->setStyleSheet("QFormLayout {"
                                         "  background-color: gray;"
                                         "  border: 2px solid black;"
                                         "  padding: 10px;"
                                         "}"
                                         "QLineEdit {"
                                         "  background-color: white;"
                                         "  border: 1px solid black;"
                                         "  padding: 5px;"
                                         "}");

               QSettings settings("UARTConfig.txt", QSettings::IniFormat);

               qDebug() << "Settings file path: " << settings.fileName();



               settings.beginGroup("USART1Configs");

               settings.setValue("Baudrate",  Baudrate);
               settings.setValue("stopBits",  stopBits);
               settings.setValue("DataBits",  DataBits);
               settings.setValue("FlowControl",  FlowControl);
               settings.setValue("Parity",  Parity);

               settings.endGroup();













               // Create the QLabel and set its text and minimum height
               QLabel* footerLabel = new QLabel();
               footerLabel->setText("Footer Text");
               footerLabel->setMinimumHeight(40);



               // Add the QLabel to the QHBoxLayout and center it
               //layout->addWidget(footerLabel, 0, Qt::AlignHCenter);

               // Set the size of the QWidget
               widget->setGeometry(100, 100, 400, 300);









    }
    void USART2Config()
    {
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);


                // Create Layout form
                QFormLayout* layout = new QFormLayout(this);

                QLabel* titleLabel = new QLabel("USART2 configurations", this);

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
               QComboBox* baudRateComboBox = new QComboBox(this);
               QList<qint32> baudRates = info.standardBaudRates(); // What baudrates does my computer support ?
               QList<QString> stringBaudRates;
                for(int i = 0 ; i < baudRates.size() ; i++){
                    stringBaudRates.append(QString::number(baudRates.at(i)));
                }
               baudRateComboBox->addItems(stringBaudRates);

               baudRateComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
               // Set the minimum width to 100 pixels
               baudRateComboBox->setMinimumWidth(10);
               baudRateLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               baudRateComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(baudRateLabel, baudRateComboBox);



               // ----------------------- Save Baudrate configs into a UARTConfig.txt-----------------------------------//


               QString BaudrateConfig = settings.value("Baudrate", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexBaudrate = baudRateComboBox->findText(BaudrateConfig);
               if (indexBaudrate != -1)
                   baudRateComboBox->setCurrentIndex(indexBaudrate);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Baudrate; // declare stopBits outside of the lambda

               connect(baudRateComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Baudrate](int indexBaudrate){
                   // Retrieve the selected option
                   QSettings settings("UARTConfig.txt", QSettings::IniFormat);

                   QString Baudrate = baudRateComboBox->itemText(indexBaudrate);
                   settings.beginGroup("USART2Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Baudrate", Baudrate);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString BaudrateConfig = settings.value("Baudrate" , Baudrate).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Baudrate;
                   qDebug() << "Baudrate:" << BaudrateConfig;
               });


               // Create the parity label and combo box

               QLabel* parityLabel = new QLabel(tr("Parity"), this);
               QComboBox* parityComboBox = new QComboBox(this);
               parityComboBox->addItems(QStringList() << "None" << "Odd" << "Even");
               parityLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               parityComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(parityLabel, parityComboBox);


               // ----------------------- Save Pqrity configs into a UARTConfig.txt-----------------------------------//


               QString ParityConfig = settings.value("Parity", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexParity = parityComboBox->findText(ParityConfig);
               if (indexParity != -1)
                   parityComboBox->setCurrentIndex(indexParity);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Parity; // declare stopBits outside of the lambda

               connect(parityComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Parity](int indexParity){
                   // Retrieve the selected option
                   QSettings settings("UARTConfig.txt", QSettings::IniFormat);

                   QString Parity = parityComboBox->itemText(indexParity);
                   settings.beginGroup("USART2Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Parity", Parity);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ParityConfig = settings.value("Parity" , Parity).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Parity;
                   qDebug() << "Parity:" << ParityConfig;
               });





               // Create the stop bits label and combo box

               QLabel* stopBitsLabel = new QLabel(tr("Stop Bits"), this);
               QComboBox* stopBitsComboBox = new QComboBox(this);
               stopBitsComboBox->addItem("1 Bits");
               stopBitsComboBox->addItem("1,5 Bits");
               stopBitsComboBox->addItem("2 Bits");

               stopBitsLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               stopBitsComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(stopBitsLabel, stopBitsComboBox);


               // Connect the combo box to the slot

             //--------------------------- Save Stop Bits Configs into a file.txt -------------------------//

               QString stopBitsConfig = settings.value("stopBits", "").toString();
               // Set the selected option in the combo box

               int index = stopBitsComboBox->findText(stopBitsConfig);
               if (index != -1)
                   stopBitsComboBox->setCurrentIndex(index);

               QString stopBits; // declare stopBits outside of the lambda

               // Connect the combo box to the slot

               connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&stopBits](int index){
                   // Retrieve the selected option
                   QSettings settings("UARTConfig.txt", QSettings::IniFormat);

                   QString stopBits = stopBitsComboBox->itemText(index);
                   settings.beginGroup("USART2Configs");


                   // Store the selected option in the settings file
                   settings.setValue("stopBits", stopBits);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString stopBitsConfig = settings.value("stopBits" , stopBits).toString();

                   qDebug() << "selected option:" << stopBits;
                   qDebug() << "stopBits:" << stopBitsConfig;
               });












               // Create the data bits label and combo box

               QLabel* DataBitsLabel = new QLabel(tr("Data Bits"), this);
               QComboBox* DataBitsComboBox = new QComboBox(this);
               DataBitsComboBox->addItems(QStringList() << "5" << "6" << "7" << "8");
               DataBitsLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               DataBitsComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               // ----------------------- Save DataBits configs into a file.txt-----------------------------------//


               QString DataBitsConfig = settings.value("DataBits", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexDataBits = DataBitsComboBox->findText(DataBitsConfig);
               if (indexDataBits != -1)
                   DataBitsComboBox->setCurrentIndex(indexDataBits);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString DataBits; // declare stopBits outside of the lambda

               connect(DataBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&DataBits](int indexDataBits){
                   // Retrieve the selected option
                   QSettings settings("UARTConfig.txt", QSettings::IniFormat);

                   QString DataBits = DataBitsComboBox->itemText(indexDataBits);
                   settings.beginGroup("USART2Configs");


                   // Store the selected option in the settings file
                   settings.setValue("DataBits", DataBits);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString DataBitsConfig = settings.value("DataBits" , DataBits).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << DataBits;
                   qDebug() << "DataBits:" << DataBitsConfig;
               });

               // Create the flow control label and combo box

               layout->addRow(DataBitsLabel, DataBitsComboBox);
               QLabel* FlowControlLabel = new QLabel(tr("Flow Control"), this);
               QComboBox* FlowControlComboBox = new QComboBox(this);
               FlowControlComboBox->addItems(QStringList() << "No Flow Control" << "Hardware Flow Control" << "Software Flow Control " );
               FlowControlLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FlowControlComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");




               layout->addRow(FlowControlLabel, FlowControlComboBox);
               layout->setContentsMargins(0, 0, 0, 0);
               layout->setSpacing(30);


               //--------------------------- Save Stop Bits Configs into a file.txt -------------------------//

                 QString FlowControlConfig = settings.value("FlowControl", "").toString();
                 // Set the selected option in the combo box

                 int indexFlowControl = FlowControlComboBox->findText(FlowControlConfig);
                 if (indexFlowControl != -1)
                     FlowControlComboBox->setCurrentIndex(indexFlowControl);

                 QString FlowControl; // declare FlowControl outside of the lambda

                 // Connect the combo box to the slot

                 connect(FlowControlComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&FlowControl](int indexFlowControl){
                     // Retrieve the selected option
                     QSettings settings("UARTConfig.txt", QSettings::IniFormat);

                     QString FlowControl = FlowControlComboBox->itemText(indexFlowControl);
                     settings.beginGroup("USART2Configs");


                     // Store the selected option in the settings file
                     settings.setValue("FlowControl", FlowControl);
                     settings.endGroup();

                     // Retrieve the stored value and print to the console
                     QString FlowControlConfig = settings.value("FlowControl" , FlowControl).toString();

                     qDebug() << "selected option:" << FlowControl;
                     qDebug() << "FlowControl:" << FlowControlConfig;
                 });

               // Create the vertical layout and add the form layout to it
               QVBoxLayout* verticalLayout = new QVBoxLayout(this);
               verticalLayout->addStretch();
               verticalLayout->addLayout(layout);
               verticalLayout->addStretch();

               // Create the horizontal layout and add the vertical layout to it
               QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
               horizontalLayout->addStretch();
               horizontalLayout->addLayout(verticalLayout);
               horizontalLayout->addStretch();

               // Set the widget layout to the horizontal layout

               widget->setLayout(horizontalLayout);
               widget->setGeometry(500, 500, 600, 500);
               widget->setStyleSheet("QFormLayout {"
                                         "  background-color: gray;"
                                         "  border: 2px solid black;"
                                         "  padding: 10px;"
                                         "}"
                                         "QLineEdit {"
                                         "  background-color: white;"
                                         "  border: 1px solid black;"
                                         "  padding: 5px;"
                                         "}");

               QSettings settings("UARTConfig.txt", QSettings::IniFormat);

               qDebug() << "Settings file path: " << settings.fileName();



               settings.beginGroup("USART2Configs");

               settings.setValue("Baudrate",  Baudrate);
               settings.setValue("stopBits",  stopBits);
               settings.setValue("DataBits",  DataBits);
               settings.setValue("FlowControl",  FlowControl);
               settings.setValue("Parity",  Parity);

               settings.endGroup();













               // Create the QLabel and set its text and minimum height
               QLabel* footerLabel = new QLabel();
               footerLabel->setText("Footer Text");
               footerLabel->setMinimumHeight(40);



               // Add the QLabel to the QHBoxLayout and center it
               //layout->addWidget(footerLabel, 0, Qt::AlignHCenter);

               // Set the size of the QWidget
               widget->setGeometry(100, 100, 400, 300);









    }


    void SPIConfig (){
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

                // Create Layout form for SPI
                QFormLayout* layout = new QFormLayout(this);



                // Create a QLabel for "SPI configurations" and center it horizontally
                QLabel* titleLabel = new QLabel("SPI configurations", this);

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




                // ----------------------Create Mode----------------------//

               QLabel* ModeLabel = new QLabel(tr("Mode"), this);
               QComboBox* ModeComboBox = new QComboBox(this);

               ModeComboBox->addItems(QStringList() << "Full-Duplex Master" << "Full-Duplex Slave" << "Half-Duplex Master " << "Half-Duplex Slave" );
               ModeComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
               // Set the minimum width to 100 pixels
               ModeComboBox->setMinimumWidth(10);
               ModeLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ModeComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


               layout->addRow(ModeLabel, ModeComboBox);


               //---------------------Save configuration into SPIConfig.txt---------------------------//

               QString ModeConfig = settings.value("Mode", "").toString();
               // Set the selected option in the combo box

               int indexMode = ModeComboBox->findText(ModeConfig);
               if (indexMode != -1)
                   ModeComboBox->setCurrentIndex(indexMode);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Mode; // declare stopBits outside of the lambda

               connect(ModeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Mode](int indexMode){
                   // Retrieve the selected option
                   QSettings settings("SPIConfig.txt", QSettings::IniFormat);

                   QString Mode = ModeComboBox->itemText(indexMode);
                   settings.beginGroup("SPIConfigs");


                   // Store the selected option in the settings file
                   settings.setValue("Mode", Mode);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ModeConfig = settings.value("Mode" , Mode).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Mode;
                   qDebug() << "Mode:" << ModeConfig;
               });

               // ----------------------Create NSS----------------------//

               QLabel* NSSLabel = new QLabel(tr("Hardware NSS Signal"), this);
               QComboBox* NSSComboBox = new QComboBox(this);
               NSSComboBox->addItems(QStringList() << "Disable" << "Hardware NSS Input Signal" << "Hardware NSS Output Signal");
               NSSLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               NSSComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(NSSLabel, NSSComboBox);

               //---------------------Save configuration into SPIConfig.txt---------------------------//

               QString NSSConfig = settings.value("NSS", "").toString();
               // Set the selected option in the combo box

               int indexNSS = NSSComboBox->findText(NSSConfig);
               if (indexNSS != -1)
                   NSSComboBox->setCurrentIndex(indexNSS);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString NSS; // declare stopBits outside of the lambda

               connect(NSSComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&NSS](int indexNSS){
                   // Retrieve the selected option
                   QSettings settings("SPIConfig.txt", QSettings::IniFormat);

                   QString NSS = NSSComboBox->itemText(indexNSS);
                   settings.beginGroup("SPIConfigs");


                   // Store the selected option in the settings file
                   settings.setValue("NSS", NSS);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString NSSConfig = settings.value("NSS" , NSS).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << NSS;
                   qDebug() << "NSS:" << NSSConfig;
               });




               // ----------------------Create Frame Format----------------------//

               QLabel* FrameFormatLabel = new QLabel(tr("Frame Format"), this);
               QComboBox* FrameFormatComboBox = new QComboBox(this);
               FrameFormatComboBox->addItems(QStringList() << "Motorola" << "Texas Instruments");
               FrameFormatLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FrameFormatComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(FrameFormatLabel, FrameFormatComboBox);

               //---------------------Save configuration into SPIConfig.txt---------------------------//

               QString FrameformatConfig = settings.value("Frameformat", "").toString();
               // Set the selected option in the combo box

               int indexFrameformat = FrameFormatComboBox->findText(FrameformatConfig);
               if (indexFrameformat != -1)
                   FrameFormatComboBox->setCurrentIndex(indexFrameformat);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Frameformat; // declare stopBits outside of the lambda

               connect(FrameFormatComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Frameformat](int indexFrameformat){
                   // Retrieve the selected option
                   QSettings settings("SPIConfig.txt", QSettings::IniFormat);

                   QString Frameformat = FrameFormatComboBox->itemText(indexFrameformat);
                   settings.beginGroup("SPIConfigs");


                   // Store the selected option in the settings file
                   settings.setValue("Frameformat", Frameformat);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString FrameformatConfig = settings.value("Frameformat" , Frameformat).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Frameformat;
                   qDebug() << "Frameformat:" << FrameformatConfig;
               });




               // ----------------------Create Data size----------------------//

               QLabel* DataSizeLabel = new QLabel(tr("Data Size"), this);
               QSpinBox* DataSizeSpinBox = new QSpinBox(this);
               DataSizeSpinBox->setMinimum(4);
               DataSizeSpinBox->setMaximum(32);

               DataSizeLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               DataSizeSpinBox->setStyleSheet("font:Arial 15px; color: gray; background-color: white;");
               layout->addRow(DataSizeLabel, DataSizeSpinBox);

               QString DataSizeConfig = settings.value("DataSize", "").toString();
               // Set the selected value in the spin box
               DataSizeSpinBox->setValue(DataSizeConfig.toInt());

               // Connect the spin box to the slot
               QString DataSize; // declare DataSize outside of the lambda
               connect(DataSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=,&DataSize](int value){
                   // Retrieve the selected value
                   QSettings settings("SPIConfig.txt", QSettings::IniFormat);

                   QString DataSize = QString::number(value);
                   settings.beginGroup("SPIConfigs");

                   // Store the selected value in the settings file
                   settings.setValue("DataSize", DataSize);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString DataSizeConfig = settings.value("DataSize" , DataSize).toString();
                   qDebug() << "selected value:" << DataSize;
                   qDebug() << "DataSize:" << DataSizeConfig;
               });







               // ----------------------Create First Bit----------------------//

               QLabel* FirstBitLabel = new QLabel(tr("First Bit"), this);
               QComboBox* FirstBitComboBox = new QComboBox(this);
               FirstBitComboBox->addItems(QStringList() << "LSB" << "MSB"  );
               FirstBitLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FirstBitComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(FirstBitLabel, FirstBitComboBox);
               layout->setContentsMargins(0, 0, 0, 0);
               layout->setSpacing(30);

               //---------------------Save configuration into SPIConfig.txt---------------------------//

               QString FirstbitConfig = settings.value("Firstbit", "").toString();
               // Set the selected option in the combo box

               int indexFirstbit = FirstBitComboBox->findText(FirstbitConfig);
               if (indexFirstbit != -1)
                   FirstBitComboBox->setCurrentIndex(indexFirstbit);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Firstbit; // declare stopBits outside of the lambda

               connect(FirstBitComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Firstbit](int indexFirstbit){
                   // Retrieve the selected option
                   QSettings settings("SPIConfig.txt", QSettings::IniFormat);

                   QString Firstbit = FirstBitComboBox->itemText(indexFirstbit);
                   settings.beginGroup("SPIConfigs");


                   // Store the selected option in the settings file
                   settings.setValue("Firstbit", Firstbit);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString FirstbitConfig = settings.value("Firstbit" , Firstbit).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Firstbit;
                   qDebug() << "Firstbit:" << FirstbitConfig;
               });


               // Create the vertical layout and add the form layout to it
               QVBoxLayout* verticalLayout = new QVBoxLayout(this);
               verticalLayout->addStretch();
               verticalLayout->addLayout(layout);
               verticalLayout->addStretch();

               // Create the horizontal layout and add the vertical layout to it
               QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
               horizontalLayout->addStretch();
               horizontalLayout->addLayout(verticalLayout);
               horizontalLayout->addStretch();

               // Set the widget layout to the horizontal layout

               widget->setLayout(horizontalLayout);
               widget->setGeometry(500, 500, 600, 500);

               QSettings settings("SPIConfig.txt", QSettings::IniFormat);

               qDebug() << "Settings file path: " << settings.fileName();



               settings.beginGroup("SPIConfigs");

               settings.setValue("Mode",  Mode);
               settings.setValue("NSS",  NSS);
               settings.setValue("Frameformat",  Frameformat);
               settings.setValue("Datasize",  DataSize);
               settings.setValue("Firstbit",  Firstbit);

               settings.endGroup();





    }
    void SPI1Config (){
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

                // Create Layout form for SPI
                QFormLayout* layout = new QFormLayout(this);


                QLabel* titleLabel = new QLabel("SPI1 configurations", this);

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


                // ----------------------Create Mode----------------------//

               QLabel* ModeLabel = new QLabel(tr("Mode"), this);
               QComboBox* ModeComboBox = new QComboBox(this);

               ModeComboBox->addItems(QStringList() << "Full-Duplex Master" << "Full-Duplex Slave" << "Half-Duplex Master " << "Half-Duplex Slave" );
               ModeComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
               // Set the minimum width to 100 pixels
               ModeComboBox->setMinimumWidth(10);
               ModeLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ModeComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


               layout->addRow(ModeLabel, ModeComboBox);

               //---------------------Save configuration into SPIConfig.txt---------------------------//

               QString ModeConfig = settings.value("Mode", "").toString();
               // Set the selected option in the combo box

               int indexMode = ModeComboBox->findText(ModeConfig);
               if (indexMode != -1)
                   ModeComboBox->setCurrentIndex(indexMode);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Mode; // declare stopBits outside of the lambda

               connect(ModeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Mode](int indexMode){
                   // Retrieve the selected option
                   QSettings settings("SPIConfig.txt", QSettings::IniFormat);

                   QString Mode = ModeComboBox->itemText(indexMode);
                   settings.beginGroup("SPI1Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Mode", Mode);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ModeConfig = settings.value("Mode" , Mode).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Mode;
                   qDebug() << "Mode:" << ModeConfig;
               });

               // ----------------------Create NSS----------------------//

               QLabel* NSSLabel = new QLabel(tr("Hardware NSS Signal"), this);
               QComboBox* NSSComboBox = new QComboBox(this);
               NSSComboBox->addItems(QStringList() << "Disable" << "Hardware NSS Input Signal" << "Hardware NSS Output Signal");
               NSSLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               NSSComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(NSSLabel, NSSComboBox);


               //---------------------Save configuration into SPIConfig.txt---------------------------//

               QString NSSConfig = settings.value("NSS", "").toString();
               // Set the selected option in the combo box

               int indexNSS = NSSComboBox->findText(NSSConfig);
               if (indexNSS != -1)
                   NSSComboBox->setCurrentIndex(indexNSS);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString NSS; // declare stopBits outside of the lambda

               connect(NSSComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&NSS](int indexNSS){
                   // Retrieve the selected option
                   QSettings settings("SPIConfig.txt", QSettings::IniFormat);

                   QString NSS = NSSComboBox->itemText(indexNSS);
                   settings.beginGroup("SPI1Configs");


                   // Store the selected option in the settings file
                   settings.setValue("NSS", NSS);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString NSSConfig = settings.value("NSS" , NSS).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << NSS;
                   qDebug() << "NSS:" << NSSConfig;
               });




               // ----------------------Create Frame Format----------------------//

               QLabel* FrameFormatLabel = new QLabel(tr("Frame Format"), this);
               QComboBox* FrameFormatComboBox = new QComboBox(this);
               FrameFormatComboBox->addItems(QStringList() << "Motorola" << "Texas Instruments");
               FrameFormatLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FrameFormatComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(FrameFormatLabel, FrameFormatComboBox);


               //---------------------Save configuration into SPIConfig.txt---------------------------//

               QString FrameformatConfig = settings.value("Frameformat", "").toString();
               // Set the selected option in the combo box

               int indexFrameformat = FrameFormatComboBox->findText(FrameformatConfig);
               if (indexFrameformat != -1)
                   FrameFormatComboBox->setCurrentIndex(indexFrameformat);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Frameformat; // declare stopBits outside of the lambda

               connect(FrameFormatComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Frameformat](int indexFrameformat){
                   // Retrieve the selected option
                   QSettings settings("SPIConfig.txt", QSettings::IniFormat);

                   QString Frameformat = FrameFormatComboBox->itemText(indexFrameformat);
                   settings.beginGroup("SPI1Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Frameformat", Frameformat);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString FrameformatConfig = settings.value("Frameformat" , Frameformat).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Frameformat;
                   qDebug() << "Frameformat:" << FrameformatConfig;
               });




               // ----------------------Create Data size----------------------//

               QLabel* DataSizeLabel = new QLabel(tr("Data Size"), this);
               QSpinBox* DataSizeSpinBox = new QSpinBox(this);
               DataSizeSpinBox->setMinimum(4);
               DataSizeSpinBox->setMaximum(32);

               DataSizeLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               DataSizeSpinBox->setStyleSheet("font:Arial 15px; color: gray; background-color: white;");
               layout->addRow(DataSizeLabel, DataSizeSpinBox);


               //---------------------Save configuration into SPIConfig.txt---------------------------//


               QString DataSizeConfig = settings.value("DataSize", "").toString();
               // Set the selected value in the spin box
               DataSizeSpinBox->setValue(DataSizeConfig.toInt());

               // Connect the spin box to the slot
               QString DataSize; // declare DataSize outside of the lambda
               connect(DataSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=,&DataSize](int value){
                   // Retrieve the selected value
                   QSettings settings("SPIConfig.txt", QSettings::IniFormat);

                   QString DataSize = QString::number(value);
                   settings.beginGroup("SPI1Configs");

                   // Store the selected value in the settings file
                   settings.setValue("DataSize", DataSize);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString DataSizeConfig = settings.value("DataSize" , DataSize).toString();
                   qDebug() << "selected value:" << DataSize;
                   qDebug() << "DataSize:" << DataSizeConfig;
               });


               // ----------------------Create First Bit----------------------//

               QLabel* FirstBitLabel = new QLabel(tr("First Bit"), this);
               QComboBox* FirstBitComboBox = new QComboBox(this);
               FirstBitComboBox->addItems(QStringList() << "LSB" << "MSB"  );
               FirstBitLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FirstBitComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(FirstBitLabel, FirstBitComboBox);
               layout->setContentsMargins(0, 0, 0, 0);
               layout->setSpacing(30);

               //---------------------Save configuration into SPIConfig.txt---------------------------//

               QString FirstbitConfig = settings.value("Firstbit", "").toString();
               // Set the selected option in the combo box

               int indexFirstbit = FirstBitComboBox->findText(FirstbitConfig);
               if (indexFirstbit != -1)
                   FirstBitComboBox->setCurrentIndex(indexFirstbit);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Firstbit; // declare stopBits outside of the lambda

               connect(FirstBitComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Firstbit](int indexFirstbit){
                   // Retrieve the selected option
                   QSettings settings("SPIConfig.txt", QSettings::IniFormat);

                   QString Firstbit = FirstBitComboBox->itemText(indexFirstbit);
                   settings.beginGroup("SPI1Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Firstbit", Firstbit);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString FirstbitConfig = settings.value("Firstbit" , Firstbit).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Firstbit;
                   qDebug() << "Firstbit:" << FirstbitConfig;
               });


               // Create the vertical layout and add the form layout to it
               QVBoxLayout* verticalLayout = new QVBoxLayout(this);
               verticalLayout->addStretch();
               verticalLayout->addLayout(layout);
               verticalLayout->addStretch();

               // Create the horizontal layout and add the vertical layout to it
               QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
               horizontalLayout->addStretch();
               horizontalLayout->addLayout(verticalLayout);
               horizontalLayout->addStretch();

               // Set the widget layout to the horizontal layout

               widget->setLayout(horizontalLayout);
               widget->setGeometry(500, 500, 600, 500);

               QSettings settings("SPIConfig.txt", QSettings::IniFormat);

               qDebug() << "Settings file path: " << settings.fileName();



               settings.beginGroup("SPI1Configs");

               settings.setValue("Mode",  Mode);
               settings.setValue("NSS",  NSS);
               settings.setValue("Frameformat",  Frameformat);
               settings.setValue("Datasize",  DataSize);
               settings.setValue("Firstbit",  Firstbit);

               settings.endGroup();





    }
    void SPI2Config (){
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

                // Create Layout form for SPI
                QFormLayout* layout = new QFormLayout(this);


                QLabel* titleLabel = new QLabel("SPI2 configurations", this);

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


                // ----------------------Create Mode----------------------//

               QLabel* ModeLabel = new QLabel(tr("Mode"), this);
               QComboBox* ModeComboBox = new QComboBox(this);

               ModeComboBox->addItems(QStringList() << "Full-Duplex Master" << "Full-Duplex Slave" << "Half-Duplex Master " << "Half-Duplex Slave" );
               ModeComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
               // Set the minimum width to 100 pixels
               ModeComboBox->setMinimumWidth(10);
               ModeLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ModeComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


               layout->addRow(ModeLabel, ModeComboBox);

               //---------------------Save configuration into SPIConfig.txt---------------------------//

               QString ModeConfig = settings.value("Mode", "").toString();
               // Set the selected option in the combo box

               int indexMode = ModeComboBox->findText(ModeConfig);
               if (indexMode != -1)
                   ModeComboBox->setCurrentIndex(indexMode);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Mode; // declare stopBits outside of the lambda

               connect(ModeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Mode](int indexMode){
                   // Retrieve the selected option
                   QSettings settings("SPIConfig.txt", QSettings::IniFormat);

                   QString Mode = ModeComboBox->itemText(indexMode);
                   settings.beginGroup("SPI2Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Mode", Mode);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ModeConfig = settings.value("Mode" , Mode).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Mode;
                   qDebug() << "Mode:" << ModeConfig;
               });

               // ----------------------Create NSS----------------------//

               QLabel* NSSLabel = new QLabel(tr("Hardware NSS Signal"), this);
               QComboBox* NSSComboBox = new QComboBox(this);
               NSSComboBox->addItems(QStringList() << "Disable" << "Hardware NSS Input Signal" << "Hardware NSS Output Signal");
               NSSLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               NSSComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(NSSLabel, NSSComboBox);

               //---------------------Save configuration into SPIConfig.txt---------------------------//

               QString NSSConfig = settings.value("NSS", "").toString();
               // Set the selected option in the combo box

               int indexNSS = NSSComboBox->findText(NSSConfig);
               if (indexNSS != -1)
                   NSSComboBox->setCurrentIndex(indexNSS);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString NSS; // declare stopBits outside of the lambda

               connect(NSSComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&NSS](int indexNSS){
                   // Retrieve the selected option
                   QSettings settings("SPIConfig.txt", QSettings::IniFormat);

                   QString NSS = NSSComboBox->itemText(indexNSS);
                   settings.beginGroup("SPI2Configs");


                   // Store the selected option in the settings file
                   settings.setValue("NSS", NSS);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString NSSConfig = settings.value("NSS" , NSS).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << NSS;
                   qDebug() << "NSS:" << NSSConfig;
               });




               // ----------------------Create Frame Format----------------------//

               QLabel* FrameFormatLabel = new QLabel(tr("Frame Format"), this);
               QComboBox* FrameFormatComboBox = new QComboBox(this);
               FrameFormatComboBox->addItems(QStringList() << "Motorola" << "Texas Instruments");
               FrameFormatLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FrameFormatComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(FrameFormatLabel, FrameFormatComboBox);

               //---------------------Save configuration into SPIConfig.txt---------------------------//

               QString FrameformatConfig = settings.value("Frameformat", "").toString();
               // Set the selected option in the combo box

               int indexFrameformat = FrameFormatComboBox->findText(FrameformatConfig);
               if (indexFrameformat != -1)
                   FrameFormatComboBox->setCurrentIndex(indexFrameformat);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Frameformat; // declare stopBits outside of the lambda

               connect(FrameFormatComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Frameformat](int indexFrameformat){
                   // Retrieve the selected option
                   QSettings settings("SPIConfig.txt", QSettings::IniFormat);

                   QString Frameformat = FrameFormatComboBox->itemText(indexFrameformat);
                   settings.beginGroup("SPI2Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Frameformat", Frameformat);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString FrameformatConfig = settings.value("Frameformat" , Frameformat).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Frameformat;
                   qDebug() << "Frameformat:" << FrameformatConfig;
               });




               // ----------------------Create Data size----------------------//

               QLabel* DataSizeLabel = new QLabel(tr("Data Size"), this);
               QSpinBox* DataSizeSpinBox = new QSpinBox(this);
               DataSizeSpinBox->setMinimum(4);
               DataSizeSpinBox->setMaximum(32);

               DataSizeLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               DataSizeSpinBox->setStyleSheet("font:Arial 15px; color: gray; background-color: white;");
               layout->addRow(DataSizeLabel, DataSizeSpinBox);


               //---------------------Save configuration into SPIConfig.txt---------------------------//


               QString DataSizeConfig = settings.value("DataSize", "").toString();
               // Set the selected value in the spin box
               DataSizeSpinBox->setValue(DataSizeConfig.toInt());

               // Connect the spin box to the slot
               QString DataSize; // declare DataSize outside of the lambda
               connect(DataSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=,&DataSize](int value){
                   // Retrieve the selected value
                   QSettings settings("SPIConfig.txt", QSettings::IniFormat);

                   QString DataSize = QString::number(value);
                   settings.beginGroup("SPI2Configs");

                   // Store the selected value in the settings file
                   settings.setValue("DataSize", DataSize);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString DataSizeConfig = settings.value("DataSize" , DataSize).toString();
                   qDebug() << "selected value:" << DataSize;
                   qDebug() << "DataSize:" << DataSizeConfig;
               });



               // ----------------------Create First Bit----------------------//

               QLabel* FirstBitLabel = new QLabel(tr("First Bit"), this);
               QComboBox* FirstBitComboBox = new QComboBox(this);
               FirstBitComboBox->addItems(QStringList() << "LSB" << "MSB"  );
               FirstBitLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FirstBitComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(FirstBitLabel, FirstBitComboBox);
               layout->setContentsMargins(0, 0, 0, 0);
               layout->setSpacing(30);

               //---------------------Save configuration into SPIConfig.txt---------------------------//

               QString FirstbitConfig = settings.value("Firstbit", "").toString();
               // Set the selected option in the combo box

               int indexFirstbit = FirstBitComboBox->findText(FirstbitConfig);
               if (indexFirstbit != -1)
                   FirstBitComboBox->setCurrentIndex(indexFirstbit);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Firstbit; // declare stopBits outside of the lambda

               connect(FirstBitComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Firstbit](int indexFirstbit){
                   // Retrieve the selected option
                   QSettings settings("SPIConfig.txt", QSettings::IniFormat);

                   QString Firstbit = FirstBitComboBox->itemText(indexFirstbit);
                   settings.beginGroup("SPI2Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Firstbit", Firstbit);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString FirstbitConfig = settings.value("Firstbit" , Firstbit).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Firstbit;
                   qDebug() << "Firstbit:" << FirstbitConfig;
               });


               // Create the vertical layout and add the form layout to it
               QVBoxLayout* verticalLayout = new QVBoxLayout(this);
               verticalLayout->addStretch();
               verticalLayout->addLayout(layout);
               verticalLayout->addStretch();

               // Create the horizontal layout and add the vertical layout to it
               QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
               horizontalLayout->addStretch();
               horizontalLayout->addLayout(verticalLayout);
               horizontalLayout->addStretch();

               // Set the widget layout to the horizontal layout

               widget->setLayout(horizontalLayout);
               widget->setGeometry(500, 500, 600, 500);

               QSettings settings("SPIConfig.txt", QSettings::IniFormat);

               qDebug() << "Settings file path: " << settings.fileName();



               settings.beginGroup("SPI2Configs");

               settings.setValue("Mode",  Mode);
               settings.setValue("NSS",  NSS);
               settings.setValue("Frameformat",  Frameformat);
               settings.setValue("Datasize",  DataSize);
               settings.setValue("Firstbit",  Firstbit);

               settings.endGroup();






    }
    void I2CConfig (){
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

                // Create Layout form for I2C
                QFormLayout* layout = new QFormLayout(this);

                QLabel* titleLabel = new QLabel("I2C configurations", this);

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


                // ----------------------Create Timing----------------------//

               QLabel* TimingLabel = new QLabel(tr("Custom Timing"), this);
               QComboBox* TimingComboBox = new QComboBox(this);

               TimingComboBox->addItems(QStringList() << "Enable" << "Disable");
               TimingComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
               // Set the minimum width to 100 pixels
               TimingComboBox->setMinimumWidth(10);
               TimingLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               TimingComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


               layout->addRow(TimingLabel, TimingComboBox);

               // ----------------------- Save Timing configs into a I2CConfig.txt-----------------------------------//


               QString TimingConfig = settings.value("Timing", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexTiming = TimingComboBox->findText(TimingConfig);
               if (indexTiming != -1)
                   TimingComboBox->setCurrentIndex(indexTiming);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Timing; // declare stopBits outside of the lambda

               connect(TimingComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Timing](int indexTiming){
                   // Retrieve the selected option
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString Timing = TimingComboBox->itemText(indexTiming);
                   settings.beginGroup("I2CConfigs");


                   // Store the selected option in the settings file
                   settings.setValue("Timing", Timing);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString TimingConfig = settings.value("Timing" , Timing).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Timing;
                   qDebug() << "Timing:" << TimingConfig;
               });

               // ----------------------Create Speed Mode----------------------//

               QLabel* SpeedLabel = new QLabel(tr("I2C Speed Mode"), this);
               QComboBox* SpeedComboBox = new QComboBox(this);
               SpeedComboBox->addItems(QStringList() << "Standart Mode" << "Fast Mode " << "Fast Mode Plus");
               SpeedLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               SpeedComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(SpeedLabel, SpeedComboBox);



               // ----------------------- Save Speed configs into a I2CConfig.txt-----------------------------------//


               QString SpeedConfig = settings.value("Speed", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexSpeed = SpeedComboBox->findText(SpeedConfig);
               if (indexSpeed != -1)
                   SpeedComboBox->setCurrentIndex(indexSpeed);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Speed; // declare stopBits outside of the lambda

               connect(SpeedComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Speed](int indexSpeed){
                   // Retrieve the selected option
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString Speed = SpeedComboBox->itemText(indexSpeed);
                   settings.beginGroup("I2CConfigs");


                   // Store the selected option in the settings file
                   settings.setValue("Speed", Speed);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString SpeedConfig = settings.value("Speed" , Speed).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Speed;
                   qDebug() << "Speed:" << SpeedConfig;
               });





               // ----------------------Create Frequency Speed----------------------//

               QLabel* FrequencyLabel = new QLabel(tr("Speed Frequency"), this);
               QComboBox* FrequencyComboBox = new QComboBox(this);
               FrequencyComboBox->addItems(QStringList() << "200 KHz" << "400 KHz " << "1 MHz");






               FrequencyLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FrequencyComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(FrequencyLabel, FrequencyComboBox);



               // ----------------------- Save Frequency configs into a I2CConfig.txt-----------------------------------//


               QString FrequencyConfig = settings.value("Frequency", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexFrequency = FrequencyComboBox->findText(FrequencyConfig);
               if (indexFrequency != -1)
                   FrequencyComboBox->setCurrentIndex(indexFrequency);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Frequency; // declare stopBits outside of the lambda

               connect(FrequencyComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Frequency](int indexFrequency){
                   // Retrieve the selected option
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString Frequency = FrequencyComboBox->itemText(indexFrequency);
                   settings.beginGroup("I2CConfigs");


                   // Store the selected option in the settings file
                   settings.setValue("Frequency", Frequency);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString FrequencyConfig = settings.value("Frequency" , Frequency).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Frequency;
                   qDebug() << "Frequency:" << FrequencyConfig;
               });


               // ----------------------Create Rise Edge----------------------//

               QLabel* RiseLabel = new QLabel(tr("Rise Time"), this);
               QSpinBox* RiseSpinBox = new QSpinBox(this);
               RiseSpinBox->setMinimum(20);
               RiseSpinBox->setMaximum(1000);

               RiseLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               RiseSpinBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
               layout->addRow(RiseLabel, RiseSpinBox);



               //---------------------Save configuration into SPIConfig.txt---------------------------//


               QString RiseConfig = settings.value("Rise", "").toString();
               // Set the selected value in the spin box
               RiseSpinBox->setValue(RiseConfig.toInt());

               // Connect the spin box to the slot
               QString Rise; // declare Rise outside of the lambda
               connect(RiseSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=,&Rise](int value){
                   // Retrieve the selected value
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString Rise = QString::number(value);
                   settings.beginGroup("I2CConfigs");

                   // Store the selected value in the settings file
                   settings.setValue("Rise", Rise);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString RiseConfig = settings.value("Rise" , Rise).toString();
                   qDebug() << "selected value:" << Rise;
                   qDebug() << "Rise:" << RiseConfig;
               });





               // ----------------------Create Fall edge----------------------//

               QLabel* FallLabel = new QLabel(tr("Fall Time"), this);
               QSpinBox* FallSpinBox = new QSpinBox(this);
               FallSpinBox->setMinimum(10);
               FallSpinBox->setMaximum(300);

               FallLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FallSpinBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
               layout->addRow(FallLabel, FallSpinBox);



               //---------------------Save configuration into SPIConfig.txt---------------------------//


               QString FallConfig = settings.value("Fall", "").toString();
               // Set the selected value in the spin box
               FallSpinBox->setValue(FallConfig.toInt());

               // Connect the spin box to the slot
               QString Fall; // declare Fall outside of the lambda
               connect(FallSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=,&Fall](int value){
                   // Retrieve the selected value
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString Fall = QString::number(value);
                   settings.beginGroup("I2CConfigs");

                   // Store the selected value in the settings file
                   settings.setValue("Fall", Fall);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString FallConfig = settings.value("Fall" , Fall).toString();
                   qDebug() << "selected value:" << Fall;
                   qDebug() << "Fall:" << FallConfig;
               });



               // ----------------------Create Converter----------------------//

               QLabel* ConverterLabel = new QLabel(tr("Coefficient of Digital Converter"), this);
               QSpinBox* ConverterSpinBox = new QSpinBox(this);
               ConverterSpinBox->setMinimum(0);
               ConverterSpinBox->setMaximum(16);

               ConverterLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ConverterSpinBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
               layout->addRow(ConverterLabel, ConverterSpinBox);


               //---------------------Save configuration into SPIConfig.txt---------------------------//


               QString ConverterConfig = settings.value("Converter", "").toString();
               // Set the selected value in the spin box
               ConverterSpinBox->setValue(ConverterConfig.toInt());

               // Connect the spin box to the slot
               QString Converter; // declare Converter outside of the lambda
               connect(ConverterSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=,&Converter](int value){
                   // Retrieve the selected value
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString Converter = QString::number(value);
                   settings.beginGroup("I2CConfigs");

                   // Store the selected value in the settings file
                   settings.setValue("Converter", Converter);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ConverterConfig = settings.value("Converter" , Converter).toString();
                   qDebug() << "selected value:" << Converter;
                   qDebug() << "Converter:" << ConverterConfig;
               });


               // ----------------------Create Analog Filter----------------------//

               QLabel* AnalogFilterLabel = new QLabel(tr("Analog Filter"), this);
               QComboBox* AnalogFilterComboBox = new QComboBox(this);
               AnalogFilterComboBox->addItems(QStringList() << "Enabled" << "Disabled"  );
               AnalogFilterLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               AnalogFilterComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");



               // ----------------------- Save Analog Filter configs into a I2CConfig.txt-----------------------------------//


               QString AnalogFilterConfig = settings.value("AnalogFilter", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexAnalogFilter = AnalogFilterComboBox->findText(AnalogFilterConfig);
               if (indexAnalogFilter != -1)
                   AnalogFilterComboBox->setCurrentIndex(indexAnalogFilter);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString AnalogFilter; // declare stopBits outside of the lambda

               connect(AnalogFilterComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&AnalogFilter](int indexAnalogFilter){
                   // Retrieve the selected option
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString AnalogFilter = AnalogFilterComboBox->itemText(indexAnalogFilter);
                   settings.beginGroup("I2CConfigs");


                   // Store the selected option in the settings file
                   settings.setValue("AnalogFilter", AnalogFilter);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString AnalogFilterConfig = settings.value("AnalogFilter" , AnalogFilter).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << AnalogFilter;
                   qDebug() << "AnalogFilter:" << AnalogFilterConfig;
               });


               layout->addRow(AnalogFilterLabel, AnalogFilterComboBox);
               layout->setContentsMargins(0, 0, 0, 0);
               layout->setSpacing(30);

               // Create the vertical layout and add the form layout to it
               QVBoxLayout* verticalLayout = new QVBoxLayout(this);
               verticalLayout->addStretch();
               verticalLayout->addLayout(layout);
               verticalLayout->addStretch();

               // Create the horizontal layout and add the vertical layout to it
               QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
               horizontalLayout->addStretch();
               horizontalLayout->addLayout(verticalLayout);
               horizontalLayout->addStretch();

               // Set the widget layout to the horizontal layout

               widget->setLayout(horizontalLayout);
               widget->setGeometry(500, 500, 600, 500);


               QSettings settings("I2CConfig.txt", QSettings::IniFormat);

               qDebug() << "Settings file path: " << settings.fileName();



               settings.beginGroup("I2CConfigs");

               settings.setValue("Timing",  Timing);
               settings.setValue("Speed",  Speed);
               settings.setValue("Frequency",  Frequency);
               settings.setValue("Rise",  Rise);
               settings.setValue("Fall",  Fall);
               settings.setValue("Converter",  Converter);
               settings.setValue("AnalogFilter",  AnalogFilter);


               settings.endGroup();




    }

    void I2C1Config (){
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

                // Create Layout form for I2C
                QFormLayout* layout = new QFormLayout(this);

                QLabel* titleLabel = new QLabel("I2C1 configurations", this);

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


                // ----------------------Create Timing----------------------//

               QLabel* TimingLabel = new QLabel(tr("Custom Timing"), this);
               QComboBox* TimingComboBox = new QComboBox(this);

               TimingComboBox->addItems(QStringList() << "Enable" << "Disable");
               TimingComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
               // Set the minimum width to 100 pixels
               TimingComboBox->setMinimumWidth(10);
               TimingLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               TimingComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


               layout->addRow(TimingLabel, TimingComboBox);


               // ----------------------- Save Timing configs into a I2CConfig.txt-----------------------------------//


               QString TimingConfig = settings.value("Timing", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexTiming = TimingComboBox->findText(TimingConfig);
               if (indexTiming != -1)
                   TimingComboBox->setCurrentIndex(indexTiming);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Timing; // declare stopBits outside of the lambda

               connect(TimingComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Timing](int indexTiming){
                   // Retrieve the selected option
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString Timing = TimingComboBox->itemText(indexTiming);
                   settings.beginGroup("I2C1Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Timing", Timing);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString TimingConfig = settings.value("Timing" , Timing).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Timing;
                   qDebug() << "Timing:" << TimingConfig;
               });




               // ----------------------Create Speed Mode----------------------//

               QLabel* SpeedLabel = new QLabel(tr("I2C Speed Mode"), this);
               QComboBox* SpeedComboBox = new QComboBox(this);
               SpeedComboBox->addItems(QStringList() << "Standart Mode" << "Fast Mode " << "Fast Mode Plus");
               SpeedLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               SpeedComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(SpeedLabel, SpeedComboBox);


               // ----------------------- Save Speed configs into a I2CConfig.txt-----------------------------------//


               QString SpeedConfig = settings.value("Speed", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexSpeed = SpeedComboBox->findText(SpeedConfig);
               if (indexSpeed != -1)
                   SpeedComboBox->setCurrentIndex(indexSpeed);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Speed; // declare stopBits outside of the lambda

               connect(SpeedComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Speed](int indexSpeed){
                   // Retrieve the selected option
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString Speed = SpeedComboBox->itemText(indexSpeed);
                   settings.beginGroup("I2C1Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Speed", Speed);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString SpeedConfig = settings.value("Speed" , Speed).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Speed;
                   qDebug() << "Speed:" << SpeedConfig;
               });


               // ----------------------Create Frequency Speed----------------------//

               QLabel* FrequencyLabel = new QLabel(tr("Speed Frequency"), this);
               QComboBox* FrequencyComboBox = new QComboBox(this);
               FrequencyComboBox->addItems(QStringList() << "200 KHz" << "400 KHz " << "1 MHz");






               FrequencyLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FrequencyComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(FrequencyLabel, FrequencyComboBox);



               // ----------------------- Save Frequency configs into a I2CConfig.txt-----------------------------------//


               QString FrequencyConfig = settings.value("Frequency", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexFrequency = FrequencyComboBox->findText(FrequencyConfig);
               if (indexFrequency != -1)
                   FrequencyComboBox->setCurrentIndex(indexFrequency);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Frequency; // declare stopBits outside of the lambda

               connect(FrequencyComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Frequency](int indexFrequency){
                   // Retrieve the selected option
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString Frequency = FrequencyComboBox->itemText(indexFrequency);
                   settings.beginGroup("I2C1Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Frequency", Frequency);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString FrequencyConfig = settings.value("Frequency" , Frequency).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Frequency;
                   qDebug() << "Frequency:" << FrequencyConfig;
               });



               // ----------------------Create Rise Edge----------------------//

               QLabel* RiseLabel = new QLabel(tr("Rise Time"), this);
               QSpinBox* RiseSpinBox = new QSpinBox(this);
               RiseSpinBox->setMinimum(20);
               RiseSpinBox->setMaximum(1000);

               RiseLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               RiseSpinBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
               layout->addRow(RiseLabel, RiseSpinBox);



               //---------------------Save configuration into SPIConfig.txt---------------------------//


               QString RiseConfig = settings.value("Rise", "").toString();
               // Set the selected value in the spin box
               RiseSpinBox->setValue(RiseConfig.toInt());

               // Connect the spin box to the slot
               QString Rise; // declare Rise outside of the lambda
               connect(RiseSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=,&Rise](int value){
                   // Retrieve the selected value
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString Rise = QString::number(value);
                   settings.beginGroup("I2C1Configs");

                   // Store the selected value in the settings file
                   settings.setValue("Rise", Rise);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString RiseConfig = settings.value("Rise" , Rise).toString();
                   qDebug() << "selected value:" << Rise;
                   qDebug() << "Rise:" << RiseConfig;
               });




               // ----------------------Create Fall edge----------------------//

               QLabel* FallLabel = new QLabel(tr("Fall Time"), this);
               QSpinBox* FallSpinBox = new QSpinBox(this);
               FallSpinBox->setMinimum(10);
               FallSpinBox->setMaximum(300);

               FallLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FallSpinBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
               layout->addRow(FallLabel, FallSpinBox);


               //---------------------Save configuration into SPIConfig.txt---------------------------//


               QString FallConfig = settings.value("Fall", "").toString();
               // Set the selected value in the spin box
               FallSpinBox->setValue(FallConfig.toInt());

               // Connect the spin box to the slot
               QString Fall; // declare Fall outside of the lambda
               connect(FallSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=,&Fall](int value){
                   // Retrieve the selected value
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString Fall = QString::number(value);
                   settings.beginGroup("I2C1Configs");

                   // Store the selected value in the settings file
                   settings.setValue("Fall", Fall);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString FallConfig = settings.value("Fall" , Fall).toString();
                   qDebug() << "selected value:" << Fall;
                   qDebug() << "Fall:" << FallConfig;
               });



               // ----------------------Create Converter----------------------//

               QLabel* ConverterLabel = new QLabel(tr("Coefficient of Digital Converter"), this);
               QSpinBox* ConverterSpinBox = new QSpinBox(this);
               ConverterSpinBox->setMinimum(0);
               ConverterSpinBox->setMaximum(16);

               ConverterLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ConverterSpinBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
               layout->addRow(ConverterLabel, ConverterSpinBox);



               //---------------------Save configuration into SPIConfig.txt---------------------------//


               QString ConverterConfig = settings.value("Converter", "").toString();
               // Set the selected value in the spin box
               ConverterSpinBox->setValue(ConverterConfig.toInt());

               // Connect the spin box to the slot
               QString Converter; // declare Converter outside of the lambda
               connect(ConverterSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=,&Converter](int value){
                   // Retrieve the selected value
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString Converter = QString::number(value);
                   settings.beginGroup("I2C1Configs");

                   // Store the selected value in the settings file
                   settings.setValue("Converter", Converter);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ConverterConfig = settings.value("Converter" , Converter).toString();
                   qDebug() << "selected value:" << Converter;
                   qDebug() << "Converter:" << ConverterConfig;
               });


               // ----------------------Create Analog Filter----------------------//

               QLabel* AnalogFilterLabel = new QLabel(tr("Analog Filter"), this);
               QComboBox* AnalogFilterComboBox = new QComboBox(this);
               AnalogFilterComboBox->addItems(QStringList() << "Enabled" << "Disabled"  );
               AnalogFilterLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               AnalogFilterComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               // ----------------------- Save Analog Filter configs into a I2CConfig.txt-----------------------------------//


               QString AnalogFilterConfig = settings.value("AnalogFilter", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexAnalogFilter = AnalogFilterComboBox->findText(AnalogFilterConfig);
               if (indexAnalogFilter != -1)
                   AnalogFilterComboBox->setCurrentIndex(indexAnalogFilter);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString AnalogFilter; // declare stopBits outside of the lambda

               connect(AnalogFilterComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&AnalogFilter](int indexAnalogFilter){
                   // Retrieve the selected option
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString AnalogFilter = AnalogFilterComboBox->itemText(indexAnalogFilter);
                   settings.beginGroup("I2C1Configs");


                   // Store the selected option in the settings file
                   settings.setValue("AnalogFilter", AnalogFilter);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString AnalogFilterConfig = settings.value("AnalogFilter" , AnalogFilter).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << AnalogFilter;
                   qDebug() << "AnalogFilter:" << AnalogFilterConfig;
               });

               layout->addRow(AnalogFilterLabel, AnalogFilterComboBox);
               layout->setContentsMargins(0, 0, 0, 0);
               layout->setSpacing(30);

               // Create the vertical layout and add the form layout to it
               QVBoxLayout* verticalLayout = new QVBoxLayout(this);
               verticalLayout->addStretch();
               verticalLayout->addLayout(layout);
               verticalLayout->addStretch();

               // Create the horizontal layout and add the vertical layout to it
               QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
               horizontalLayout->addStretch();
               horizontalLayout->addLayout(verticalLayout);
               horizontalLayout->addStretch();

               // Set the widget layout to the horizontal layout

               widget->setLayout(horizontalLayout);
               widget->setGeometry(500, 500, 600, 500);



               QSettings settings("I2CConfig.txt", QSettings::IniFormat);

               qDebug() << "Settings file path: " << settings.fileName();



               settings.beginGroup("I2C1Configs");

               settings.setValue("Timing",  Timing);
               settings.setValue("Speed",  Speed);
               settings.setValue("Frequency",  Frequency);
               settings.setValue("Rise",  Rise);
               settings.setValue("Fall",  Fall);
               settings.setValue("Converter",  Converter);
               settings.setValue("AnalogFilter",  AnalogFilter);


               settings.endGroup();






    }

    void I2C2Config (){
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

                // Create Layout form for I2C
                QFormLayout* layout = new QFormLayout(this);

                QLabel* titleLabel = new QLabel("I2C2 configurations", this);

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


                // ----------------------Create Timing----------------------//

               QLabel* TimingLabel = new QLabel(tr("Custom Timing"), this);
               QComboBox* TimingComboBox = new QComboBox(this);

               TimingComboBox->addItems(QStringList() << "Enable" << "Disable");
               TimingComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
               // Set the minimum width to 100 pixels
               TimingComboBox->setMinimumWidth(10);
               TimingLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               TimingComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


               layout->addRow(TimingLabel, TimingComboBox);


               // ----------------------- Save Timing configs into a I2CConfig.txt-----------------------------------//


               QString TimingConfig = settings.value("Timing", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexTiming = TimingComboBox->findText(TimingConfig);
               if (indexTiming != -1)
                   TimingComboBox->setCurrentIndex(indexTiming);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Timing; // declare stopBits outside of the lambda

               connect(TimingComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Timing](int indexTiming){
                   // Retrieve the selected option
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString Timing = TimingComboBox->itemText(indexTiming);
                   settings.beginGroup("I2C2Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Timing", Timing);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString TimingConfig = settings.value("Timing" , Timing).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Timing;
                   qDebug() << "Timing:" << TimingConfig;
               });

               // ----------------------Create Speed Mode----------------------//

               QLabel* SpeedLabel = new QLabel(tr("I2C Speed Mode"), this);
               QComboBox* SpeedComboBox = new QComboBox(this);
               SpeedComboBox->addItems(QStringList() << "Standart Mode" << "Fast Mode " << "Fast Mode Plus");
               SpeedLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               SpeedComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(SpeedLabel, SpeedComboBox);



               // ----------------------- Save Speed configs into a I2CConfig.txt-----------------------------------//


               QString SpeedConfig = settings.value("Speed", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexSpeed = SpeedComboBox->findText(SpeedConfig);
               if (indexSpeed != -1)
                   SpeedComboBox->setCurrentIndex(indexSpeed);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Speed; // declare stopBits outside of the lambda

               connect(SpeedComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Speed](int indexSpeed){
                   // Retrieve the selected option
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString Speed = SpeedComboBox->itemText(indexSpeed);
                   settings.beginGroup("I2C2Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Speed", Speed);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString SpeedConfig = settings.value("Speed" , Speed).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Speed;
                   qDebug() << "Speed:" << SpeedConfig;
               });


               // ----------------------Create Frequency Speed----------------------//

               QLabel* FrequencyLabel = new QLabel(tr("Speed Frequency"), this);
               QComboBox* FrequencyComboBox = new QComboBox(this);
               FrequencyComboBox->addItems(QStringList() << "200 KHz" << "400 KHz " << "1 MHz");
               FrequencyLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FrequencyComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(FrequencyLabel, FrequencyComboBox);

               // ----------------------- Save Frequency configs into a I2CConfig.txt-----------------------------------//


               QString FrequencyConfig = settings.value("Frequency", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexFrequency = FrequencyComboBox->findText(FrequencyConfig);
               if (indexFrequency != -1)
                   FrequencyComboBox->setCurrentIndex(indexFrequency);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Frequency; // declare stopBits outside of the lambda

               connect(FrequencyComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Frequency](int indexFrequency){
                   // Retrieve the selected option
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString Frequency = FrequencyComboBox->itemText(indexFrequency);
                   settings.beginGroup("I2C2Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Frequency", Frequency);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString FrequencyConfig = settings.value("Frequency" , Frequency).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Frequency;
                   qDebug() << "Frequency:" << FrequencyConfig;
               });


               // ----------------------Create Rise Edge----------------------//

               QLabel* RiseLabel = new QLabel(tr("Rise Time"), this);
               QSpinBox* RiseSpinBox = new QSpinBox(this);
               RiseSpinBox->setMinimum(20);
               RiseSpinBox->setMaximum(1000);

               RiseLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               RiseSpinBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
               layout->addRow(RiseLabel, RiseSpinBox);


               //---------------------Save configuration into SPIConfig.txt---------------------------//


               QString RiseConfig = settings.value("Rise", "").toString();
               // Set the selected value in the spin box
               RiseSpinBox->setValue(RiseConfig.toInt());

               // Connect the spin box to the slot
               QString Rise; // declare Rise outside of the lambda
               connect(RiseSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=,&Rise](int value){
                   // Retrieve the selected value
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString Rise = QString::number(value);
                   settings.beginGroup("I2C2Configs");

                   // Store the selected value in the settings file
                   settings.setValue("Rise", Rise);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString RiseConfig = settings.value("Rise" , Rise).toString();
                   qDebug() << "selected value:" << Rise;
                   qDebug() << "Rise:" << RiseConfig;
               });




               // ----------------------Create Fall edge----------------------//

               QLabel* FallLabel = new QLabel(tr("Fall Time"), this);
               QSpinBox* FallSpinBox = new QSpinBox(this);
               FallSpinBox->setMinimum(10);
               FallSpinBox->setMaximum(300);

               FallLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FallSpinBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
               layout->addRow(FallLabel, FallSpinBox);


               //---------------------Save configuration into SPIConfig.txt---------------------------//


               QString FallConfig = settings.value("Fall", "").toString();
               // Set the selected value in the spin box
               FallSpinBox->setValue(FallConfig.toInt());

               // Connect the spin box to the slot
               QString Fall; // declare Fall outside of the lambda
               connect(FallSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=,&Fall](int value){
                   // Retrieve the selected value
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString Fall = QString::number(value);
                   settings.beginGroup("I2C2Configs");

                   // Store the selected value in the settings file
                   settings.setValue("Fall", Fall);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString FallConfig = settings.value("Fall" , Fall).toString();
                   qDebug() << "selected value:" << Fall;
                   qDebug() << "Fall:" << FallConfig;
               });



               // ----------------------Create Converter----------------------//

               QLabel* ConverterLabel = new QLabel(tr("Coefficient of Digital Converter"), this);
               QSpinBox* ConverterSpinBox = new QSpinBox(this);
               ConverterSpinBox->setMinimum(0);
               ConverterSpinBox->setMaximum(16);

               ConverterLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ConverterSpinBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
               layout->addRow(ConverterLabel, ConverterSpinBox);


               //---------------------Save configuration into SPIConfig.txt---------------------------//


               QString ConverterConfig = settings.value("Converter", "").toString();
               // Set the selected value in the spin box
               ConverterSpinBox->setValue(ConverterConfig.toInt());

               // Connect the spin box to the slot
               QString Converter; // declare Converter outside of the lambda
               connect(ConverterSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=,&Converter](int value){
                   // Retrieve the selected value
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString Converter = QString::number(value);
                   settings.beginGroup("I2C2Configs");

                   // Store the selected value in the settings file
                   settings.setValue("Converter", Converter);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ConverterConfig = settings.value("Converter" , Converter).toString();
                   qDebug() << "selected value:" << Converter;
                   qDebug() << "Converter:" << ConverterConfig;
               });



               // ----------------------Create Analog Filter----------------------//

               QLabel* AnalogFilterLabel = new QLabel(tr("Analog Filter"), this);
               QComboBox* AnalogFilterComboBox = new QComboBox(this);
               AnalogFilterComboBox->addItems(QStringList() << "Enabled" << "Disabled"  );
               AnalogFilterLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               AnalogFilterComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               // ----------------------- Save Analog Filter configs into a I2CConfig.txt-----------------------------------//


               QString AnalogFilterConfig = settings.value("AnalogFilter", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexAnalogFilter = AnalogFilterComboBox->findText(AnalogFilterConfig);
               if (indexAnalogFilter != -1)
                   AnalogFilterComboBox->setCurrentIndex(indexAnalogFilter);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString AnalogFilter; // declare stopBits outside of the lambda

               connect(AnalogFilterComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&AnalogFilter](int indexAnalogFilter){
                   // Retrieve the selected option
                   QSettings settings("I2CConfig.txt", QSettings::IniFormat);

                   QString AnalogFilter = AnalogFilterComboBox->itemText(indexAnalogFilter);
                   settings.beginGroup("I2C2Configs");


                   // Store the selected option in the settings file
                   settings.setValue("AnalogFilter", AnalogFilter);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString AnalogFilterConfig = settings.value("AnalogFilter" , AnalogFilter).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << AnalogFilter;
                   qDebug() << "AnalogFilter:" << AnalogFilterConfig;
               });

               layout->addRow(AnalogFilterLabel, AnalogFilterComboBox);
               layout->setContentsMargins(0, 0, 0, 0);
               layout->setSpacing(30);

               // Create the vertical layout and add the form layout to it
               QVBoxLayout* verticalLayout = new QVBoxLayout(this);
               verticalLayout->addStretch();
               verticalLayout->addLayout(layout);
               verticalLayout->addStretch();

               // Create the horizontal layout and add the vertical layout to it
               QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
               horizontalLayout->addStretch();
               horizontalLayout->addLayout(verticalLayout);
               horizontalLayout->addStretch();

               // Set the widget layout to the horizontal layout

               widget->setLayout(horizontalLayout);
               widget->setGeometry(500, 500, 600, 500);


               QSettings settings("I2CConfig.txt", QSettings::IniFormat);

               qDebug() << "Settings file path: " << settings.fileName();



               settings.beginGroup("I2C2Configs");

               settings.setValue("Timing",  Timing);
               settings.setValue("Speed",  Speed);
               settings.setValue("Frequency",  Frequency);
               settings.setValue("Rise",  Rise);
               settings.setValue("Fall",  Fall);
               settings.setValue("Converter",  Converter);
               settings.setValue("AnalogFilter",  AnalogFilter);


               settings.endGroup();




    }
    void ADCConfig (){
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

                // Create Layout form for ADC
                QFormLayout* layout = new QFormLayout(this);

                // Create a QLabel for "DAC configurations" and center it horizontally
                QLabel* titleLabel = new QLabel("ADC configurations", this);

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





                // ----------------------Create Channel Choices----------------------//

               QLabel* ChannelLabel = new QLabel(tr("Select Channel"), this);
               QComboBox* ChannelComboBox = new QComboBox(this);

               ChannelComboBox->addItems(QStringList() << "IN2" << "IN3" << "IN4" <<"IN5" << "IN6" << "IN7" << "IN8" << "IN9" << "IN10" << "IN11" << "IN14" << "IN15" << "IN16" << "IN17" <<"IN18" <<"IN19");
               // Create the second QComboBox and add it as an item to the first combo box


               ChannelComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
               // Set the minimum width to 100 pixels
               ChannelComboBox->setMinimumWidth(10);
               ChannelLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ChannelComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


               layout->addRow(ChannelLabel, ChannelComboBox);


               // ----------------------- Save Channel Choices configs into a ADCConfig.txt-----------------------------------//


               QString ChannelConfig = settings.value("Channel", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexChannel = ChannelComboBox->findText(ChannelConfig);
               if (indexChannel != -1)
                   ChannelComboBox->setCurrentIndex(indexChannel);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Channel; // declare stopBits outside of the lambda

               connect(ChannelComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Channel](int indexChannel){
                   // Retrieve the selected option
                   QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                   QString Channel = ChannelComboBox->itemText(indexChannel);
                   settings.beginGroup("ADCConfigs");


                   // Store the selected option in the settings file
                   settings.setValue("Channel", Channel);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ChannelConfig = settings.value("Channel" , Channel).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Channel;
                   qDebug() << "Channel:" << ChannelConfig;
               });

               // ----------------------Create Resolution Mode----------------------//

               QLabel* ResolutionLabel = new QLabel(tr("ADC Resolution Bit"), this);
               QComboBox* ResolutionComboBox = new QComboBox(this);
               ResolutionComboBox->addItems(QStringList() << "ADC 8-Bit Resolution" << "ADC 10-Bit Resolution" << "ADC 12-Bit Resolution" << "ADC 14-Bit Resolution" << "ADC 16-Bit Resolution"<< "ADC 12-Bit Optimized Resolution" << "ADC 14-Bit Optimized Resolution"  );
               ResolutionLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ResolutionComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(ResolutionLabel, ResolutionComboBox);


               // ----------------------- Save Resolution Choices configs into a ADCConfig.txt-----------------------------------//


               QString ResolutionConfig = settings.value("Resolution", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexResolution = ResolutionComboBox->findText(ResolutionConfig);
               if (indexResolution != -1)
                   ResolutionComboBox->setCurrentIndex(indexResolution);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Resolution; // declare stopBits outside of the lambda

               connect(ResolutionComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Resolution](int indexResolution){
                   // Retrieve the selected option
                   QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                   QString Resolution = ResolutionComboBox->itemText(indexResolution);
                   settings.beginGroup("ADCConfigs");


                   // Store the selected option in the settings file
                   settings.setValue("Resolution", Resolution);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ResolutionConfig = settings.value("Resolution" , Resolution).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Resolution;
                   qDebug() << "Resolution:" << ResolutionConfig;
               });


               // ----------------------Create Scan Mode----------------------//

               QLabel* ScanLabel = new QLabel(tr("Scan Conversion Mode"), this);
               QComboBox* ScanComboBox = new QComboBox(this);
               ScanComboBox->addItems(QStringList() << "Disabled" );
               ScanLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ScanComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(ScanLabel, ScanComboBox);

               // ----------------------- Save Scan Mode Choices configs into a ADCConfig.txt-----------------------------------//


               QString ScanConfig = settings.value("Scan", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexScan = ScanComboBox->findText(ScanConfig);
               if (indexScan != -1)
                   ScanComboBox->setCurrentIndex(indexScan);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Scan; // declare stopBits outside of the lambda

               connect(ScanComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Scan](int indexScan){
                   // Retrieve the selected option
                   QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                   QString Scan = ScanComboBox->itemText(indexScan);
                   settings.beginGroup("ADCConfigs");


                   // Store the selected option in the settings file
                   settings.setValue("Scan", Scan);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ScanConfig = settings.value("Scan" , Scan).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Scan;
                   qDebug() << "Scan:" << ScanConfig;
               });


               // ----------------------Create continuous Mode----------------------//

               QLabel* ContinuousLabel = new QLabel(tr("Continuous Conversion Mode"), this);
               QComboBox* ContinuousComboBox = new QComboBox(this);


               ContinuousComboBox->addItems(QStringList() << "Enabled" << "Disabled");

               ContinuousLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ContinuousComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
               layout->addRow(ContinuousLabel, ContinuousComboBox);


               // ----------------------- Save Continuous Mode Choices configs into a ADCConfig.txt-----------------------------------//


               QString ContinuousConfig = settings.value("Continuous", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexContinuous = ContinuousComboBox->findText(ContinuousConfig);
               if (indexContinuous != -1)
                   ContinuousComboBox->setCurrentIndex(indexContinuous);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Continuous; // declare stopBits outside of the lambda

               connect(ContinuousComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Continuous](int indexContinuous){
                   // Retrieve the selected option
                   QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                   QString Continuous = ContinuousComboBox->itemText(indexContinuous);
                   settings.beginGroup("ADCConfigs");


                   // Store the selected option in the settings file
                   settings.setValue("Continuous", Continuous);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ContinuousConfig = settings.value("Continuous" , Continuous).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Continuous;
                   qDebug() << "Continuous:" << ContinuousConfig;
               });


               // ----------------------Create Discontinuous Mode----------------------//

              QLabel* DiscontinuousLabel = new QLabel(tr("Discontinuous Conversion Mode"), this);
              QComboBox* DiscontinuousComboBox = new QComboBox(this);


              DiscontinuousComboBox->addItems(QStringList() << "Enabled" << "Disabled");

              DiscontinuousLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
              DiscontinuousComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
              layout->addRow(DiscontinuousLabel, DiscontinuousComboBox);


              // ----------------------- Save Discontinuous Mode Choices configs into a ADCConfig.txt-----------------------------------//


              QString DiscontinuousConfig = settings.value("Discontinuous", "").toString();
//                QString stopBitsConfig;
              // Set the selected option in the combo box

              int indexDiscontinuous = DiscontinuousComboBox->findText(DiscontinuousConfig);
              if (indexDiscontinuous != -1)
                  DiscontinuousComboBox->setCurrentIndex(indexDiscontinuous);

              // Connect the combo box to the slot
   //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
              QString Discontinuous; // declare stopBits outside of the lambda

              connect(DiscontinuousComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Discontinuous](int indexDiscontinuous){
                  // Retrieve the selected option
                  QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                  QString Discontinuous = DiscontinuousComboBox->itemText(indexDiscontinuous);
                  settings.beginGroup("ADCConfigs");


                  // Store the selected option in the settings file
                  settings.setValue("Discontinuous", Discontinuous);
                  settings.endGroup();

                  // Retrieve the stored value and print to the console
                  QString DiscontinuousConfig = settings.value("Discontinuous" , Discontinuous).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                  qDebug() << "selected option:" << Discontinuous;
                  qDebug() << "Discontinuous:" << DiscontinuousConfig;
              });


              // ----------------------Create End of Conversion Mode----------------------//

             QLabel* EndConversionLabel = new QLabel(tr("End of Conversion Mode"), this);
             QComboBox* EndConversionComboBox = new QComboBox(this);


             EndConversionComboBox->addItems(QStringList() << "End of Single Conversion" << "End of sequence Conversion");

             EndConversionLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
             EndConversionComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
             layout->addRow(EndConversionLabel, EndConversionComboBox);

             // ----------------------- Save End of Conversion Choices configs into a ADCConfig.txt-----------------------------------//


             QString EndConversionConfig = settings.value("EndConversion", "").toString();
//                QString stopBitsConfig;
             // Set the selected option in the combo box

             int indexEndConversion = EndConversionComboBox->findText(EndConversionConfig);
             if (indexEndConversion != -1)
                 EndConversionComboBox->setCurrentIndex(indexEndConversion);

             // Connect the combo box to the slot
  //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
             QString EndConversion; // declare stopBits outside of the lambda

             connect(EndConversionComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&EndConversion](int indexEndConversion){
                 // Retrieve the selected option
                 QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                 QString EndConversion = EndConversionComboBox->itemText(indexEndConversion);
                 settings.beginGroup("ADCConfigs");


                 // Store the selected option in the settings file
                 settings.setValue("EndConversion", EndConversion);
                 settings.endGroup();

                 // Retrieve the stored value and print to the console
                 QString EndConversionConfig = settings.value("EndConversion" , EndConversion).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                 qDebug() << "selected option:" << EndConversion;
                 qDebug() << "EndConversion:" << EndConversionConfig;
             });


             // ----------------------Create Behavior Bit----------------------//

            QLabel* BehaviorLabel = new QLabel(tr("Overrun Behavior"), this);
            QComboBox* BehaviorComboBox = new QComboBox(this);


            BehaviorComboBox->addItems(QStringList() << "Overrun Data Preserved" << "Overrun Data Overwritten");

            BehaviorLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
            BehaviorComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
            layout->addRow(BehaviorLabel, BehaviorComboBox);


            // ----------------------- Save Behavior Bit Choices configs into a ADCConfig.txt-----------------------------------//


            QString BehaviorConfig = settings.value("Behavior", "").toString();
//                QString stopBitsConfig;
            // Set the selected option in the combo box

            int indexBehavior = BehaviorComboBox->findText(BehaviorConfig);
            if (indexBehavior != -1)
                BehaviorComboBox->setCurrentIndex(indexBehavior);

            // Connect the combo box to the slot
 //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
            QString Behavior; // declare stopBits outside of the lambda

            connect(BehaviorComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Behavior](int indexBehavior){
                // Retrieve the selected option
                QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                QString Behavior = BehaviorComboBox->itemText(indexBehavior);
                settings.beginGroup("ADCConfigs");


                // Store the selected option in the settings file
                settings.setValue("Behavior", Behavior);
                settings.endGroup();

                // Retrieve the stored value and print to the console
                QString BehaviorConfig = settings.value("Behavior" , Behavior).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                qDebug() << "selected option:" << Behavior;
                qDebug() << "Behavior:" << BehaviorConfig;
            });



            // ----------------------Create Left Bit----------------------//

               QLabel* LeftBitLabel = new QLabel(tr("Left Bit Shift"), this);
               QComboBox* LeftBitComboBox = new QComboBox(this);
               LeftBitComboBox->addItems(QStringList() << "No Bit Shift" << "1 Bit Shift" << "2 Bit Shift"<<  "3 Bit Shift" << "4 Bit Shift" <<"5 Bit Shift" << "6 Bit Shift" <<"7 Bit Shift" <<"8 Bit Shift" <<"9 Bit Shift" <<"10 Bit Shift" <<"11 Bit Shift" << "12 Bit Shift" <<"13 Bit Shift" <<"14 Bit Shift" << "15 Bit Shift" );
               LeftBitLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               LeftBitComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               // ----------------------- Save Left Bit Choices configs into a ADCConfig.txt-----------------------------------//


               QString LeftBitConfig = settings.value("LeftBit", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexLeftBit = LeftBitComboBox->findText(LeftBitConfig);
               if (indexLeftBit != -1)
                   LeftBitComboBox->setCurrentIndex(indexLeftBit);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString LeftBit; // declare stopBits outside of the lambda

               connect(LeftBitComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&LeftBit](int indexLeftBit){
                   // Retrieve the selected option
                   QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                   QString LeftBit = LeftBitComboBox->itemText(indexLeftBit);
                   settings.beginGroup("ADCConfigs");


                   // Store the selected option in the settings file
                   settings.setValue("LeftBit", LeftBit);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString LeftBitConfig = settings.value("LeftBit" , LeftBit).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << LeftBit;
                   qDebug() << "LeftBit:" << LeftBitConfig;
               });

               layout->addRow(LeftBitLabel, LeftBitComboBox);
               layout->setContentsMargins(0, 0, 0, 0);
               layout->setSpacing(30);

               // Create the vertical layout and add the form layout to it
               QVBoxLayout* verticalLayout = new QVBoxLayout(this);
               verticalLayout->addStretch();
               verticalLayout->addLayout(layout);
               verticalLayout->addStretch();

               // Create the horizontal layout and add the vertical layout to it
               QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
               horizontalLayout->addStretch();
               horizontalLayout->addLayout(verticalLayout);
               horizontalLayout->addStretch();

               // Set the widget layout to the horizontal layout

               widget->setLayout(horizontalLayout);
               widget->setGeometry(500, 500, 600, 500);


               QSettings settings("ADCConfig.txt", QSettings::IniFormat);

               qDebug() << "Settings file path: " << settings.fileName();



               settings.beginGroup("ADCConfigs");

               settings.setValue("Channel",  Channel);
               settings.setValue("Resolution",  Resolution);
               settings.setValue("Scan",  ScanComboBox->currentText());
               settings.setValue("Continuous",  Continuous);
               settings.setValue("Discontinuous",  Discontinuous);
               settings.setValue("EndConversion",  EndConversion);
               settings.setValue("Behavior",  Behavior);
               settings.setValue("LeftBit",  LeftBit);


               settings.endGroup();



    }

    void ADC1Config (){
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

                // Create Layout form for ADC
                QFormLayout* layout = new QFormLayout(this);

                // Create a QLabel for "DAC configurations" and center it horizontally
                QLabel* titleLabel = new QLabel("ADC1 configurations", this);

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



                // ----------------------Create Channel Choices----------------------//

               QLabel* ChannelLabel = new QLabel(tr("Select Channel"), this);
               QComboBox* ChannelComboBox = new QComboBox(this);

               ChannelComboBox->addItems(QStringList() << "IN2" << "IN3" << "IN4" <<"IN5" << "IN6" << "IN7" << "IN8" << "IN9" << "IN10" << "IN11" << "IN14" << "IN15" << "IN16" << "IN17" <<"IN18" <<"IN19");
               // Create the second QComboBox and add it as an item to the first combo box


               ChannelComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
               // Set the minimum width to 100 pixels
               ChannelComboBox->setMinimumWidth(10);
               ChannelLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ChannelComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


               layout->addRow(ChannelLabel, ChannelComboBox);

               // ----------------------- Save Channel Choices configs into a ADCConfig.txt-----------------------------------//


               QString ChannelConfig = settings.value("Channel", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexChannel = ChannelComboBox->findText(ChannelConfig);
               if (indexChannel != -1)
                   ChannelComboBox->setCurrentIndex(indexChannel);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Channel; // declare stopBits outside of the lambda

               connect(ChannelComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Channel](int indexChannel){
                   // Retrieve the selected option
                   QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                   QString Channel = ChannelComboBox->itemText(indexChannel);
                   settings.beginGroup("ADC1Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Channel", Channel);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ChannelConfig = settings.value("Channel" , Channel).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Channel;
                   qDebug() << "Channel:" << ChannelConfig;
               });

               // ----------------------Create Resolution Mode----------------------//

               QLabel* ResolutionLabel = new QLabel(tr("ADC Resolution Bit"), this);
               QComboBox* ResolutionComboBox = new QComboBox(this);
               ResolutionComboBox->addItems(QStringList() << "ADC 8-Bit Resolution" << "ADC 10-Bit Resolution" << "ADC 12-Bit Resolution" << "ADC 14-Bit Resolution" << "ADC 16-Bit Resolution"<< "ADC 12-Bit Optimized Resolution" << "ADC 14-Bit Optimized Resolution"  );
               ResolutionLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ResolutionComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(ResolutionLabel, ResolutionComboBox);


               // ----------------------- Save Resolution Choices configs into a ADCConfig.txt-----------------------------------//


               QString ResolutionConfig = settings.value("Resolution", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexResolution = ResolutionComboBox->findText(ResolutionConfig);
               if (indexResolution != -1)
                   ResolutionComboBox->setCurrentIndex(indexResolution);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Resolution; // declare stopBits outside of the lambda

               connect(ResolutionComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Resolution](int indexResolution){
                   // Retrieve the selected option
                   QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                   QString Resolution = ResolutionComboBox->itemText(indexResolution);
                   settings.beginGroup("ADC1Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Resolution", Resolution);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ResolutionConfig = settings.value("Resolution" , Resolution).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Resolution;
                   qDebug() << "Resolution:" << ResolutionConfig;
               });



               // ----------------------Create Scan Mode----------------------//

               QLabel* ScanLabel = new QLabel(tr("Scan Conversion Mode"), this);
               QComboBox* ScanComboBox = new QComboBox(this);
               ScanComboBox->addItems(QStringList() << "Disabled" );
               ScanLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ScanComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(ScanLabel, ScanComboBox);

               // ----------------------- Save Scan Mode Choices configs into a ADCConfig.txt-----------------------------------//


               QString ScanConfig = settings.value("Scan", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexScan = ScanComboBox->findText(ScanConfig);
               if (indexScan != -1)
                   ScanComboBox->setCurrentIndex(indexScan);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Scan; // declare stopBits outside of the lambda

               connect(ScanComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Scan](int indexScan){
                   // Retrieve the selected option
                   QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                   QString Scan = ScanComboBox->itemText(indexScan);
                   settings.beginGroup("ADC1Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Scan", Scan);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ScanConfig = settings.value("Scan" , Scan).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Scan;
                   qDebug() << "Scan:" << ScanConfig;
               });



               // ----------------------Create continuous Mode----------------------//

               QLabel* ContinuousLabel = new QLabel(tr("Continuous Conversion Mode"), this);
               QComboBox* ContinuousComboBox = new QComboBox(this);


               ContinuousComboBox->addItems(QStringList() << "Enabled" << "Disabled");

               ContinuousLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ContinuousComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
               layout->addRow(ContinuousLabel, ContinuousComboBox);

               // ----------------------- Save Continuous Mode Choices configs into a ADCConfig.txt-----------------------------------//


               QString ContinuousConfig = settings.value("Continuous", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexContinuous = ContinuousComboBox->findText(ContinuousConfig);
               if (indexContinuous != -1)
                   ContinuousComboBox->setCurrentIndex(indexContinuous);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Continuous; // declare stopBits outside of the lambda

               connect(ContinuousComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Continuous](int indexContinuous){
                   // Retrieve the selected option
                   QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                   QString Continuous = ContinuousComboBox->itemText(indexContinuous);
                   settings.beginGroup("ADC1Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Continuous", Continuous);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ContinuousConfig = settings.value("Continuous" , Continuous).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Continuous;
                   qDebug() << "Continuous:" << ContinuousConfig;
               });


               // ----------------------Create Discontinuous Mode----------------------//

              QLabel* DiscontinuousLabel = new QLabel(tr("Discontinuous Conversion Mode"), this);
              QComboBox* DiscontinuousComboBox = new QComboBox(this);


              DiscontinuousComboBox->addItems(QStringList() << "Enabled" << "Disabled");

              DiscontinuousLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
              DiscontinuousComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


              // ----------------------- Save Discontinuous Mode Choices configs into a ADCConfig.txt-----------------------------------//


              QString DiscontinuousConfig = settings.value("Discontinuous", "").toString();
//                QString stopBitsConfig;
              // Set the selected option in the combo box

              int indexDiscontinuous = DiscontinuousComboBox->findText(DiscontinuousConfig);
              if (indexDiscontinuous != -1)
                  DiscontinuousComboBox->setCurrentIndex(indexDiscontinuous);

              // Connect the combo box to the slot
   //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
              QString Discontinuous; // declare stopBits outside of the lambda

              connect(DiscontinuousComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Discontinuous](int indexDiscontinuous){
                  // Retrieve the selected option
                  QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                  QString Discontinuous = DiscontinuousComboBox->itemText(indexDiscontinuous);
                  settings.beginGroup("ADC1Configs");


                  // Store the selected option in the settings file
                  settings.setValue("Discontinuous", Discontinuous);
                  settings.endGroup();

                  // Retrieve the stored value and print to the console
                  QString DiscontinuousConfig = settings.value("Discontinuous" , Discontinuous).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                  qDebug() << "selected option:" << Discontinuous;
                  qDebug() << "Discontinuous:" << DiscontinuousConfig;
              });

              layout->addRow(DiscontinuousLabel, DiscontinuousComboBox);


              // ----------------------Create End of Conversion Mode----------------------//

             QLabel* EndConversionLabel = new QLabel(tr("End of Conversion Mode"), this);
             QComboBox* EndConversionComboBox = new QComboBox(this);


             EndConversionComboBox->addItems(QStringList() << "End of Single Conversion" << "End of sequence Conversion");

             EndConversionLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
             EndConversionComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
             layout->addRow(EndConversionLabel, EndConversionComboBox);


             // ----------------------- Save End of Conversion Choices configs into a ADCConfig.txt-----------------------------------//


             QString EndConversionConfig = settings.value("EndConversion", "").toString();
//                QString stopBitsConfig;
             // Set the selected option in the combo box

             int indexEndConversion = EndConversionComboBox->findText(EndConversionConfig);
             if (indexEndConversion != -1)
                 EndConversionComboBox->setCurrentIndex(indexEndConversion);

             // Connect the combo box to the slot
  //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
             QString EndConversion; // declare stopBits outside of the lambda

             connect(EndConversionComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&EndConversion](int indexEndConversion){
                 // Retrieve the selected option
                 QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                 QString EndConversion = EndConversionComboBox->itemText(indexEndConversion);
                 settings.beginGroup("ADC1Configs");


                 // Store the selected option in the settings file
                 settings.setValue("EndConversion", EndConversion);
                 settings.endGroup();

                 // Retrieve the stored value and print to the console
                 QString EndConversionConfig = settings.value("EndConversion" , EndConversion).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                 qDebug() << "selected option:" << EndConversion;
                 qDebug() << "EndConversion:" << EndConversionConfig;
             });


             // ----------------------Create Behavior Bit----------------------//

            QLabel* BehaviorLabel = new QLabel(tr("Overrun Behavior"), this);
            QComboBox* BehaviorComboBox = new QComboBox(this);


            BehaviorComboBox->addItems(QStringList() << "Overrun Data Preserved" << "Overrun Data Overwritten");

            BehaviorLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
            BehaviorComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
            layout->addRow(BehaviorLabel, BehaviorComboBox);


            // ----------------------- Save Behavior Bit Choices configs into a ADCConfig.txt-----------------------------------//


            QString BehaviorConfig = settings.value("Behavior", "").toString();
//                QString stopBitsConfig;
            // Set the selected option in the combo box

            int indexBehavior = BehaviorComboBox->findText(BehaviorConfig);
            if (indexBehavior != -1)
                BehaviorComboBox->setCurrentIndex(indexBehavior);

            // Connect the combo box to the slot
 //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
            QString Behavior; // declare stopBits outside of the lambda

            connect(BehaviorComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Behavior](int indexBehavior){
                // Retrieve the selected option
                QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                QString Behavior = BehaviorComboBox->itemText(indexBehavior);
                settings.beginGroup("ADC1Configs");


                // Store the selected option in the settings file
                settings.setValue("Behavior", Behavior);
                settings.endGroup();

                // Retrieve the stored value and print to the console
                QString BehaviorConfig = settings.value("Behavior" , Behavior).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                qDebug() << "selected option:" << Behavior;
                qDebug() << "Behavior:" << BehaviorConfig;
            });



            // ----------------------Create Left Bit----------------------//

               QLabel* LeftBitLabel = new QLabel(tr("Left Bit Shift"), this);
               QComboBox* LeftBitComboBox = new QComboBox(this);
               LeftBitComboBox->addItems(QStringList() << "No Bit Shift" << "1 Bit Shift" << "2 Bit Shift"<<  "3 Bit Shift" << "4 Bit Shift" <<"5 Bit Shift" << "6 Bit Shift" <<"7 Bit Shift" <<"8 Bit Shift" <<"9 Bit Shift" <<"10 Bit Shift" <<"11 Bit Shift" << "12 Bit Shift" <<"13 Bit Shift" <<"14 Bit Shift" << "15 Bit Shift" );
               LeftBitLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               LeftBitComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               // ----------------------- Save Left Bit Choices configs into a ADCConfig.txt-----------------------------------//


               QString LeftBitConfig = settings.value("LeftBit", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexLeftBit = LeftBitComboBox->findText(LeftBitConfig);
               if (indexLeftBit != -1)
                   LeftBitComboBox->setCurrentIndex(indexLeftBit);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString LeftBit; // declare stopBits outside of the lambda

               connect(LeftBitComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&LeftBit](int indexLeftBit){
                   // Retrieve the selected option
                   QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                   QString LeftBit = LeftBitComboBox->itemText(indexLeftBit);
                   settings.beginGroup("ADC1Configs");


                   // Store the selected option in the settings file
                   settings.setValue("LeftBit", LeftBit);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString LeftBitConfig = settings.value("LeftBit" , LeftBit).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << LeftBit;
                   qDebug() << "LeftBit:" << LeftBitConfig;
               });

               layout->addRow(LeftBitLabel, LeftBitComboBox);
               layout->setContentsMargins(0, 0, 0, 0);
               layout->setSpacing(30);

               // Create the vertical layout and add the form layout to it
               QVBoxLayout* verticalLayout = new QVBoxLayout(this);
               verticalLayout->addStretch();
               verticalLayout->addLayout(layout);
               verticalLayout->addStretch();

               // Create the horizontal layout and add the vertical layout to it
               QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
               horizontalLayout->addStretch();
               horizontalLayout->addLayout(verticalLayout);
               horizontalLayout->addStretch();

               // Set the widget layout to the horizontal layout

               widget->setLayout(horizontalLayout);
               widget->setGeometry(500, 500, 600, 500);


               QSettings settings("ADCConfig.txt", QSettings::IniFormat);

               qDebug() << "Settings file path: " << settings.fileName();



               settings.beginGroup("ADC1Configs");

               settings.setValue("Channel",  Channel);
               settings.setValue("Resolution",  Resolution);
               settings.setValue("Scan",  ScanComboBox->currentText());
               settings.setValue("Continuous",  Continuous);
               settings.setValue("Discontinuous",  Discontinuous);
               settings.setValue("EndConversion",  EndConversion);
               settings.setValue("Behavior",  Behavior);
               settings.setValue("LeftBit",  LeftBit);


               settings.endGroup();





    }

    void ADC3Config (){
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

                // Create Layout form for ADC
                QFormLayout* layout = new QFormLayout(this);

                // Create a QLabel for "DAC configurations" and center it horizontally
                QLabel* titleLabel = new QLabel("ADC3 configurations", this);

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



                // ----------------------Create Channel Choices----------------------//

               QLabel* ChannelLabel = new QLabel(tr("Select Channel"), this);
               QComboBox* ChannelComboBox = new QComboBox(this);

               ChannelComboBox->addItems(QStringList() << "IN2" << "IN3" << "IN4" <<"IN5" << "IN6" << "IN7" << "IN8" << "IN9" << "IN10" << "IN11" << "IN14" << "IN15" << "IN16" << "IN17" <<"IN18" <<"IN19");
               // Create the second QComboBox and add it as an item to the first combo box


               ChannelComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
               // Set the minimum width to 100 pixels
               ChannelComboBox->setMinimumWidth(10);
               ChannelLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ChannelComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


               layout->addRow(ChannelLabel, ChannelComboBox);


               // ----------------------- Save Channel Choices configs into a ADCConfig.txt-----------------------------------//


               QString ChannelConfig = settings.value("Channel", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexChannel = ChannelComboBox->findText(ChannelConfig);
               if (indexChannel != -1)
                   ChannelComboBox->setCurrentIndex(indexChannel);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Channel; // declare stopBits outside of the lambda

               connect(ChannelComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Channel](int indexChannel){
                   // Retrieve the selected option
                   QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                   QString Channel = ChannelComboBox->itemText(indexChannel);
                   settings.beginGroup("ADC3Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Channel", Channel);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ChannelConfig = settings.value("Channel" , Channel).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Channel;
                   qDebug() << "Channel:" << ChannelConfig;
               });


               // ----------------------Create Resolution Mode----------------------//

               QLabel* ResolutionLabel = new QLabel(tr("ADC Resolution Bit"), this);
               QComboBox* ResolutionComboBox = new QComboBox(this);
               ResolutionComboBox->addItems(QStringList() << "ADC 8-Bit Resolution" << "ADC 10-Bit Resolution" << "ADC 12-Bit Resolution" << "ADC 14-Bit Resolution" << "ADC 16-Bit Resolution"<< "ADC 12-Bit Optimized Resolution" << "ADC 14-Bit Optimized Resolution"  );
               ResolutionLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ResolutionComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(ResolutionLabel, ResolutionComboBox);

               // ----------------------- Save Resolution Choices configs into a ADCConfig.txt-----------------------------------//


               QString ResolutionConfig = settings.value("Resolution", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexResolution = ResolutionComboBox->findText(ResolutionConfig);
               if (indexResolution != -1)
                   ResolutionComboBox->setCurrentIndex(indexResolution);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Resolution; // declare stopBits outside of the lambda

               connect(ResolutionComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Resolution](int indexResolution){
                   // Retrieve the selected option
                   QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                   QString Resolution = ResolutionComboBox->itemText(indexResolution);
                   settings.beginGroup("ADC3Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Resolution", Resolution);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ResolutionConfig = settings.value("Resolution" , Resolution).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Resolution;
                   qDebug() << "Resolution:" << ResolutionConfig;
               });


               // ----------------------Create Scan Mode----------------------//

               QLabel* ScanLabel = new QLabel(tr("Scan Conversion Mode"), this);
               QComboBox* ScanComboBox = new QComboBox(this);
               ScanComboBox->addItems(QStringList() << "Disabled" );
               ScanLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ScanComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(ScanLabel, ScanComboBox);



               // ----------------------- Save Scan Mode Choices configs into a ADCConfig.txt-----------------------------------//


               QString ScanConfig = settings.value("Scan", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexScan = ScanComboBox->findText(ScanConfig);
               if (indexScan != -1)
                   ScanComboBox->setCurrentIndex(indexScan);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Scan; // declare stopBits outside of the lambda

               connect(ScanComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Scan](int indexScan){
                   // Retrieve the selected option
                   QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                   QString Scan = ScanComboBox->itemText(indexScan);
                   settings.beginGroup("ADC3Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Scan", Scan);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ScanConfig = settings.value("Scan" , Scan).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Scan;
                   qDebug() << "Scan:" << ScanConfig;
               });




               // ----------------------Create continuous Mode----------------------//

               QLabel* ContinuousLabel = new QLabel(tr("Continuous Conversion Mode"), this);
               QComboBox* ContinuousComboBox = new QComboBox(this);


               ContinuousComboBox->addItems(QStringList() << "Enabled" << "Disabled");

               ContinuousLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ContinuousComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
               layout->addRow(ContinuousLabel, ContinuousComboBox);


               // ----------------------- Save Continuous Mode Choices configs into a ADCConfig.txt-----------------------------------//


               QString ContinuousConfig = settings.value("Continuous", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexContinuous = ContinuousComboBox->findText(ContinuousConfig);
               if (indexContinuous != -1)
                   ContinuousComboBox->setCurrentIndex(indexContinuous);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString Continuous; // declare stopBits outside of the lambda

               connect(ContinuousComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Continuous](int indexContinuous){
                   // Retrieve the selected option
                   QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                   QString Continuous = ContinuousComboBox->itemText(indexContinuous);
                   settings.beginGroup("ADC3Configs");


                   // Store the selected option in the settings file
                   settings.setValue("Continuous", Continuous);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString ContinuousConfig = settings.value("Continuous" , Continuous).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << Continuous;
                   qDebug() << "Continuous:" << ContinuousConfig;
               });


               // ----------------------Create Discontinuous Mode----------------------//

              QLabel* DiscontinuousLabel = new QLabel(tr("Discontinuous Conversion Mode"), this);
              QComboBox* DiscontinuousComboBox = new QComboBox(this);


              DiscontinuousComboBox->addItems(QStringList() << "Enabled" << "Disabled");

              DiscontinuousLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
              DiscontinuousComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
              layout->addRow(DiscontinuousLabel, DiscontinuousComboBox);


              // ----------------------- Save Discontinuous Mode Choices configs into a ADCConfig.txt-----------------------------------//


              QString DiscontinuousConfig = settings.value("Discontinuous", "").toString();
//                QString stopBitsConfig;
              // Set the selected option in the combo box

              int indexDiscontinuous = DiscontinuousComboBox->findText(DiscontinuousConfig);
              if (indexDiscontinuous != -1)
                  DiscontinuousComboBox->setCurrentIndex(indexDiscontinuous);

              // Connect the combo box to the slot
   //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
              QString Discontinuous; // declare stopBits outside of the lambda

              connect(DiscontinuousComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Discontinuous](int indexDiscontinuous){
                  // Retrieve the selected option
                  QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                  QString Discontinuous = DiscontinuousComboBox->itemText(indexDiscontinuous);
                  settings.beginGroup("ADC3Configs");


                  // Store the selected option in the settings file
                  settings.setValue("Discontinuous", Discontinuous);
                  settings.endGroup();

                  // Retrieve the stored value and print to the console
                  QString DiscontinuousConfig = settings.value("Discontinuous" , Discontinuous).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                  qDebug() << "selected option:" << Discontinuous;
                  qDebug() << "Discontinuous:" << DiscontinuousConfig;
              });




              // ----------------------Create End of Conversion Mode----------------------//

             QLabel* EndConversionLabel = new QLabel(tr("End of Conversion Mode"), this);
             QComboBox* EndConversionComboBox = new QComboBox(this);


             EndConversionComboBox->addItems(QStringList() << "End of Single Conversion" << "End of sequence Conversion");

             EndConversionLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
             EndConversionComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
             layout->addRow(EndConversionLabel, EndConversionComboBox);


             // ----------------------- Save End of Conversion Choices configs into a ADCConfig.txt-----------------------------------//


             QString EndConversionConfig = settings.value("EndConversion", "").toString();
//                QString stopBitsConfig;
             // Set the selected option in the combo box

             int indexEndConversion = EndConversionComboBox->findText(EndConversionConfig);
             if (indexEndConversion != -1)
                 EndConversionComboBox->setCurrentIndex(indexEndConversion);

             // Connect the combo box to the slot
  //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
             QString EndConversion; // declare stopBits outside of the lambda

             connect(EndConversionComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&EndConversion](int indexEndConversion){
                 // Retrieve the selected option
                 QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                 QString EndConversion = EndConversionComboBox->itemText(indexEndConversion);
                 settings.beginGroup("ADC3Configs");


                 // Store the selected option in the settings file
                 settings.setValue("EndConversion", EndConversion);
                 settings.endGroup();

                 // Retrieve the stored value and print to the console
                 QString EndConversionConfig = settings.value("EndConversion" , EndConversion).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                 qDebug() << "selected option:" << EndConversion;
                 qDebug() << "EndConversion:" << EndConversionConfig;
             });


             // ----------------------Create Behavior Bit----------------------//

            QLabel* BehaviorLabel = new QLabel(tr("Overrun Behavior"), this);
            QComboBox* BehaviorComboBox = new QComboBox(this);


            BehaviorComboBox->addItems(QStringList() << "Overrun Data Preserved" << "Overrun Data Overwritten");

            BehaviorLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
            BehaviorComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
            layout->addRow(BehaviorLabel, BehaviorComboBox);


            // ----------------------- Save Behavior Bit Choices configs into a ADCConfig.txt-----------------------------------//


            QString BehaviorConfig = settings.value("Behavior", "").toString();
//                QString stopBitsConfig;
            // Set the selected option in the combo box

            int indexBehavior = BehaviorComboBox->findText(BehaviorConfig);
            if (indexBehavior != -1)
                BehaviorComboBox->setCurrentIndex(indexBehavior);

            // Connect the combo box to the slot
 //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
            QString Behavior; // declare stopBits outside of the lambda

            connect(BehaviorComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Behavior](int indexBehavior){
                // Retrieve the selected option
                QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                QString Behavior = BehaviorComboBox->itemText(indexBehavior);
                settings.beginGroup("ADC3Configs");


                // Store the selected option in the settings file
                settings.setValue("Behavior", Behavior);
                settings.endGroup();

                // Retrieve the stored value and print to the console
                QString BehaviorConfig = settings.value("Behavior" , Behavior).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                qDebug() << "selected option:" << Behavior;
                qDebug() << "Behavior:" << BehaviorConfig;
            });




            // ----------------------Create Left Bit----------------------//

               QLabel* LeftBitLabel = new QLabel(tr("Left Bit Shift"), this);
               QComboBox* LeftBitComboBox = new QComboBox(this);
               LeftBitComboBox->addItems(QStringList() << "No Bit Shift" << "1 Bit Shift" << "2 Bit Shift"<<  "3 Bit Shift" << "4 Bit Shift" <<"5 Bit Shift" << "6 Bit Shift" <<"7 Bit Shift" <<"8 Bit Shift" <<"9 Bit Shift" <<"10 Bit Shift" <<"11 Bit Shift" << "12 Bit Shift" <<"13 Bit Shift" <<"14 Bit Shift" << "15 Bit Shift" );
               LeftBitLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               LeftBitComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               // ----------------------- Save Left Bit Choices configs into a ADCConfig.txt-----------------------------------//


               QString LeftBitConfig = settings.value("LeftBit", "").toString();
//                QString stopBitsConfig;
               // Set the selected option in the combo box

               int indexLeftBit = LeftBitComboBox->findText(LeftBitConfig);
               if (indexLeftBit != -1)
                   LeftBitComboBox->setCurrentIndex(indexLeftBit);

               // Connect the combo box to the slot
    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
               QString LeftBit; // declare stopBits outside of the lambda

               connect(LeftBitComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&LeftBit](int indexLeftBit){
                   // Retrieve the selected option
                   QSettings settings("ADCConfig.txt", QSettings::IniFormat);

                   QString LeftBit = LeftBitComboBox->itemText(indexLeftBit);
                   settings.beginGroup("ADC3Configs");


                   // Store the selected option in the settings file
                   settings.setValue("LeftBit", LeftBit);
                   settings.endGroup();

                   // Retrieve the stored value and print to the console
                   QString LeftBitConfig = settings.value("LeftBit" , LeftBit).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

                   qDebug() << "selected option:" << LeftBit;
                   qDebug() << "LeftBit:" << LeftBitConfig;
               });

               layout->addRow(LeftBitLabel, LeftBitComboBox);
               layout->setContentsMargins(0, 0, 0, 0);
               layout->setSpacing(30);

               // Create the vertical layout and add the form layout to it
               QVBoxLayout* verticalLayout = new QVBoxLayout(this);
               verticalLayout->addStretch();
               verticalLayout->addLayout(layout);
               verticalLayout->addStretch();

               // Create the horizontal layout and add the vertical layout to it
               QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
               horizontalLayout->addStretch();
               horizontalLayout->addLayout(verticalLayout);
               horizontalLayout->addStretch();

               // Set the widget layout to the horizontal layout

               widget->setLayout(horizontalLayout);
               widget->setGeometry(500, 500, 600, 500);

               QSettings settings("ADCConfig.txt", QSettings::IniFormat);

               qDebug() << "Settings file path: " << settings.fileName();



               settings.beginGroup("ADC3Configs");

               settings.setValue("Channel",  Channel);
               settings.setValue("Resolution",  Resolution);
               settings.setValue("Scan",  ScanComboBox->currentText());
               settings.setValue("Continuous",  Continuous);
               settings.setValue("Discontinuous",  Discontinuous);
               settings.setValue("EndConversion",  EndConversion);
               settings.setValue("Behavior",  Behavior);
               settings.setValue("LeftBit",  LeftBit);


               settings.endGroup();





    }
    void DACConfig (){
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

        // Create Layout form for DAC
        QFormLayout* layout = new QFormLayout(this);



        // Create a QLabel for "DAC configurations" and center it horizontally
        QLabel* titleLabel = new QLabel("DAC configurations", this);

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





        // -----------------OUT1 Connected to-----------------//

        QLabel* ChannelLabel = new QLabel(tr("OUT1 Connected to "), this);
        QComboBox* ChannelComboBox = new QComboBox(this);
        ChannelComboBox->addItems(QStringList() << "Disable" << "Only External Pin" << "Only on Chip Analog Peripherals" <<"Both external Pin and on Chip Analog" );
        ChannelLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        ChannelComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
        layout->addRow(ChannelLabel, ChannelComboBox);


        // ----------------------- Save Resolution Choices configs into a ADCConfig.txt-----------------------------------//


        QString ChannelConfig = settings.value("Channel", "").toString();
//                QString stopBitsConfig;
        // Set the selected option in the combo box

        int indexChannel = ChannelComboBox->findText(ChannelConfig);
        if (indexChannel != -1)
            ChannelComboBox->setCurrentIndex(indexChannel);

        // Connect the combo box to the slot
//           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
        QString Channel; // declare stopBits outside of the lambda

        connect(ChannelComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Channel](int indexChannel){
            // Retrieve the selected option
            QSettings settings("DACConfig.txt", QSettings::IniFormat);

            QString Channel = ChannelComboBox->itemText(indexChannel);
            settings.beginGroup("DAC1Configs");


            // Store the selected option in the settings file
            settings.setValue("Channel", Channel);
            settings.endGroup();

            // Retrieve the stored value and print to the console
            QString ChannelConfig = settings.value("Channel" , Channel).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

            qDebug() << "selected option:" << Channel;
            qDebug() << "Channel:" << ChannelConfig;
        });


        // --------------OUT2 Connected to--------------------//

        QLabel* Channel2Label = new QLabel(tr("OUT2 Connected to "), this);
        QComboBox* Channel2ComboBox = new QComboBox(this);
        Channel2ComboBox->addItems(QStringList() << "Disable" << "Only External Pin" << "Only on Chip Analog Peripherals" <<"Both external Pin and on Chip Analog" );
        Channel2Label->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        Channel2ComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
        layout->addRow(Channel2Label, Channel2ComboBox);

        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);



        // ----------------------- Save Resolution Choices configs into a ADCConfig.txt-----------------------------------//


        QString Channel2Config = settings.value("Channel2", "").toString();
//                QString stopBitsConfig;
        // Set the selected option in the combo box

        int indexChannel2 = Channel2ComboBox->findText(Channel2Config);
        if (indexChannel2 != -1)
            Channel2ComboBox->setCurrentIndex(indexChannel2);

        // Connect the combo box to the slot
//           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
        QString Channel2; // declare stopBits outside of the lambda

        connect(Channel2ComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Channel2](int indexChannel2){
            // Retrieve the selected option
            QSettings settings("DACConfig.txt", QSettings::IniFormat);

            QString Channel2 = Channel2ComboBox->itemText(indexChannel2);
            settings.beginGroup("DAC2Configs");


            // Store the selected option in the settings file
            settings.setValue("Channel2", Channel2);
            settings.endGroup();

            // Retrieve the stored value and print to the console
            QString Channel2Config = settings.value("Channel2" , Channel2).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

            qDebug() << "selected option:" << Channel2;
            qDebug() << "Channel2:" << Channel2Config;
        });



        // --------------Connection between two widgets Channel1 & Channel2--------------------//

        connect(ChannelComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &Dashboard::ShowingDAC1Configs);
        connect(Channel2ComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &Dashboard::ShowingDAC2Configs);


        // Create the vertical layout and add the form layout to it
        QVBoxLayout* verticalLayout = new QVBoxLayout(this);
//        verticalLayout->addWidget(titleLabel);
        verticalLayout->addStretch();
        verticalLayout->addLayout(layout);
        verticalLayout->addStretch();

        // Create the horizontal layout and add the vertical layout to it
        QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
        horizontalLayout->addStretch();
        horizontalLayout->addLayout(verticalLayout);
        horizontalLayout->addStretch();

        // Set the widget layout to the horizontal layout
        widget->setLayout(horizontalLayout);
        widget->setGeometry(500, 500, 600, 500);

        // Saving DAC Configs into a file
        QSettings settings("file.txt", QSettings::IniFormat);
        settings.beginGroup("DACConfigs");
        settings.setValue("Channel",  ChannelComboBox->currentText());
        settings.setValue("Channel2",  Channel2ComboBox->currentText());
        settings.endGroup();
    }



    // Layout Form the DAC Configuration

    void ShowingDAC1Configs(){

        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);


        QFormLayout* layout = new QFormLayout(this);
        // Create a QLabel for "DAC configurations" and center it horizontally
        QLabel* titleLabel = new QLabel("DAC Showing configurations", this);

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

        // --------------Mode selected for the OUT1--------------------//

        QLabel* ModeLabel = new QLabel(tr("Mode selected"), this);
        QComboBox* ModeComboBox = new QComboBox(this);

        ModeComboBox->addItems(QStringList() << "Normal Mode" << "Sample and Hold Mode" );


        ModeLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        ModeComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(ModeLabel, ModeComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);


        // ----------------------- Save Resolution Choices configs into a ADCConfig.txt-----------------------------------//


        QString ModeConfig = settings.value("Mode", "").toString();
//                QString stopBitsConfig;
        // Set the selected option in the combo box

        int indexMode = ModeComboBox->findText(ModeConfig);
        if (indexMode != -1)
            ModeComboBox->setCurrentIndex(indexMode);

        // Connect the combo box to the slot
//           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
        QString Mode; // declare stopBits outside of the lambda

        connect(ModeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Mode](int indexMode){
            // Retrieve the selected option
            QSettings settings("DACConfig.txt", QSettings::IniFormat);

            QString Mode = ModeComboBox->itemText(indexMode);
            settings.beginGroup("DAC1Configs");


            // Store the selected option in the settings file
            settings.setValue("Mode", Mode);
            settings.endGroup();

            // Retrieve the stored value and print to the console
            QString ModeConfig = settings.value("Mode" , Mode).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

            qDebug() << "selected option:" << Mode;
            qDebug() << "Mode:" << ModeConfig;
        });


        // --------------Output Buffer for the OUT1--------------------//

        QLabel* BufferLabel = new QLabel(tr(" Output Buffer "), this);
        QComboBox* BufferComboBox = new QComboBox(this);

        BufferComboBox->addItems(QStringList() << "Enable" << "Disable" );


        BufferLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        BufferComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(BufferLabel, BufferComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);



        // ----------------------- Save Resolution Choices configs into a ADCConfig.txt-----------------------------------//


        QString BufferConfig = settings.value("Buffer", "").toString();
//                QString stopBitsConfig;
        // Set the selected option in the combo box

        int indexBuffer = BufferComboBox->findText(BufferConfig);
        if (indexBuffer != -1)
            BufferComboBox->setCurrentIndex(indexBuffer);

        // Connect the combo box to the slot
//           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
        QString Buffer; // declare stopBits outside of the lambda

        connect(BufferComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Buffer](int indexBuffer){
            // Retrieve the selected option
            QSettings settings("DACConfig.txt", QSettings::IniFormat);

            QString Buffer = BufferComboBox->itemText(indexBuffer);
            settings.beginGroup("DAC1Configs");


            // Store the selected option in the settings file
            settings.setValue("Buffer", Buffer);
            settings.endGroup();

            // Retrieve the stored value and print to the console
            QString BufferConfig = settings.value("Buffer" , Buffer).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

            qDebug() << "selected option:" << Buffer;
            qDebug() << "Buffer:" << BufferConfig;
        });



        // --------------Trigger for the OUT1--------------------//

        QLabel* TriggerLabel = new QLabel(tr("Trigger"), this);
        QComboBox* TriggerComboBox = new QComboBox(this);

        TriggerComboBox->addItems(QStringList() << "None" << "TIMER1 Trigger OUT event " << "TIMER1 Trigger OUT event " << "TIMER1 Trigger OUT event " << "TIMER2 Trigger OUT event " << "TIMER4 Trigger OUT event " << "TIMER5 Trigger OUT event " << "TIMER6 Trigger OUT event " << "TIMER7 Trigger OUT event " << "TIMER8 Trigger OUT event " << "TIMER15 Trigger OUT event" << "LPTIMER1 Trigger OUT event" << "LPTIMER2 Trigger OUT event" << "Software Trigger");


        TriggerLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        TriggerComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(TriggerLabel, TriggerComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);


        // ----------------------- Save Resolution Choices configs into a ADCConfig.txt-----------------------------------//


        QString TriggerConfig = settings.value("Trigger", "").toString();
//                QString stopBitsConfig;
        // Set the selected option in the combo box

        int indexTrigger = TriggerComboBox->findText(TriggerConfig);
        if (indexTrigger != -1)
            TriggerComboBox->setCurrentIndex(indexTrigger);

        // Connect the combo box to the slot
//           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
        QString Trigger; // declare stopBits outside of the lambda

        connect(TriggerComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Trigger](int indexTrigger){
            // Retrieve the selected option
            QSettings settings("DACConfig.txt", QSettings::IniFormat);

            QString Trigger = TriggerComboBox->itemText(indexTrigger);
            settings.beginGroup("DAC1Configs");


            // Store the selected option in the settings file
            settings.setValue("Trigger", Trigger);
            settings.endGroup();

            // Retrieve the stored value and print to the console
            QString TriggerConfig = settings.value("Trigger" , Trigger).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

            qDebug() << "selected option:" << Trigger;
            qDebug() << "Trigger:" << TriggerConfig;
        });



        // --------------Trimming for the OUT1--------------------//

        QLabel* TrimmingLabel = new QLabel(tr(" Trimming "), this);
        QComboBox* TrimmingComboBox = new QComboBox(this);

        TrimmingComboBox->addItems(QStringList() << "Factory Trimming" << "User Trimming" );


        TrimmingLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        TrimmingComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(TrimmingLabel, TrimmingComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);



        // ----------------------- Save Resolution Choices configs into a ADCConfig.txt-----------------------------------//


        QString TrimmingConfig = settings.value("Trimming", "").toString();
//                QString stopBitsConfig;
        // Set the selected option in the combo box

        int indexTrimming = TrimmingComboBox->findText(TrimmingConfig);
        if (indexTrimming != -1)
            TrimmingComboBox->setCurrentIndex(indexTrimming);

        // Connect the combo box to the slot
//           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
        QString Trimming; // declare stopBits outside of the lambda

        connect(TrimmingComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Trimming](int indexTrimming){
            // Retrieve the selected option
            QSettings settings("DACConfig.txt", QSettings::IniFormat);

            QString Trimming = TrimmingComboBox->itemText(indexTrimming);
            settings.beginGroup("DAC1Configs");


            // Store the selected option in the settings file
            settings.setValue("Trimming", Trimming);
            settings.endGroup();

            // Retrieve the stored value and print to the console
            QString TrimmingConfig = settings.value("Trimming" , Trimming).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

            qDebug() << "selected option:" << Trimming;
            qDebug() << "Trimming:" << TrimmingConfig;
        });



        // Create the vertical layout and add the form layout to it
        QVBoxLayout* verticalLayout = new QVBoxLayout(this);
        verticalLayout->addStretch();
        verticalLayout->addLayout(layout);
        verticalLayout->addStretch();

        // Create the horizontal layout and add the vertical layout to it
        QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
        horizontalLayout->addStretch();
        horizontalLayout->addLayout(verticalLayout);
        horizontalLayout->addStretch();

        // Set the widget layout to the horizontal layout

        widget->setLayout(horizontalLayout);
        widget->setGeometry(500, 500, 600, 500);

        QSettings settings("DACConfig.txt", QSettings::IniFormat);


        // DAC Configs
        settings.beginGroup("DAC1Configs");

        settings.setValue("Mode",  Mode);
        settings.setValue("Buffer",  Buffer);
        settings.setValue("Trigger",  Trigger);
        settings.setValue("Trimming",  Trimming);




        settings.endGroup();



    }

    void ShowingDAC2Configs(){

        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);


        QFormLayout* layout = new QFormLayout(this);
        // Create a QLabel for "DAC configurations" and center it horizontally
        QLabel* titleLabel = new QLabel("DAC Showing configurations", this);

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

        // --------------Mode selected for the OUT1--------------------//

        QLabel* ModeLabel = new QLabel(tr("Mode selected"), this);
        QComboBox* ModeComboBox = new QComboBox(this);

        ModeComboBox->addItems(QStringList() << "Normal Mode" << "Sample and Hold Mode" );


        ModeLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        ModeComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(ModeLabel, ModeComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);


        // ----------------------- Save Resolution Choices configs into a ADCConfig.txt-----------------------------------//


        QString ModeConfig = settings.value("Mode", "").toString();
//                QString stopBitsConfig;
        // Set the selected option in the combo box

        int indexMode = ModeComboBox->findText(ModeConfig);
        if (indexMode != -1)
            ModeComboBox->setCurrentIndex(indexMode);

        // Connect the combo box to the slot
//           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
        QString Mode; // declare stopBits outside of the lambda

        connect(ModeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Mode](int indexMode){
            // Retrieve the selected option
            QSettings settings("DACConfig.txt", QSettings::IniFormat);

            QString Mode = ModeComboBox->itemText(indexMode);
            settings.beginGroup("DAC2Configs");


            // Store the selected option in the settings file
            settings.setValue("Mode", Mode);
            settings.endGroup();

            // Retrieve the stored value and print to the console
            QString ModeConfig = settings.value("Mode" , Mode).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

            qDebug() << "selected option:" << Mode;
            qDebug() << "Mode:" << ModeConfig;
        });


        // --------------Output Buffer for the OUT1--------------------//

        QLabel* BufferLabel = new QLabel(tr(" Output Buffer "), this);
        QComboBox* BufferComboBox = new QComboBox(this);

        BufferComboBox->addItems(QStringList() << "Enable" << "Disable" );


        BufferLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        BufferComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(BufferLabel, BufferComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);



        // ----------------------- Save Resolution Choices configs into a ADCConfig.txt-----------------------------------//


        QString BufferConfig = settings.value("Buffer", "").toString();
//                QString stopBitsConfig;
        // Set the selected option in the combo box

        int indexBuffer = BufferComboBox->findText(BufferConfig);
        if (indexBuffer != -1)
            BufferComboBox->setCurrentIndex(indexBuffer);

        // Connect the combo box to the slot
//           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
        QString Buffer; // declare stopBits outside of the lambda

        connect(BufferComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Buffer](int indexBuffer){
            // Retrieve the selected option
            QSettings settings("DACConfig.txt", QSettings::IniFormat);

            QString Buffer = BufferComboBox->itemText(indexBuffer);
            settings.beginGroup("DAC2Configs");


            // Store the selected option in the settings file
            settings.setValue("Buffer", Buffer);
            settings.endGroup();

            // Retrieve the stored value and print to the console
            QString BufferConfig = settings.value("Buffer" , Buffer).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

            qDebug() << "selected option:" << Buffer;
            qDebug() << "Buffer:" << BufferConfig;
        });



        // --------------Trigger for the OUT1--------------------//

        QLabel* TriggerLabel = new QLabel(tr("Trigger"), this);
        QComboBox* TriggerComboBox = new QComboBox(this);

        TriggerComboBox->addItems(QStringList() << "None" << "TIMER1 Trigger OUT event " << "TIMER1 Trigger OUT event " << "TIMER1 Trigger OUT event " << "TIMER2 Trigger OUT event " << "TIMER4 Trigger OUT event " << "TIMER5 Trigger OUT event " << "TIMER6 Trigger OUT event " << "TIMER7 Trigger OUT event " << "TIMER8 Trigger OUT event " << "TIMER15 Trigger OUT event" << "LPTIMER1 Trigger OUT event" << "LPTIMER2 Trigger OUT event" << "Software Trigger");


        TriggerLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        TriggerComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(TriggerLabel, TriggerComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);


        // ----------------------- Save Resolution Choices configs into a ADCConfig.txt-----------------------------------//


        QString TriggerConfig = settings.value("Trigger", "").toString();
//                QString stopBitsConfig;
        // Set the selected option in the combo box

        int indexTrigger = TriggerComboBox->findText(TriggerConfig);
        if (indexTrigger != -1)
            TriggerComboBox->setCurrentIndex(indexTrigger);

        // Connect the combo box to the slot
//           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
        QString Trigger; // declare stopBits outside of the lambda

        connect(TriggerComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Trigger](int indexTrigger){
            // Retrieve the selected option
            QSettings settings("DACConfig.txt", QSettings::IniFormat);

            QString Trigger = TriggerComboBox->itemText(indexTrigger);
            settings.beginGroup("DAC2Configs");


            // Store the selected option in the settings file
            settings.setValue("Trigger", Trigger);
            settings.endGroup();

            // Retrieve the stored value and print to the console
            QString TriggerConfig = settings.value("Trigger" , Trigger).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

            qDebug() << "selected option:" << Trigger;
            qDebug() << "Trigger:" << TriggerConfig;
        });



        // --------------Trimming for the OUT1--------------------//

        QLabel* TrimmingLabel = new QLabel(tr(" Trimming "), this);
        QComboBox* TrimmingComboBox = new QComboBox(this);

        TrimmingComboBox->addItems(QStringList() << "Factory Trimming" << "User Trimming" );


        TrimmingLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        TrimmingComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(TrimmingLabel, TrimmingComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);



        // ----------------------- Save Resolution Choices configs into a ADCConfig.txt-----------------------------------//


        QString TrimmingConfig = settings.value("Trimming", "").toString();
//                QString stopBitsConfig;
        // Set the selected option in the combo box

        int indexTrimming = TrimmingComboBox->findText(TrimmingConfig);
        if (indexTrimming != -1)
            TrimmingComboBox->setCurrentIndex(indexTrimming);

        // Connect the combo box to the slot
//           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
        QString Trimming; // declare stopBits outside of the lambda

        connect(TrimmingComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Trimming](int indexTrimming){
            // Retrieve the selected option
            QSettings settings("DACConfig.txt", QSettings::IniFormat);

            QString Trimming = TrimmingComboBox->itemText(indexTrimming);
            settings.beginGroup("DAC2Configs");


            // Store the selected option in the settings file
            settings.setValue("Trimming", Trimming);
            settings.endGroup();

            // Retrieve the stored value and print to the console
            QString TrimmingConfig = settings.value("Trimming" , Trimming).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

            qDebug() << "selected option:" << Trimming;
            qDebug() << "Trimming:" << TrimmingConfig;
        });



        // Create the vertical layout and add the form layout to it
        QVBoxLayout* verticalLayout = new QVBoxLayout(this);
        verticalLayout->addStretch();
        verticalLayout->addLayout(layout);
        verticalLayout->addStretch();

        // Create the horizontal layout and add the vertical layout to it
        QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
        horizontalLayout->addStretch();
        horizontalLayout->addLayout(verticalLayout);
        horizontalLayout->addStretch();

        // Set the widget layout to the horizontal layout

        widget->setLayout(horizontalLayout);
        widget->setGeometry(500, 500, 600, 500);

        QSettings settings("DACConfig.txt", QSettings::IniFormat);


        // DAC Configs
        settings.beginGroup("DAC2Configs");

        settings.setValue("Mode",  Mode);
        settings.setValue("Buffer",  Buffer);
        settings.setValue("Trigger",  Trigger);
        settings.setValue("Trimming",  Trimming);




        settings.endGroup();



    }


    void GPIOOUPUTConfig(){

        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);


        QFormLayout* layout = new QFormLayout(this);

        // Create a QLabel for "DAC configurations" and center it horizontally
        QLabel* titleLabel = new QLabel("GPIO Output configurations", this);

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


        // --------------Select GPIO PIN--------------------//

        QLabel* PINLabel = new QLabel(tr("GPIO Output PIN "), this);
        QComboBox* PINComboBox = new QComboBox(this);

        PINComboBox->addItems(QStringList() << "PG4" << "PG5" << "PG6" << "PG7" << "PG10" << "PG11" << "PG12" << "PG13" );


        PINLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        PINComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(PINLabel, PINComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);



        // ----------------------- Save PIN Choices configs into a ADCConfig.txt-----------------------------------//


        QString PINConfig = settings.value("PIN", "").toString();
//                QString stopBitsConfig;
        // Set the selected option in the combo box

        int indexPIN = PINComboBox->findText(PINConfig);
        if (indexPIN != -1)
            PINComboBox->setCurrentIndex(indexPIN);

        // Connect the combo box to the slot
//           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
        QString PIN; // declare stopBits outside of the lambda

        connect(PINComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&PIN](int indexPIN){
            // Retrieve the selected option
            QSettings settings("GPIOConfig.txt", QSettings::IniFormat);

            QString PIN = PINComboBox->itemText(indexPIN);
            settings.beginGroup("GPIOOUTPUTConfigs");


            // Store the selected option in the settings file
            settings.setValue("PIN", PIN);
            settings.endGroup();

            // Retrieve the stored value and print to the console
            QString PINConfig = settings.value("PIN" , PIN).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

            qDebug() << "selected option:" << PIN;
            qDebug() << "PIN:" << PINConfig;
        });


        // --------------GPIO Mode selected for the OUT1--------------------//

        QLabel* ModeLabel = new QLabel(tr("GPIO Mode "), this);
        QComboBox* ModeComboBox = new QComboBox(this);

        ModeComboBox->addItems(QStringList() << "Push-Pull" << "Open-Drain" );


        ModeLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        ModeComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(ModeLabel, ModeComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);


        // ----------------------- Save Resolution Choices configs into a ADCConfig.txt-----------------------------------//


        QString ModeConfig = settings.value("Mode", "").toString();
//                QString stopBitsConfig;
        // Set the selected option in the combo box

        int indexMode = ModeComboBox->findText(ModeConfig);
        if (indexMode != -1)
            ModeComboBox->setCurrentIndex(indexMode);

        // Connect the combo box to the slot
//           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
        QString Mode; // declare stopBits outside of the lambda

        connect(ModeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Mode](int indexMode){
            // Retrieve the selected option
            QSettings settings("GPIOConfig.txt", QSettings::IniFormat);

            QString Mode = ModeComboBox->itemText(indexMode);
            settings.beginGroup("GPIOOUTPUTConfigs");


            // Store the selected option in the settings file
            settings.setValue("Mode", Mode);
            settings.endGroup();

            // Retrieve the stored value and print to the console
            QString ModeConfig = settings.value("Mode" , Mode).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

            qDebug() << "selected option:" << Mode;
            qDebug() << "Mode:" << ModeConfig;
        });


        // --------------GPIO PULL UP -- DOWN --------------------//

        QLabel* GPIOLabel = new QLabel(tr("GPIO Pull-up/Pull-down "), this);
        QComboBox* GPIOComboBox = new QComboBox(this);

        GPIOComboBox->addItems(QStringList() << "No Pull-up and No Pull-down" << "Pull-up" << "Pull-down" );


        GPIOLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        GPIOComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(GPIOLabel, GPIOComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);



        // ----------------------- Save Resolution Choices configs into a ADCConfig.txt-----------------------------------//


        QString GPIOConfig = settings.value("GPIO", "").toString();
//                QString stopBitsConfig;
        // Set the selected option in the combo box

        int indexGPIO = GPIOComboBox->findText(GPIOConfig);
        if (indexGPIO != -1)
            GPIOComboBox->setCurrentIndex(indexGPIO);

        // Connect the combo box to the slot
//           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
        QString GPIO; // declare stopBits outside of the lambda

        connect(GPIOComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&GPIO](int indexGPIO){
            // Retrieve the selected option
            QSettings settings("GPIOConfig.txt", QSettings::IniFormat);

            QString GPIO = GPIOComboBox->itemText(indexGPIO);
            settings.beginGroup("GPIOOUTPUTConfigs");


            // Store the selected option in the settings file
            settings.setValue("GPIO", GPIO);
            settings.endGroup();

            // Retrieve the stored value and print to the console
            QString GPIOConfig = settings.value("GPIO" , GPIO).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

            qDebug() << "selected option:" << GPIO;
            qDebug() << "GPIO:" << GPIOConfig;
        });




        // --------------Maximum Output Speed for the GPIO OUTPUT--------------------//

        QLabel* SpeedLabel = new QLabel(tr(" Maximum Output Speed "), this);
        QComboBox* SpeedComboBox = new QComboBox(this);

        SpeedComboBox->addItems(QStringList() << "Low" << "Meduim" << "High" << "Very High" );


        SpeedLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        SpeedComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(SpeedLabel, SpeedComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);



        // ----------------------- Save Resolution Choices configs into a ADCConfig.txt-----------------------------------//


        QString SpeedConfig = settings.value("Speed", "").toString();
//                QString stopBitsConfig;
        // Set the selected option in the combo box

        int indexSpeed = SpeedComboBox->findText(SpeedConfig);
        if (indexSpeed != -1)
            SpeedComboBox->setCurrentIndex(indexSpeed);

        // Connect the combo box to the slot
//           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
        QString Speed; // declare stopBits outside of the lambda

        connect(SpeedComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Speed](int indexSpeed){
            // Retrieve the selected option
            QSettings settings("GPIOConfig.txt", QSettings::IniFormat);

            QString Speed = SpeedComboBox->itemText(indexSpeed);
            settings.beginGroup("GPIOOUTPUTConfigs");


            // Store the selected option in the settings file
            settings.setValue("Speed", Speed);
            settings.endGroup();

            // Retrieve the stored value and print to the console
            QString SpeedConfig = settings.value("Speed" , Speed).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

            qDebug() << "selected option:" << Speed;
            qDebug() << "Speed:" << SpeedConfig;
        });




        // --------------User Label for the GPIO OUTPUT --------------------//

        QLabel* UserLabel = new QLabel(tr(" User Label "), this);
        QLineEdit* UserLineEdit = new QLineEdit(this);



        UserLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        UserLineEdit->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(UserLabel, UserLineEdit);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);


        // Create the vertical layout and add the form layout to it
        QVBoxLayout* verticalLayout = new QVBoxLayout(this);
        verticalLayout->addStretch();
        verticalLayout->addLayout(layout);
        verticalLayout->addStretch();

        // Create the horizontal layout and add the vertical layout to it
        QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
        horizontalLayout->addStretch();
        horizontalLayout->addLayout(verticalLayout);
        horizontalLayout->addStretch();

        // Set the widget layout to the horizontal layout

        widget->setLayout(horizontalLayout);
        widget->setGeometry(500, 500, 600, 500);


        QSettings settings("GPIOConfig.txt", QSettings::IniFormat);


        // GPIO OUTPUT Configs
        settings.beginGroup("GPIOOUTPUTConfigs");

        settings.setValue("PIN",  PIN);
        settings.setValue("Mode",  Mode);

        settings.setValue("GPIO",  GPIO);
        settings.setValue("Speed",  Speed);
        settings.setValue("UserLabel",  UserLineEdit->text());




        settings.endGroup();





    }

    void GPIOINPUTConfig(){

        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);


        QFormLayout* layout = new QFormLayout(this);
        // Create a QLabel for "DAC configurations" and center it horizontally
        QLabel* titleLabel = new QLabel("GPIO Input configurations", this);

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


        // --------------Select GPIO PIN--------------------//

        QLabel* PINLabel = new QLabel(tr("GPIO Input PIN "), this);
        QComboBox* PINComboBox = new QComboBox(this);

        PINComboBox->addItems(QStringList() << "PA6" << "PA7" << "PA8" << "PA9" << "PA10" << "PA11" << "PA12" << "PA13" );


        PINLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        PINComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(PINLabel, PINComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);


        // ----------------------- Save PIN Choices configs into a ADCConfig.txt-----------------------------------//


        QString PINConfig = settings.value("PIN", "").toString();
//                QString stopBitsConfig;
        // Set the selected option in the combo box

        int indexPIN = PINComboBox->findText(PINConfig);
        if (indexPIN != -1)
            PINComboBox->setCurrentIndex(indexPIN);

        // Connect the combo box to the slot
//           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
        QString PIN; // declare stopBits outside of the lambda

        connect(PINComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&PIN](int indexPIN){
            // Retrieve the selected option
            QSettings settings("GPIOConfig.txt", QSettings::IniFormat);

            QString PIN = PINComboBox->itemText(indexPIN);
            settings.beginGroup("GPIOINPUTConfigs");


            // Store the selected option in the settings file
            settings.setValue("PIN", PIN);
            settings.endGroup();

            // Retrieve the stored value and print to the console
            QString PINConfig = settings.value("PIN" , PIN).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

            qDebug() << "selected option:" << PIN;
            qDebug() << "PIN:" << PINConfig;
        });


        // --------------GPIO PULL UP -- DOWN --------------------//

        QLabel* GPIOLabel = new QLabel(tr("GPIO Pull-up/Pull-down "), this);
        QComboBox* GPIOComboBox = new QComboBox(this);

        GPIOComboBox->addItems(QStringList() << "No Pull-up and No Pull-down" << "Pull-up" << "Pull-down" );


        GPIOLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        GPIOComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(GPIOLabel, GPIOComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);


        // ----------------------- Save Resolution Choices configs into a ADCConfig.txt-----------------------------------//


        QString GPIOConfig = settings.value("GPIO", "").toString();
//                QString stopBitsConfig;
        // Set the selected option in the combo box

        int indexGPIO = GPIOComboBox->findText(GPIOConfig);
        if (indexGPIO != -1)
            GPIOComboBox->setCurrentIndex(indexGPIO);

        // Connect the combo box to the slot
//           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
        QString GPIO; // declare stopBits outside of the lambda

        connect(GPIOComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&GPIO](int indexGPIO){
            // Retrieve the selected option
            QSettings settings("GPIOConfig.txt", QSettings::IniFormat);

            QString GPIO = GPIOComboBox->itemText(indexGPIO);
            settings.beginGroup("GPIOINPUTConfigs");


            // Store the selected option in the settings file
            settings.setValue("GPIO", GPIO);
            settings.endGroup();

            // Retrieve the stored value and print to the console
            QString GPIOConfig = settings.value("GPIO" , GPIO).toString();
//                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

            qDebug() << "selected option:" << GPIO;
            qDebug() << "GPIO:" << GPIOConfig;
        });







        // --------------User Label for the GPIO OUTPUT --------------------//

        QLabel* UserLabel = new QLabel(tr(" User Label "), this);
        QLineEdit* UserLineEdit = new QLineEdit(this);



        UserLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        UserLineEdit->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(UserLabel, UserLineEdit);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);


        // Create the vertical layout and add the form layout to it
        QVBoxLayout* verticalLayout = new QVBoxLayout(this);
        verticalLayout->addStretch();
        verticalLayout->addLayout(layout);
        verticalLayout->addStretch();

        // Create the horizontal layout and add the vertical layout to it
        QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
        horizontalLayout->addStretch();
        horizontalLayout->addLayout(verticalLayout);
        horizontalLayout->addStretch();

        // Set the widget layout to the horizontal layout

        widget->setLayout(horizontalLayout);
        widget->setGeometry(500, 500, 600, 500);

        QSettings settings("GPIOConfig.txt", QSettings::IniFormat);


        // GPIO OUTPUT Configs
        settings.beginGroup("GPIOINPUTConfigs");

        settings.setValue("PIN",  PIN);

        settings.setValue("GPIO",  GPIO);
        settings.setValue("UserLabel",  UserLineEdit->text());




        settings.endGroup();

        settings.beginGroup("GPIOINTPUTConfigs");
        settings.remove("");
        settings.endGroup();





    }
    void FrequencyMesureConfig(){

        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);


        QFormLayout* layout = new QFormLayout(this);
        // Create a QLabel for "DAC configurations" and center it horizontally
        QLabel* titleLabel = new QLabel("Frequency Mesure configurations", this);

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


        // --------------Select Channel --------------------//

        QLabel* ChannelLabel = new QLabel(tr("Select Channel"), this);
        QComboBox* ChannelComboBox = new QComboBox(this);

        ChannelComboBox->addItems(QStringList() << "Channel1" << "Channel2" << "Channel3" << "Channel4");


        ChannelLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        ChannelComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(ChannelLabel, ChannelComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);

        // --------------Prescaler for Frequency Mesure--------------------//

        QLabel* PrescalerLabel = new QLabel(tr("Prescaler"), this);
        QSpinBox* PrescalerSpinBox = new QSpinBox(this);
        PrescalerSpinBox->setMinimum(0);
        PrescalerSpinBox->setMaximum(65535);




        PrescalerLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        PrescalerSpinBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(PrescalerLabel, PrescalerSpinBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);

        // --------------Counter Mode--------------------//

        QLabel* CounterLabel = new QLabel(tr("Counter Mode"), this);
        QComboBox* CounterComboBox = new QComboBox(this);

        CounterComboBox->addItems(QStringList() <<"Up" << "Down" );


        CounterLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        CounterComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(CounterLabel, CounterComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);


        // --------------Counter Periode === AutoReload--------------------//

        QLabel* AutoReloadLabel = new QLabel(tr("Counter Period (AutoReload) "), this);
        QSpinBox* AutoReloadSpinBox = new QSpinBox(this);
        AutoReloadSpinBox->setMinimum(0);
        AutoReloadSpinBox->setMaximum(65535);


        AutoReloadLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        AutoReloadSpinBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(AutoReloadLabel, AutoReloadSpinBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);


        // --------------Inetrnal Clock Division --------------------//

        QLabel* ClockLabel = new QLabel(tr("Internal Clock Division"), this);
        QComboBox* ClockComboBox = new QComboBox(this);

        ClockComboBox->addItems(QStringList() <<"No Division" << "Division by 2" << "Division by 4" );



        ClockLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        ClockComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(ClockLabel, ClockComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);



        // --------------Repitition Counter --------------------//

        QLabel* RepititionLabel = new QLabel(tr("Repitition Counter"), this);
        QSpinBox* RepititionSpinBox = new QSpinBox(this);
        RepititionSpinBox->setMinimum(0);
        RepititionSpinBox->setMaximum(65535);


        RepititionLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        RepititionSpinBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(RepititionLabel, RepititionSpinBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);


        // --------------Auto-Reload Preload --------------------//

        QLabel* PreloadLabel = new QLabel(tr("Auto-Reload Preload"), this);
        QComboBox* PreloadComboBox = new QComboBox(this);

        PreloadComboBox->addItems(QStringList() <<"Enable" << "Disable" );



        PreloadLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        PreloadComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(PreloadLabel, PreloadComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);



        // Create the vertical layout and add the form layout to it
        QVBoxLayout* verticalLayout = new QVBoxLayout(this);
        verticalLayout->addStretch();
        verticalLayout->addLayout(layout);
        verticalLayout->addStretch();

        // Create the horizontal layout and add the vertical layout to it
        QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
        horizontalLayout->addStretch();
        horizontalLayout->addLayout(verticalLayout);
        horizontalLayout->addStretch();

        // Set the widget layout to the horizontal layout

        widget->setLayout(horizontalLayout);
        widget->setGeometry(500, 500, 600, 500);


        QSettings settings("file.txt", QSettings::IniFormat);


        // GPIO OUTPUT Configs
        settings.beginGroup("FrequencyMesure");

        settings.setValue("Channel",  ChannelComboBox->currentText());
        settings.setValue("Prescaler",  PrescalerSpinBox->value());

        settings.setValue("CounterMode",  CounterComboBox->currentText());
        settings.setValue("CounterPeriod",  AutoReloadSpinBox->value());
        settings.setValue("InetrnalClock",  ClockComboBox->currentText());
        settings.setValue("RepititionCounter",  RepititionSpinBox->value());
        settings.setValue("Auto-Reload",  PreloadComboBox->currentText());






        settings.endGroup();




}
private:
    Ui::Dashboard *ui;
    QSerialPortInfo info;
    ConfigMode *ConfigScreen ;
    QToolButton *connectButton;
//         QList<QString> selectedUartOptions;
    static QStringList selectedUartOptionsStatic;
    static QStringList selectedI2COptionsStatic;
    static QStringList selectedSPIOptionsStatic;
    static QStringList selectedADCOptionsStatic;
    static QStringList selectedDACOptionsStatic;
    static QStringList selectedGPIOOptionsStatic;
    static QStringList selectedTIMEROptionsStatic;


public slots :
    void showConfigMode();
    void onUartOptionSelected();

       void onI2COptionSelected();
       void onSPIOptionSelected();
       void onADCOptionSelected();
       void onDACOptionSelected();
       void onGPIOOptionSelected();
       void onTIMEROptionSelected();



};

#endif // DASHBOARD_H
