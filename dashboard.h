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
                QFontDatabase fontDatabase;
                QStringList fontFamilies = fontDatabase.families();

                // Choose the first available font as the best font
                QString bestFont = fontFamilies.first();

                // Create a font object with the best font and size
                QFont font(bestFont, 15);

                // Set the font and style sheet for the label
                titleLabel->setFont(font);
                titleLabel->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");

                titleLabel->setAlignment(Qt::AlignCenter);
        //        titleLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");

        //        QFont titleFont("Helvetica", 10, QFont::Bold);
        //        titleLabel->setFont(titleFont);
                layout->addRow(titleLabel);

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

                // Create a QLabel for "DAC configurations" and center it horizontally
                QLabel* titleLabel = new QLabel("UART4 configurations", this);
                QFontDatabase fontDatabase;
                QStringList fontFamilies = fontDatabase.families();

                // Choose the first available font as the best font
                QString bestFont = fontFamilies.first();

                // Create a font object with the best font and size
                QFont font(bestFont, 15);

                // Set the font and style sheet for the label
                titleLabel->setFont(font);
                titleLabel->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");

                titleLabel->setAlignment(Qt::AlignCenter);
        //        titleLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");

        //        QFont titleFont("Helvetica", 10, QFont::Bold);
        //        titleLabel->setFont(titleFont);
                layout->addRow(titleLabel);

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

                // Create a QLabel for "DAC configurations" and center it horizontally
                QLabel* titleLabel = new QLabel("UART5 configurations", this);
                QFontDatabase fontDatabase;
                QStringList fontFamilies = fontDatabase.families();

                // Choose the first available font as the best font
                QString bestFont = fontFamilies.first();

                // Create a font object with the best font and size
                QFont font(bestFont, 15);

                // Set the font and style sheet for the label
                titleLabel->setFont(font);
                titleLabel->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");

                titleLabel->setAlignment(Qt::AlignCenter);
        //        titleLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");

        //        QFont titleFont("Helvetica", 10, QFont::Bold);
        //        titleLabel->setFont(titleFont);
                layout->addRow(titleLabel);

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

                // Create a QLabel for "DAC configurations" and center it horizontally
                QLabel* titleLabel = new QLabel("USART1 configurations", this);
                QFontDatabase fontDatabase;
                QStringList fontFamilies = fontDatabase.families();

                // Choose the first available font as the best font
                QString bestFont = fontFamilies.first();

                // Create a font object with the best font and size
                QFont font(bestFont, 15);

                // Set the font and style sheet for the label
                titleLabel->setFont(font);
                titleLabel->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");

                titleLabel->setAlignment(Qt::AlignCenter);
        //        titleLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");

        //        QFont titleFont("Helvetica", 10, QFont::Bold);
        //        titleLabel->setFont(titleFont);
                layout->addRow(titleLabel);

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

                // Create a QLabel for "DAC configurations" and center it horizontally
                QLabel* titleLabel = new QLabel("USART2 configurations", this);
                QFontDatabase fontDatabase;
                QStringList fontFamilies = fontDatabase.families();

                // Choose the first available font as the best font
                QString bestFont = fontFamilies.first();

                // Create a font object with the best font and size
                QFont font(bestFont, 15);

                // Set the font and style sheet for the label
                titleLabel->setFont(font);
                titleLabel->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");

                titleLabel->setAlignment(Qt::AlignCenter);
        //        titleLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");

        //        QFont titleFont("Helvetica", 10, QFont::Bold);
        //        titleLabel->setFont(titleFont);
                layout->addRow(titleLabel);

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


                // Create a QLabel for "DAC configurations" and center it horizontally
                QLabel* titleLabel = new QLabel("SPI configurations", this);
                QFontDatabase fontDatabase;
                QStringList fontFamilies = fontDatabase.families();

                // Choose the first available font as the best font
                QString bestFont = fontFamilies.first();

                // Create a font object with the best font and size
                QFont font(bestFont, 15);

                // Set the font and style sheet for the label
                titleLabel->setFont(font);
                titleLabel->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");

                titleLabel->setAlignment(Qt::AlignCenter);
        //        titleLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");

        //        QFont titleFont("Helvetica", 10, QFont::Bold);
        //        titleLabel->setFont(titleFont);
                layout->addRow(titleLabel);

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

               // ----------------------Create NSS----------------------//

               QLabel* NSSLabel = new QLabel(tr("Hardware NSS Signal"), this);
               QComboBox* NSSComboBox = new QComboBox(this);
               NSSComboBox->addItems(QStringList() << "Disable" << "Hardware NSS Input Signal" << "Hardware NSS Output Signal");
               NSSLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               NSSComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(NSSLabel, NSSComboBox);



               // ----------------------Create Frame Format----------------------//

               QLabel* FrameFormatLabel = new QLabel(tr("Frame Format"), this);
               QComboBox* FrameFormatComboBox = new QComboBox(this);
               FrameFormatComboBox->addItems(QStringList() << "Motorola" << "Texas Instruments");
               FrameFormatLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FrameFormatComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(FrameFormatLabel, FrameFormatComboBox);


               // ----------------------Create Data size----------------------//

               QLabel* DataSizeLabel = new QLabel(tr("Data Size"), this);
               QSpinBox* DataSizeSpinBox = new QSpinBox(this);
               DataSizeSpinBox->setMinimum(4);
               DataSizeSpinBox->setMaximum(32);

               DataSizeLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               DataSizeSpinBox->setStyleSheet("font:Arial 15px; color: gray; background-color: white;");
               layout->addRow(DataSizeLabel, DataSizeSpinBox);


               // ----------------------Create First Bit----------------------//

               QLabel* FirstBitLabel = new QLabel(tr("First Bit"), this);
               QComboBox* FirstBitComboBox = new QComboBox(this);
               FirstBitComboBox->addItems(QStringList() << "LSB" << "MSB"  );
               FirstBitLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FirstBitComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(FirstBitLabel, FirstBitComboBox);
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

               // ----------------------Save configs into a file----------------------//


               QSettings settings("file.txt", QSettings::IniFormat);



               settings.beginGroup("SPIConfigs");


               settings.setValue("Mode",  ModeComboBox->currentText());
               settings.setValue("NSS",  NSSComboBox->currentText());
               settings.setValue("Frameformat",  FrameFormatComboBox->currentText());
               settings.setValue("Datasize",  DataSizeSpinBox->value());
               settings.setValue("Firstbit",  FirstBitComboBox->currentText());

               settings.endGroup();





    }
    void I2CConfig (){
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

                // Create Layout form for I2C
                QFormLayout* layout = new QFormLayout(this);

                // Create a QLabel for "DAC configurations" and center it horizontally
                QLabel* titleLabel = new QLabel("I2C configurations", this);
                QFontDatabase fontDatabase;
                QStringList fontFamilies = fontDatabase.families();

                // Choose the first available font as the best font
                QString bestFont = fontFamilies.first();

                // Create a font object with the best font and size
                QFont font(bestFont, 15);

                // Set the font and style sheet for the label
                titleLabel->setFont(font);
                titleLabel->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");

                titleLabel->setAlignment(Qt::AlignCenter);

                layout->addRow(titleLabel);



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

               // ----------------------Create Speed Mode----------------------//

               QLabel* SpeedLabel = new QLabel(tr("I2C Speed Mode"), this);
               QComboBox* SpeedComboBox = new QComboBox(this);
               SpeedComboBox->addItems(QStringList() << "Standart Mode" << "Fast Mode " << "Fast Mode Plus");
               SpeedLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               SpeedComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(SpeedLabel, SpeedComboBox);


               // ----------------------Create Frequency Speed----------------------//

               QLabel* FrequencyLabel = new QLabel(tr("Speed Frequency"), this);
               QComboBox* FrequencyComboBox = new QComboBox(this);
               FrequencyComboBox->addItems(QStringList() << "200 KHz" << "400 KHz " << "1 MHz");






               FrequencyLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FrequencyComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(FrequencyLabel, FrequencyComboBox);


               // ----------------------Create Rise Edge----------------------//

               QLabel* RiseLabel = new QLabel(tr("Rise Time"), this);
               QSpinBox* RiseSpinBox = new QSpinBox(this);
               RiseSpinBox->setMinimum(20);
               RiseSpinBox->setMaximum(1000);

               RiseLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               RiseSpinBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
               layout->addRow(RiseLabel, RiseSpinBox);


               // ----------------------Create Fall edge----------------------//

               QLabel* FallLabel = new QLabel(tr("Fall Time"), this);
               QSpinBox* FallSpinBox = new QSpinBox(this);
               FallSpinBox->setMinimum(10);
               FallSpinBox->setMaximum(300);

               FallLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FallSpinBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
               layout->addRow(FallLabel, FallSpinBox);


               // ----------------------Create Converter----------------------//

               QLabel* ConverterLabel = new QLabel(tr("Coefficient of Digital Converter"), this);
               QSpinBox* ConverterSpinBox = new QSpinBox(this);
               ConverterSpinBox->setMinimum(0);
               ConverterSpinBox->setMaximum(16);

               ConverterLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ConverterSpinBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
               layout->addRow(ConverterLabel, ConverterSpinBox);

               // ----------------------Create Analog Filter----------------------//

               QLabel* AnalogFilterLabel = new QLabel(tr("Analog Filter"), this);
               QComboBox* AnalogFilterComboBox = new QComboBox(this);
               AnalogFilterComboBox->addItems(QStringList() << "Enabled" << "Disabled"  );
               AnalogFilterLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               AnalogFilterComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               //QSpacerItem* spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);


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


               // ----------------------Save configs into file ----------------------//

               QSettings settings("file.txt", QSettings::IniFormat);



               settings.beginGroup("I2CConfigs");

               settings.setValue("Timing",  TimingComboBox->currentText());
               settings.setValue("I2CSpeedMode",  SpeedComboBox->currentText());
               settings.setValue("SpeedFrequency",  FrequencyComboBox->currentText());
               settings.setValue("RiseTime",  RiseSpinBox->value());
               settings.setValue("FallTime",  FallSpinBox->value());
               settings.setValue("CoefficientofDigitalConverter",  ConverterSpinBox->value());
               settings.setValue("Analogfilter",  AnalogFilterComboBox->currentText());



               settings.endGroup();



    }
    void ADCConfig (){
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

                // Create Layout form for ADC
                QFormLayout* layout = new QFormLayout(this);

                // Create a QLabel for "DAC configurations" and center it horizontally
                QLabel* titleLabel = new QLabel("ADC configurations", this);
                QFontDatabase fontDatabase;
                QStringList fontFamilies = fontDatabase.families();

                // Choose the first available font as the best font
                QString bestFont = fontFamilies.first();

                // Create a font object with the best font and size
                QFont font(bestFont, 15);

                // Set the font and style sheet for the label
                titleLabel->setFont(font);
                titleLabel->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");

                titleLabel->setAlignment(Qt::AlignCenter);
        //        titleLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");

        //        QFont titleFont("Helvetica", 10, QFont::Bold);
        //        titleLabel->setFont(titleFont);
                layout->addRow(titleLabel);



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

               // ----------------------Create Resolution Mode----------------------//

               QLabel* ResolutionLabel = new QLabel(tr("ADC Resolution Bit"), this);
               QComboBox* ResolutionComboBox = new QComboBox(this);
               ResolutionComboBox->addItems(QStringList() << "ADC 8-Bit Resolution" << "ADC 10-Bit Resolution" << "ADC 12-Bit Resolution" << "ADC 14-Bit Resolution" << "ADC 16-Bit Resolution"<< "ADC 12-Bit Optimized Resolution" << "ADC 14-Bit Optimized Resolution"  );
               ResolutionLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ResolutionComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(ResolutionLabel, ResolutionComboBox);


               // ----------------------Create Scan Mode----------------------//

               QLabel* ScanLabel = new QLabel(tr("Scan Conversion Mode"), this);
               QComboBox* ScanComboBox = new QComboBox(this);
               ScanComboBox->addItems(QStringList() << "Disabled" );
               ScanLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ScanComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               layout->addRow(ScanLabel, ScanComboBox);


               // ----------------------Create continuous Mode----------------------//

               QLabel* ContinuousLabel = new QLabel(tr("Continuous Conversion Mode"), this);
               QComboBox* ContinuousComboBox = new QComboBox(this);


               ContinuousComboBox->addItems(QStringList() << "Enabled" << "Disabled");

               ContinuousLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ContinuousComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
               layout->addRow(ContinuousLabel, ContinuousComboBox);


               // ----------------------Create Discontinuous Mode----------------------//

              QLabel* DiscontinuousLabel = new QLabel(tr("Discontinuous Conversion Mode"), this);
              QComboBox* DiscontinuousComboBox = new QComboBox(this);


              DiscontinuousComboBox->addItems(QStringList() << "Enabled" << "Disabled");

              DiscontinuousLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
              DiscontinuousComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
              layout->addRow(DiscontinuousLabel, DiscontinuousComboBox);


              // ----------------------Create End of Conversion Mode----------------------//

             QLabel* EndConversionLabel = new QLabel(tr("End of Conversion Mode"), this);
             QComboBox* EndConversionComboBox = new QComboBox(this);


             EndConversionComboBox->addItems(QStringList() << "End of Single Conversion" << "End of sequence Conversion");

             EndConversionLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
             EndConversionComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
             layout->addRow(EndConversionLabel, EndConversionComboBox);


             // ----------------------Create Behavior Bit----------------------//

            QLabel* BehaviorLabel = new QLabel(tr("Overrun Behavior"), this);
            QComboBox* BehaviorComboBox = new QComboBox(this);


            BehaviorComboBox->addItems(QStringList() << "Overrun Data Preserved" << "Overrun Data Overwritten");

            BehaviorLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
            BehaviorComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
            layout->addRow(BehaviorLabel, BehaviorComboBox);



            // ----------------------Create Left Bit----------------------//

               QLabel* LeftBitLabel = new QLabel(tr("Left Bit Shift"), this);
               QComboBox* LeftBitComboBox = new QComboBox(this);
               LeftBitComboBox->addItems(QStringList() << "No Bit Shift" << "1 Bit Shift" << "2 Bit Shift"<<  "3 Bit Shift" << "4 Bit Shift" <<"5 Bit Shift" << "6 Bit Shift" <<"7 Bit Shift" <<"8 Bit Shift" <<"9 Bit Shift" <<"10 Bit Shift" <<"11 Bit Shift" << "12 Bit Shift" <<"13 Bit Shift" <<"14 Bit Shift" << "15 Bit Shift" );
               LeftBitLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               LeftBitComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");

               //QSpacerItem* spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);


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

               // ----------------------Save Configs in file----------------------//
               QSettings settings("file.txt", QSettings::IniFormat);

               settings.beginGroup("ADCConfigs");

               settings.setValue("Channel",  ChannelComboBox->currentText());
               settings.setValue("Resolution",  ResolutionComboBox->currentText());
               settings.setValue("Scan",  ScanComboBox->currentText());
               settings.setValue("Continuous",  ContinuousComboBox->currentText());
               settings.setValue("Discontinuous",  DiscontinuousComboBox->currentText());
               settings.setValue("EndConversion",  EndConversionComboBox->currentText());
               settings.setValue("Behavior",  BehaviorComboBox->currentText());
               settings.setValue("LeftBit",  LeftBitComboBox->currentText());
               settings.endGroup();




    }
    void DACConfig (){
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

        // Create Layout form for DAC
        QFormLayout* layout = new QFormLayout(this);



        // Create a QLabel for "DAC configurations" and center it horizontally
        QLabel* titleLabel = new QLabel("DAC configurations", this);
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 15);

        // Set the font and style sheet for the label
        titleLabel->setFont(font);
        titleLabel->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");

        titleLabel->setAlignment(Qt::AlignCenter);
