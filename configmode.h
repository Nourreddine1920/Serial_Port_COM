#ifndef CONFIGMODE_H
#define CONFIGMODE_H

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
#include <QListWidget>

namespace Ui {
class ConfigMode;
}

class ConfigMode : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigMode(QWidget *parent = nullptr);
    ~ConfigMode();
    QSettings settings;

private:
    Ui::ConfigMode *ui;
    QSerialPortInfo info;


public slots :
    void returnDashboard();
    void UART4ShowingConfig(){
//        QWidget *widget = new QWidget(this);
//        setCentralWidget(widget);


//                // Create Layout form
//                QFormLayout* layout = new QFormLayout(this);

//                // Create a QLabel for "DAC configurations" and center it horizontally
//                QLabel* titleLabel = new QLabel("UART configurations", this);

//                // Load the icon image
//                QPixmap icon("C:/Users/nawledbr/Documents/Serial_Port_COM/config7.png");

//                // Create a QLabel for the icon and set its size
//                QLabel* iconLabel = new QLabel(this);
//                iconLabel->setPixmap(icon.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
//                iconLabel->setFixedSize(30, 30);

//                // Create a QHBoxLayout to hold the icon and the title label
//                QHBoxLayout* titleLayout = new QHBoxLayout();
//                titleLayout->addWidget(iconLabel);
//                titleLayout->addWidget(titleLabel);
//                titleLayout->setSpacing(10); // Set the spacing between the icon and the title label

//                // Set the font and style sheet for the title label
//                QFontDatabase fontDatabase;
//                QStringList fontFamilies = fontDatabase.families();

//                // Choose the first available font as the best font
//                QString bestFont = fontFamilies.first();

//                // Create a font object with the best font and size
//                QFont font(bestFont, 15);

//                // Set the font and style sheet for the label
//                titleLabel->setFont(font);
//                iconLabel->setFont(font);

//                titleLabel->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");
////                iconLabel->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");

//                titleLabel->setAlignment(Qt::AlignCenter);


//                // Add the title label and the icon to the main layout
//                layout->addRow(titleLayout);


//               // Create the baud rate label and combo box

//               QLabel* baudRateLabel = new QLabel(tr("Baud Rate"), this);
//               QComboBox* baudRateComboBox = new QComboBox(this);
////               baudRateComboBox->setStyleSheet("QComboBox {"
////                                       "background-color: white;"
////                                       "border: 1px solid gray;"
////                                       "border-radius: 3px;"
////                                       "padding: 1px 18px 1px 3px;"
////                                       "min-width: 6em;"
////                                       "}"
////                                       "QComboBox::drop-down {"
////                                       "subcontrol-origin: padding;"
////                                       "subcontrol-position: top right;"
////                                       "width: 15px;"
////                                       "border-left-width: 1px;"
////                                       "border-left-color: gray;"
////                                       "border-left-style: solid;"
////                                       "border-top-right-radius: 3px;"
////                                       "border-bottom-right-radius: 3px;"
////                                       "}"
////                                       "QComboBox::down-arrow {"
////                                       "image: url(:/images/down_arrow.png);"
////                                       "}"
////                                       "QComboBox QAbstractItemView {"
////                                       "background-color: white;"
////                                       "border: 1px solid gray;"
////                                       "selection-background-color: lightgray;"
////                                       "}"
////                                       );

//               QList<qint32> baudRates = info.standardBaudRates(); // What baudrates does my computer support ?
//               QList<QString> stringBaudRates;
//                for(int i = 0 ; i < baudRates.size() ; i++){
//                    stringBaudRates.append(QString::number(baudRates.at(i)));
//                }
//               baudRateComboBox->addItems(stringBaudRates);

//               baudRateComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
//               // Set the minimum width to 100 pixels
//               baudRateComboBox->setMinimumWidth(10);
//               baudRateLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
//               baudRateComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

//               layout->addRow(baudRateLabel, baudRateComboBox);



//               // ----------------------- Save Baudrate configs into a file.txt-----------------------------------//


//               QString BaudrateConfig = settings.value("Baudrate", "").toString();
////                QString stopBitsConfig;
//               // Set the selected option in the combo box

//               int indexBaudrate = baudRateComboBox->findText(BaudrateConfig);
//               if (indexBaudrate != -1)
//                   baudRateComboBox->setCurrentIndex(indexBaudrate);

//               // Connect the combo box to the slot
//    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
//               QString Baudrate; // declare stopBits outside of the lambda

//               connect(baudRateComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Baudrate](int indexBaudrate){
//                   // Retrieve the selected option
//                   QSettings settings("file.txt", QSettings::IniFormat);

//                   QString Baudrate = baudRateComboBox->itemText(indexBaudrate);
//                   settings.beginGroup("UARTConfigs");


//                   // Store the selected option in the settings file
//                   settings.setValue("Baudrate", Baudrate);
//                   settings.endGroup();

//                   // Retrieve the stored value and print to the console
//                   QString BaudrateConfig = settings.value("Baudrate" , Baudrate).toString();
////                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

//                   qDebug() << "selected option:" << Baudrate;
//                   qDebug() << "Baudrate:" << BaudrateConfig;
//               });


//               // Create the parity label and combo box

//               QLabel* parityLabel = new QLabel(tr("Parity"), this);
//               QComboBox* parityComboBox = new QComboBox(this);
//               parityComboBox->addItems(QStringList() << "None" << "Odd" << "Even");
//               parityLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
//               parityComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

//               layout->addRow(parityLabel, parityComboBox);


//               // ----------------------- Save Pqrity configs into a file.txt-----------------------------------//


//               QString ParityConfig = settings.value("Parity", "").toString();
////                QString stopBitsConfig;
//               // Set the selected option in the combo box

//               int indexParity = parityComboBox->findText(ParityConfig);
//               if (indexParity != -1)
//                   parityComboBox->setCurrentIndex(indexParity);

//               // Connect the combo box to the slot
//    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
//               QString Parity; // declare stopBits outside of the lambda

//               connect(parityComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&Parity](int indexParity){
//                   // Retrieve the selected option
//                   QSettings settings("file.txt", QSettings::IniFormat);

//                   QString Parity = parityComboBox->itemText(indexParity);
//                   settings.beginGroup("UARTConfigs");


//                   // Store the selected option in the settings file
//                   settings.setValue("Parity", Parity);
//                   settings.endGroup();

//                   // Retrieve the stored value and print to the console
//                   QString ParityConfig = settings.value("Parity" , Parity).toString();
////                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

//                   qDebug() << "selected option:" << Parity;
//                   qDebug() << "Parity:" << ParityConfig;
//               });





//               // Create the stop bits label and combo box

//               QLabel* stopBitsLabel = new QLabel(tr("Stop Bits"), this);
//               QComboBox* stopBitsComboBox = new QComboBox(this);
//               stopBitsComboBox->addItem("1 Bits");
//               stopBitsComboBox->addItem("1,5 Bits");
//               stopBitsComboBox->addItem("2 Bits");

//               stopBitsLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
//               stopBitsComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

//               layout->addRow(stopBitsLabel, stopBitsComboBox);


//               // Connect the combo box to the slot

//             //--------------------------- Save Stop Bits Configs into a file.txt -------------------------//

//               QString stopBitsConfig = settings.value("stopBits", "").toString();
//               // Set the selected option in the combo box

//               int index = stopBitsComboBox->findText(stopBitsConfig);
//               if (index != -1)
//                   stopBitsComboBox->setCurrentIndex(index);

//               QString stopBits; // declare stopBits outside of the lambda

//               // Connect the combo box to the slot

//               connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&stopBits](int index){
//                   // Retrieve the selected option
//                   QSettings settings("file.txt", QSettings::IniFormat);

//                   QString stopBits = stopBitsComboBox->itemText(index);
//                   settings.beginGroup("UARTConfigs");


//                   // Store the selected option in the settings file
//                   settings.setValue("stopBits", stopBits);
//                   settings.endGroup();

//                   // Retrieve the stored value and print to the console
//                   QString stopBitsConfig = settings.value("stopBits" , stopBits).toString();

//                   qDebug() << "selected option:" << stopBits;
//                   qDebug() << "stopBits:" << stopBitsConfig;
//               });












//               // Create the data bits label and combo box

//               QLabel* DataBitsLabel = new QLabel(tr("Data Bits"), this);
//               QComboBox* DataBitsComboBox = new QComboBox(this);
//               DataBitsComboBox->addItems(QStringList() << "5" << "6" << "7" << "8");
//               DataBitsLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
//               DataBitsComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

//               // ----------------------- Save DataBits configs into a file.txt-----------------------------------//


//               QString DataBitsConfig = settings.value("DataBits", "").toString();
////                QString stopBitsConfig;
//               // Set the selected option in the combo box

//               int indexDataBits = DataBitsComboBox->findText(DataBitsConfig);
//               if (indexDataBits != -1)
//                   DataBitsComboBox->setCurrentIndex(indexDataBits);

//               // Connect the combo box to the slot
//    //           connect(stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dashboard::onStopBitsComboBoxChanged);
//               QString DataBits; // declare stopBits outside of the lambda

//               connect(DataBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&DataBits](int indexDataBits){
//                   // Retrieve the selected option
//                   QSettings settings("file.txt", QSettings::IniFormat);

//                   QString DataBits = DataBitsComboBox->itemText(indexDataBits);
//                   settings.beginGroup("UARTConfigs");


//                   // Store the selected option in the settings file
//                   settings.setValue("DataBits", DataBits);
//                   settings.endGroup();

//                   // Retrieve the stored value and print to the console
//                   QString DataBitsConfig = settings.value("DataBits" , DataBits).toString();
////                   qDebug() << "Retrieved stopBits:" << stopBitsConfig;

//                   qDebug() << "selected option:" << DataBits;
//                   qDebug() << "DataBits:" << DataBitsConfig;
//               });

//               // Create the flow control label and combo box

//               layout->addRow(DataBitsLabel, DataBitsComboBox);
//               QLabel* FlowControlLabel = new QLabel(tr("Flow Control"), this);
//               QComboBox* FlowControlComboBox = new QComboBox(this);
//               FlowControlComboBox->addItems(QStringList() << "No Flow Control" << "Hardware Flow Control" << "Software Flow Control " );
//               FlowControlLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
//               FlowControlComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");




//               layout->addRow(FlowControlLabel, FlowControlComboBox);
//               layout->setContentsMargins(0, 0, 0, 0);
//               layout->setSpacing(30);


//               //--------------------------- Save Stop Bits Configs into a file.txt -------------------------//

//                 QString FlowControlConfig = settings.value("FlowControl", "").toString();
//                 // Set the selected option in the combo box

//                 int indexFlowControl = FlowControlComboBox->findText(FlowControlConfig);
//                 if (indexFlowControl != -1)
//                     FlowControlComboBox->setCurrentIndex(indexFlowControl);

//                 QString FlowControl; // declare FlowControl outside of the lambda

//                 // Connect the combo box to the slot

//                 connect(FlowControlComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=,&FlowControl](int indexFlowControl){
//                     // Retrieve the selected option
//                     QSettings settings("file.txt", QSettings::IniFormat);

//                     QString FlowControl = FlowControlComboBox->itemText(indexFlowControl);
//                     settings.beginGroup("UARTConfigs");


//                     // Store the selected option in the settings file
//                     settings.setValue("FlowControl", FlowControl);
//                     settings.endGroup();

//                     // Retrieve the stored value and print to the console
//                     QString FlowControlConfig = settings.value("FlowControl" , FlowControl).toString();

//                     qDebug() << "selected option:" << FlowControl;
//                     qDebug() << "FlowControl:" << FlowControlConfig;
//                 });

//               // Create the vertical layout and add the form layout to it
//               QVBoxLayout* verticalLayout = new QVBoxLayout(this);
//               verticalLayout->addStretch();
//               verticalLayout->addLayout(layout);
//               verticalLayout->addStretch();

//               // Create the horizontal layout and add the vertical layout to it
//               QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
//               horizontalLayout->addStretch();
//               horizontalLayout->addLayout(verticalLayout);
//               horizontalLayout->addStretch();

//               // Set the widget layout to the horizontal layout

//               widget->setLayout(horizontalLayout);
//               widget->setGeometry(500, 500, 600, 500);
//               widget->setStyleSheet("QFormLayout {"
//                                         "  background-color: gray;"
//                                         "  border: 2px solid black;"
//                                         "  padding: 10px;"
//                                         "}"
//                                         "QLineEdit {"
//                                         "  background-color: white;"
//                                         "  border: 1px solid black;"
//                                         "  padding: 5px;"
//                                         "}");

//               QSettings settings("file.txt", QSettings::IniFormat);

//               qDebug() << "Settings file path: " << settings.fileName();



//               settings.beginGroup("UARTConfigs");

//               settings.setValue("Baudrate",  Baudrate);
//               settings.setValue("stopBits",  stopBits);
//               settings.setValue("DataBits",  DataBits);
//               settings.setValue("FlowControl",  FlowControl);
//               settings.setValue("Parity",  Parity);

//               settings.endGroup();













//               // Create the QLabel and set its text and minimum height
//               QLabel* footerLabel = new QLabel();
//               footerLabel->setText("Footer Text");
//               footerLabel->setMinimumHeight(40);



//               // Add the QLabel to the QHBoxLayout and center it
//               //layout->addWidget(footerLabel, 0, Qt::AlignHCenter);

//               // Set the size of the QWidget
//               widget->setGeometry(100, 100, 400, 300);
//        QSettings settings("UARTConfig.txt", QSettings::IniFormat);

//        QListWidget* configList = new QListWidget(this);
//        configList->clear(); // clear the list

//         // create a new item for each selected configuration option
//        QString Baudrate; // declare stopBits outside of the lambda
//        QString Parity;

//         QListWidgetItem* baudRateItem = new QListWidgetItem("Baud Rate: " +  settings.value("Baudrate" ,Baudrate).toString(), configList);
//         QListWidgetItem* parityItem = new QListWidgetItem("Parity: " + settings.value("Parity" ,Parity).toString(), configList);
//         settings.beginGroup("UART4Configs");

//         qDebug() << "selected option:" << baudRateItem;
//         qDebug() << "selected option:" << parityItem;

//         QString BaudrateConfig = settings.value("Baudrate" , Baudrate).toString();
//         qDebug() << "baudrate option:" << BaudrateConfig;

//         settings.endGroup();

         QSettings settings("UARTConfig.txt", QSettings::IniFormat);
         QListWidget* configList = new QListWidget(this);
         configList->clear();

         // get baudrate value from settings file
                  settings.beginGroup("UART4Configs");

         QString baudRate = settings.value("Baudrate").toString();
                  qDebug() << "baudrate option:" << baudRate;

                  settings.endGroup();


         // create list item with baudrate value
         QListWidgetItem* baudRateItem = new QListWidgetItem("Baud Rate: " + baudRate, configList);

         qDebug() << "baudrate:" << baudRateItem;


         // add item to list widget
         configList->addItem(baudRateItem);






//         // set the font and style for the items
//         QFont itemFont("Arial", 12);
//         itemFont.setBold(true);
//         baudRateItem->setFont(itemFont);
//         parityItem->setFont(itemFont);
////         baudRateItem->setTextColor(QColor("#328930")); // set the color of the text
////         parityItem->setTextColor(QColor("#328930"));

//         // add the items to the list
//         configList->addItem(baudRateItem);
//         configList->addItem(parityItem);





    }

};

#endif // CONFIGMODE_H