//        titleLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");

//        QFont titleFont("Helvetica", 10, QFont::Bold);
//        titleLabel->setFont(titleFont);
        layout->addRow(titleLabel);






        // -----------------OUT1 Connected to-----------------//

        QLabel* ChannelLabel = new QLabel(tr("OUT1 Connected to "), this);
        QComboBox* ChannelComboBox = new QComboBox(this);
        ChannelComboBox->addItems(QStringList() << "Disable" << "Only External Pin" << "Only on Chip Analog Peripherals" <<"Both external Pin and on Chip Analog" );
        ChannelLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        ChannelComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
        layout->addRow(ChannelLabel, ChannelComboBox);

        // --------------OUT2 Connected to--------------------//

        QLabel* Channel2Label = new QLabel(tr("OUT2 Connected to "), this);
        QComboBox* Channel2ComboBox = new QComboBox(this);
        Channel2ComboBox->addItems(QStringList() << "Disable" << "Only External Pin" << "Only on Chip Analog Peripherals" <<"Both external Pin and on Chip Analog" );
        Channel2Label->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        Channel2ComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");
        layout->addRow(Channel2Label, Channel2ComboBox);

        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);


        // --------------Connection between two widgets Channel1 & Channel2--------------------//

        connect(ChannelComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &Dashboard::ShowingDACConfigs);
        connect(Channel2ComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &Dashboard::ShowingDACConfigs);


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

    void ShowingDACConfigs(){

        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);


        QFormLayout* layout = new QFormLayout(this);

        // --------------Mode selected for the OUT1--------------------//

        QLabel* ModeLabel = new QLabel(tr("Mode selected"), this);
        QComboBox* ModeComboBox = new QComboBox(this);

        ModeComboBox->addItems(QStringList() << "Normal Mode" << "Sample and Hold Mode" );


        ModeLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        ModeComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(ModeLabel, ModeComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);

        // --------------Output Buffer for the OUT1--------------------//

        QLabel* BufferLabel = new QLabel(tr(" Output Buffer "), this);
        QComboBox* BufferComboBox = new QComboBox(this);

        BufferComboBox->addItems(QStringList() << "Enable" << "Disable" );


        BufferLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        BufferComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(BufferLabel, BufferComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);


        // --------------Trigger for the OUT1--------------------//

        QLabel* TriggerLabel = new QLabel(tr(" Trigger "), this);
        QComboBox* TriggerComboBox = new QComboBox(this);

        TriggerComboBox->addItems(QStringList() << "None" << "TIMER1 Trigger OUT event " << "TIMER1 Trigger OUT event " << "TIMER1 Trigger OUT event " << "TIMER2 Trigger OUT event " << "TIMER4 Trigger OUT event " << "TIMER5 Trigger OUT event " << "TIMER6 Trigger OUT event " << "TIMER7 Trigger OUT event " << "TIMER8 Trigger OUT event " << "TIMER15 Trigger OUT event" << "LPTIMER1 Trigger OUT event" << "LPTIMER2 Trigger OUT event" << "Software Trigger");


        TriggerLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        TriggerComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(TriggerLabel, TriggerComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);


        // --------------Trimming for the OUT1--------------------//

        QLabel* TrimmingLabel = new QLabel(tr(" Trimming "), this);
        QComboBox* TrimmingComboBox = new QComboBox(this);

        TrimmingComboBox->addItems(QStringList() << "Factory Trimming" << "User Trimming" );


        TrimmingLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        TrimmingComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(TrimmingLabel, TrimmingComboBox);
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


        // DAC Configs
        settings.beginGroup("SohwingDACConfigs");

        settings.setValue("ModeDAC",  ModeComboBox->currentText());
        settings.setValue("Buffer",  BufferComboBox->currentText());
        settings.setValue("Trigger",  TriggerComboBox->currentText());
        settings.setValue("Trimming",  TrimmingComboBox->currentText());




        settings.endGroup();



    }
    void GPIOOUPUTConfig(){

        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);


        QFormLayout* layout = new QFormLayout(this);

        // Create a QLabel for "DAC configurations" and center it horizontally
        QLabel* titleLabel = new QLabel("GPIO Output configurations", this);
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 15);

        // Set the font and style sheet for the label
        titleLabel->setFont(font);
        titleLabel->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");

        titleLabel->setAlignment(Qt::AlignCenter);
//        titleLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");

//        QFont titleFont("Helvetica", 10, QFont::Bold);
//        titleLabel->setFont(titleFont);
        layout->addRow(titleLabel);

        // --------------Select GPIO PIN--------------------//

        QLabel* PINLabel = new QLabel(tr("GPIO Output PIN "), this);
        QComboBox* PINComboBox = new QComboBox(this);

        PINComboBox->addItems(QStringList() << "PG4" << "PG5" << "PG6" << "PG7" << "PG10" << "PG11" << "PG12" << "PG13" );


        PINLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        PINComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(PINLabel, PINComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);

        // --------------GPIO Mode selected for the OUT1--------------------//

        QLabel* ModeLabel = new QLabel(tr("GPIO Mode "), this);
        QComboBox* ModeComboBox = new QComboBox(this);

        ModeComboBox->addItems(QStringList() << "Push-Pull" << "Open-Drain" );


        ModeLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        ModeComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(ModeLabel, ModeComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);

        // --------------GPIO PULL UP -- DOWN --------------------//

        QLabel* GPIOLabel = new QLabel(tr("GPIO Pull-up/Pull-down "), this);
        QComboBox* GPIOComboBox = new QComboBox(this);

        GPIOComboBox->addItems(QStringList() << "No Pull-up and No Pull-down" << "Pull-up" << "Pull-down" );


        GPIOLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        GPIOComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(GPIOLabel, GPIOComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);


        // --------------Maximum Output Speed for the GPIO OUTPUT--------------------//

        QLabel* SpeedLabel = new QLabel(tr(" Maximum Output Speed "), this);
        QComboBox* SpeedComboBox = new QComboBox(this);

        SpeedComboBox->addItems(QStringList() << "Low" << "Meduim" << "High" << "Very High" );


        SpeedLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        SpeedComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(SpeedLabel, SpeedComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);


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


        QSettings settings("file.txt", QSettings::IniFormat);


        // GPIO OUTPUT Configs
        settings.beginGroup("GPIOOUTPUT");

        settings.setValue("SelectedPIN",  PINComboBox->currentText());
        settings.setValue("GPIOMode",  ModeComboBox->currentText());

        settings.setValue("GPIOType",  GPIOComboBox->currentText());
        settings.setValue("GPIOSpeedOUTPUT",  SpeedComboBox->currentText());
        settings.setValue("UserLabel",  UserLineEdit->text());




        settings.endGroup();


        settings.beginGroup("GPIO OUTPUT ");
        settings.remove("");
        settings.endGroup();



    }

    void GPIOINPUTConfig(){

        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);


        QFormLayout* layout = new QFormLayout(this);
        // Create a QLabel for "DAC configurations" and center it horizontally
        QLabel* titleLabel = new QLabel("GPIO Input configurations", this);
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 15);

        // Set the font and style sheet for the label
        titleLabel->setFont(font);
        titleLabel->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");

        titleLabel->setAlignment(Qt::AlignCenter);
//        titleLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");

//        QFont titleFont("Helvetica", 10, QFont::Bold);
//        titleLabel->setFont(titleFont);
        layout->addRow(titleLabel);

        // --------------Select GPIO PIN--------------------//

        QLabel* PINLabel = new QLabel(tr("GPIO Input PIN "), this);
        QComboBox* PINComboBox = new QComboBox(this);

        PINComboBox->addItems(QStringList() << "PA6" << "PA7" << "PA8" << "PA9" << "PA10" << "PA11" << "PA12" << "PA13" );


        PINLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        PINComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(PINLabel, PINComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);

        // --------------GPIO PULL UP -- DOWN --------------------//

        QLabel* GPIOLabel = new QLabel(tr("GPIO Pull-up/Pull-down "), this);
        QComboBox* GPIOComboBox = new QComboBox(this);

        GPIOComboBox->addItems(QStringList() << "No Pull-up and No Pull-down" << "Pull-up" << "Pull-down" );


        GPIOLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        GPIOComboBox->setStyleSheet("font-weight: bold; border: 1px solid 868482; color: gray; background-color: white;");


        layout->addRow(GPIOLabel, GPIOComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);




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

        QSettings settings("file.txt", QSettings::IniFormat);


        // GPIO OUTPUT Configs
        settings.beginGroup("GPIOINPUT");

        settings.setValue("SelectedPIN",  PINComboBox->currentText());

        settings.setValue("GPIOType",  GPIOComboBox->currentText());
        settings.setValue("UserLabel",  UserLineEdit->text());




        settings.endGroup();


        settings.beginGroup("GPIO INPUT ");
        settings.remove("");
        settings.endGroup();



    }
    void FrequencyMesureConfig(){

        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);


        QFormLayout* layout = new QFormLayout(this);
        // Create a QLabel for "DAC configurations" and center it horizontally
        QLabel* titleLabel = new QLabel("Frequency Mesure configurations", this);
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 15);

        // Set the font and style sheet for the label
        titleLabel->setFont(font);
        titleLabel->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");

        titleLabel->setAlignment(Qt::AlignCenter);
//        titleLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");

//        QFont titleFont("Helvetica", 10, QFont::Bold);
//        titleLabel->setFont(titleFont);
        layout->addRow(titleLabel);

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


};

#endif // DASHBOARD_H
