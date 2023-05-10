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
//    static QStringList selectedUartOptionsStatic;
//    static QStringList selectedI2COptionsStatic;
//    static QStringList selectedSPIOptionsStatic;
//    static QStringList selectedADCOptionsStatic;
//    static QStringList selectedDACOptionsStatic;
//    static QStringList selectedGPIOOptionsStatic;
//    static QStringList selectedTIMEROptionsStatic;



public slots :
    void returnDashboard();
    void addActionToMenu(QString menuItem, QString actionName);
    void sendframe();
    void onUartOptionSelected();

//    void onI2COptionSelected();
//    void onSPIOptionSelected();
//    void onADCOptionSelected();
//    void onDACOptionSelected();
//    void onGPIOOptionSelected();
//    void onTIMEROptionSelected();

private slots :
    void showUART4config(){
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
                QBrush gray(Qt::darkGreen);
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
                configList->setStyleSheet("background-color: #E3E0DF; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



        //        layout1->addRow(configList);
        //        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
        //                                  "QListWidget::item { padding: 5px; }"
        //                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


                // set the central widget of the main window to the layout
                setCentralWidget(centralWidget);


    }
    void showUART5config(){
        QSettings settings("UARTConfig.txt", QSettings::IniFormat);

        // create the list widget
        QListWidget* configList = new QListWidget(this);
        configList->clear();
        settings.beginGroup("UART5Configs");

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



        QListWidgetItem* titleItem = new QListWidgetItem(tr("UART5 Configurations"), configList);

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
        QBrush gray(Qt::darkGreen);
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
        QLabel* titleLabel = new QLabel("UART5 configurations", this);

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
        configList->setStyleSheet("background-color: #E3E0DF; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



//        layout1->addRow(configList);
//        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
//                                  "QListWidget::item { padding: 5px; }"
//                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


        // set the central widget of the main window to the layout
        setCentralWidget(centralWidget);

    }
    void showUSART1config(){
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
        QBrush gray(Qt::darkGreen);
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
        configList->setStyleSheet("background-color: #E3E0DF; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



//        layout1->addRow(configList);
//        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
//                                  "QListWidget::item { padding: 5px; }"
//                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


        // set the central widget of the main window to the layout
        setCentralWidget(centralWidget);
    }
    void showUSART2config(){
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


        QListWidgetItem* baudRateItem = new QListWidgetItem(tr("•  Baud Rate  :  ") +BaudrateConfig , configList);
        QListWidgetItem* ParityItem = new QListWidgetItem(tr("•  Parity  :  ") +ParityConfig , configList);
        QListWidgetItem* stopBitsItem = new QListWidgetItem(tr("•  stopBits  :  ") +stopBitsConfig , configList);
        QListWidgetItem* DataBitsItem = new QListWidgetItem(tr("•  DataBits  :  ") +DataBitsConfig , configList);
        QListWidgetItem* FlowControlItem = new QListWidgetItem(tr("•  FlowControl  :  ") +FlowControlConfig , configList);


        // Set the font and style sheet for the title label
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 18);

        titleItem->setFont(font);
        titleItem->setTextAlignment(Qt::TopLeftCorner);
        QBrush gray(Qt::darkGreen);
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
        configList->setStyleSheet("background-color: #E3E0DF; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



//        layout1->addRow(configList);
//        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
//                                  "QListWidget::item { padding: 5px; }"
//                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


        // set the central widget of the main window to the layout
        setCentralWidget(centralWidget);
    }
    void showSPI1config(){
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


        QListWidgetItem* ModeItem = new QListWidgetItem(tr("•  Mode  :  ") +ModeConfig , configList);
        QListWidgetItem* NSSItem = new QListWidgetItem(tr("•  NSS  :  ") +NSSConfig , configList);
        QListWidgetItem* FrameformatItem = new QListWidgetItem(tr("•  Frameformat  :  ") +FrameformatConfig , configList);
        QListWidgetItem* DatasizeItem = new QListWidgetItem(tr("•  Datasize  :  ") +DatasizeConfig , configList);
        QListWidgetItem* FirstbitItem = new QListWidgetItem(tr("•  Firstbit  :  ") +FirstbitConfig , configList);




        // Set the font and style sheet for the title label
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 18);

        titleItem->setFont(font);
        titleItem->setTextAlignment(Qt::TopLeftCorner);
        QBrush gray(Qt::darkGreen);
        QBrush white(Qt::white);

        titleItem->setBackground(gray);
        titleItem->setForeground(white);

        ModeItem->setFont(QFont("Helvetica", 12));
        ModeItem->setTextAlignment(Qt::TopLeftCorner);
        NSSItem->setFont(QFont("Helvetica", 12));
        NSSItem->setTextAlignment(Qt::TopLeftCorner);
        FrameformatItem->setFont(QFont("Helvetica", 12));
        FrameformatItem->setTextAlignment(Qt::TopLeftCorner);
        DatasizeItem->setFont(QFont("Helvetica", 12));
        DatasizeItem->setTextAlignment(Qt::TopLeftCorner);
        FirstbitItem->setFont(QFont("Helvetica", 12));
        FirstbitItem->setTextAlignment(Qt::TopLeftCorner);


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
        configList->setStyleSheet("background-color: #E3E0DF; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



//        layout1->addRow(configList);
//        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
//                                  "QListWidget::item { padding: 5px; }"
//                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


        // set the central widget of the main window to the layout
        setCentralWidget(centralWidget);
    }
    void showSPI2config(){
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

        QListWidgetItem* ModeItem = new QListWidgetItem(tr("•  Mode  : ") +ModeConfig , configList);
        QListWidgetItem* NSSItem = new QListWidgetItem(tr("•  NSS  : ") +NSSConfig , configList);
        QListWidgetItem* FrameformatItem = new QListWidgetItem(tr("•  Frameformat  : ") +FrameformatConfig , configList);
        QListWidgetItem* DatasizeItem = new QListWidgetItem(tr("•  Datasize  : ") +DatasizeConfig , configList);
        QListWidgetItem* FirstbitItem = new QListWidgetItem(tr("•  Firstbit  : ") +FirstbitConfig , configList);


        // Set the font and style sheet for the title label
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 18);

        titleItem->setFont(font);
        titleItem->setTextAlignment(Qt::TopLeftCorner);
        QBrush gray(Qt::darkGreen);
        QBrush white(Qt::white);

        titleItem->setBackground(gray);
        titleItem->setForeground(white);

        ModeItem->setFont(QFont("Helvetica", 12));
        ModeItem->setTextAlignment(Qt::TopLeftCorner);
        NSSItem->setFont(QFont("Helvetica", 12));
        NSSItem->setTextAlignment(Qt::TopLeftCorner);
        FrameformatItem->setFont(QFont("Helvetica", 12));
        FrameformatItem->setTextAlignment(Qt::TopLeftCorner);
        DatasizeItem->setFont(QFont("Helvetica", 12));
        DatasizeItem->setTextAlignment(Qt::TopLeftCorner);
        FirstbitItem->setFont(QFont("Helvetica", 12));
        FirstbitItem->setTextAlignment(Qt::TopLeftCorner);


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
        configList->setStyleSheet("background-color: #E3E0DF; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



//        layout1->addRow(configList);
//        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
//                                  "QListWidget::item { padding: 5px; }"
//                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


        // set the central widget of the main window to the layout
        setCentralWidget(centralWidget);
    }
    void showSPI3config(){
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

        QListWidgetItem* ModeItem = new QListWidgetItem(tr("•  Mode  : ") +ModeConfig , configList);
        QListWidgetItem* NSSItem = new QListWidgetItem(tr("•  NSS  : ") +NSSConfig , configList);
        QListWidgetItem* FrameformatItem = new QListWidgetItem(tr("•  Frameformat  : ") +FrameformatConfig , configList);
        QListWidgetItem* DatasizeItem = new QListWidgetItem(tr("•  Datasize  : ") +DatasizeConfig , configList);
        QListWidgetItem* FirstbitItem = new QListWidgetItem(tr("•  Firstbit  : ") +FirstbitConfig , configList);


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
        QBrush gray(Qt::darkGreen);
        QBrush white(Qt::white);

        titleItem->setBackground(gray);
        titleItem->setForeground(white);

        ModeItem->setFont(QFont("Helvetica", 12));
        ModeItem->setTextAlignment(Qt::TopLeftCorner);
        NSSItem->setFont(QFont("Helvetica", 12));
        NSSItem->setTextAlignment(Qt::TopLeftCorner);
        FrameformatItem->setFont(QFont("Helvetica", 12));
        FrameformatItem->setTextAlignment(Qt::TopLeftCorner);
        DatasizeItem->setFont(QFont("Helvetica", 12));
        DatasizeItem->setTextAlignment(Qt::TopLeftCorner);
        FirstbitItem->setFont(QFont("Helvetica", 12));
        FirstbitItem->setTextAlignment(Qt::TopLeftCorner);


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
    }
    void showI2C1config(){
            QSettings settings("I2CConfig.txt", QSettings::IniFormat);

            // create the list widget
            QListWidget* configList = new QListWidget(this);
            configList->clear();
            settings.beginGroup("I2C1Configs");

            QString AdressLenght ;
            QString DualAddressMode;
            QString NoStretchMode;
            QString AddressMasks;
            QString GeneralCallMode;




            QString AdressLenghtConfig = settings.value("AdressLenght" , AdressLenght).toString();
            QString DualAddressModeConfig = settings.value("DualAddressMode" , DualAddressMode).toString();
            QString NoStretchModeConfig = settings.value("NoStretchMode" , NoStretchMode).toString();
            QString AddressMasksConfig = settings.value("AddressMasks" , AddressMasks).toString();
            QString GeneralCallModeConfig = settings.value("GeneralCallMode" , GeneralCallMode).toString();



            QListWidgetItem* titleItem = new QListWidgetItem(tr("I2C1 Configurations"), configList);


            QListWidgetItem* AdressLenghtItem = new QListWidgetItem(tr("•  Adress Lenght     :     ") +AdressLenghtConfig , configList);
            QListWidgetItem* DualAddressModeItem = new QListWidgetItem(tr("•  Dual Address Mode       :  ") +DualAddressModeConfig , configList);
            QListWidgetItem* NoStretchModeItem = new QListWidgetItem(tr("•  No Stretch Mode     :    ") +NoStretchModeConfig , configList);
            QListWidgetItem* AddressMasksItem = new QListWidgetItem(tr("•  Address Masks     :    ") +AddressMasksConfig , configList);
            QListWidgetItem* GeneralCallModeItem = new QListWidgetItem(tr("•  General Call Mode    :    ") +GeneralCallModeConfig , configList);



            // Set the font and style sheet for the title label
            QFontDatabase fontDatabase;
            QStringList fontFamilies = fontDatabase.families();

            // Choose the first available font as the best font
            QString bestFont = fontFamilies.first();

            // Create a font object with the best font and size
            QFont font(bestFont, 18);

            titleItem->setFont(font);
            titleItem->setTextAlignment(Qt::TopLeftCorner);
            QBrush gray(Qt::darkGreen);
            QBrush white(Qt::white);

            titleItem->setBackground(gray);
            titleItem->setForeground(white);

            AdressLenghtItem->setFont(QFont("Helvetica", 13));
            AdressLenghtItem->setTextAlignment(Qt::TopLeftCorner);
            DualAddressModeItem->setFont(QFont("Helvetica", 13));
            DualAddressModeItem->setTextAlignment(Qt::TopLeftCorner);
            NoStretchModeItem->setFont(QFont("Helvetica", 13));
            NoStretchModeItem->setTextAlignment(Qt::TopLeftCorner);
            AddressMasksItem->setFont(QFont("Helvetica", 13));
            AddressMasksItem->setTextAlignment(Qt::TopLeftCorner);
            GeneralCallModeItem->setFont(QFont("Helvetica", 13));
            GeneralCallModeItem->setTextAlignment(Qt::TopLeftCorner);



            configList->setSpacing(15);
            configList->addItem(titleItem);

            configList->addItem(AdressLenghtItem);
            configList->addItem(DualAddressModeItem);
            configList->addItem(NoStretchModeItem);
            configList->addItem(AddressMasksItem);
            configList->addItem(GeneralCallModeItem);




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
            configList->setStyleSheet("background-color: #E3E0DF; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



    //        layout1->addRow(configList);
    //        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
    //                                  "QListWidget::item { padding: 5px; }"
    //                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


            // set the central widget of the main window to the layout
            setCentralWidget(centralWidget);
        }
        void showI2C2config(){
            QSettings settings("I2CConfig.txt", QSettings::IniFormat);

            // create the list widget
            QListWidget* configList = new QListWidget(this);
            configList->clear();
            settings.beginGroup("I2C2Configs");

            QString AdressLenght ;
            QString DualAddressMode;
            QString NoStretchMode;
            QString AddressMasks;
            QString GeneralCallMode;




            QString AdressLenghtConfig = settings.value("AdressLenght" , AdressLenght).toString();
            QString DualAddressModeConfig = settings.value("DualAddressMode" , DualAddressMode).toString();
            QString NoStretchModeConfig = settings.value("NoStretchMode" , NoStretchMode).toString();
            QString AddressMasksConfig = settings.value("AddressMasks" , AddressMasks).toString();
            QString GeneralCallModeConfig = settings.value("GeneralCallMode" , GeneralCallMode).toString();



            QListWidgetItem* titleItem = new QListWidgetItem(tr("I2C2 Configurations"), configList);


            QListWidgetItem* AdressLenghtItem = new QListWidgetItem(tr("•  Adress Lenght     :     ") +AdressLenghtConfig , configList);
            QListWidgetItem* DualAddressModeItem = new QListWidgetItem(tr("•  Dual Address Mode       :  ") +DualAddressModeConfig , configList);
            QListWidgetItem* NoStretchModeItem = new QListWidgetItem(tr("•  No Stretch Mode     :    ") +NoStretchModeConfig , configList);
            QListWidgetItem* AddressMasksItem = new QListWidgetItem(tr("•  Address Masks     :    ") +AddressMasksConfig , configList);
            QListWidgetItem* GeneralCallModeItem = new QListWidgetItem(tr("•  General Call Mode    :    ") +GeneralCallModeConfig , configList);



            // Set the font and style sheet for the title label
            QFontDatabase fontDatabase;
            QStringList fontFamilies = fontDatabase.families();

            // Choose the first available font as the best font
            QString bestFont = fontFamilies.first();

            // Create a font object with the best font and size
            QFont font(bestFont, 18);

            titleItem->setFont(font);
            titleItem->setTextAlignment(Qt::TopLeftCorner);
            QBrush gray(Qt::darkGreen);
            QBrush white(Qt::white);

            titleItem->setBackground(gray);
            titleItem->setForeground(white);

            AdressLenghtItem->setFont(QFont("Helvetica", 13));
            AdressLenghtItem->setTextAlignment(Qt::TopLeftCorner);
            DualAddressModeItem->setFont(QFont("Helvetica", 13));
            DualAddressModeItem->setTextAlignment(Qt::TopLeftCorner);
            NoStretchModeItem->setFont(QFont("Helvetica", 13));
            NoStretchModeItem->setTextAlignment(Qt::TopLeftCorner);
            AddressMasksItem->setFont(QFont("Helvetica", 13));
            AddressMasksItem->setTextAlignment(Qt::TopLeftCorner);
            GeneralCallModeItem->setFont(QFont("Helvetica", 13));
            GeneralCallModeItem->setTextAlignment(Qt::TopLeftCorner);



            configList->setSpacing(15);
            configList->addItem(titleItem);

            configList->addItem(AdressLenghtItem);
            configList->addItem(DualAddressModeItem);
            configList->addItem(NoStretchModeItem);
            configList->addItem(AddressMasksItem);
            configList->addItem(GeneralCallModeItem);




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
            configList->setStyleSheet("background-color: #E3E0DF; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



    //        layout1->addRow(configList);
    //        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
    //                                  "QListWidget::item { padding: 5px; }"
    //                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


            // set the central widget of the main window to the layout
            setCentralWidget(centralWidget);
        }
    void showADC1config(){
        QSettings settings("ADCConfig.txt", QSettings::IniFormat);

        // create the list widget
        QListWidget* configList = new QListWidget(this);
        configList->clear();
        settings.beginGroup("ADC1Configs");

        QString Channel;
        QString Resolution;
        QString Scan;
        QString Continuous;
        QString Discontinuous;
        QString EndConversion;
        QString Behavior;
        QString LeftBit;




        QString ChannelConfig = settings.value("Channel" , Channel).toString();
        QString ResolutionConfig = settings.value("Resolution" , Resolution).toString();
        QString ScanConfig = settings.value("Scan" , Scan).toString();
        QString ContinuousConfig = settings.value("Continuous" , Continuous).toString();
        QString DiscontinuousConfig = settings.value("Discontinuous" , Discontinuous).toString();
        QString EndConversionConfig = settings.value("EndConversion" , EndConversion).toString();
        QString BehaviorConfig = settings.value("Behavior" , Behavior).toString();
        QString LeftBitConfig = settings.value("LeftBit" , LeftBit).toString();


        QListWidgetItem* titleItem = new QListWidgetItem(tr("ADC1 Configurations"), configList);


        QListWidgetItem* ChannelItem = new QListWidgetItem(tr("•  Channel     :     ") +ChannelConfig , configList);
        QListWidgetItem* ResolutionItem = new QListWidgetItem(tr("•  Resolution       :  ") +ResolutionConfig , configList);
        QListWidgetItem* ScanItem = new QListWidgetItem(tr("•  Scan     :    ") +ScanConfig , configList);
        QListWidgetItem* ContinuousItem = new QListWidgetItem(tr("•  Continuous     :    ") +ContinuousConfig , configList);
        QListWidgetItem* DiscontinuousItem = new QListWidgetItem(tr("•  Discontinuous    :    ") +DiscontinuousConfig , configList);
        QListWidgetItem* EndConversionItem = new QListWidgetItem(tr("•  EndConversion    :    ") +EndConversionConfig , configList);
        QListWidgetItem* BehaviorItem = new QListWidgetItem(tr("•  Behavior    :    ") +BehaviorConfig , configList);
        QListWidgetItem* LeftBitItem = new QListWidgetItem(tr("•  LeftBit    :    ") +LeftBitConfig , configList);

        // Set the font and style sheet for the title label
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 18);

        titleItem->setFont(font);
        titleItem->setTextAlignment(Qt::TopLeftCorner);
        QBrush gray(Qt::darkGreen);
        QBrush white(Qt::white);

        titleItem->setBackground(gray);
        titleItem->setForeground(white);

        ChannelItem->setFont(QFont("Helvetica", 13));
        ChannelItem->setTextAlignment(Qt::TopLeftCorner);
        ResolutionItem->setFont(QFont("Helvetica", 13));
        ResolutionItem->setTextAlignment(Qt::TopLeftCorner);
        ScanItem->setFont(QFont("Helvetica", 13));
        ScanItem->setTextAlignment(Qt::TopLeftCorner);
        ContinuousItem->setFont(QFont("Helvetica", 13));
        ContinuousItem->setTextAlignment(Qt::TopLeftCorner);
        DiscontinuousItem->setFont(QFont("Helvetica", 13));
        DiscontinuousItem->setTextAlignment(Qt::TopLeftCorner);
        EndConversionItem->setFont(QFont("Helvetica", 13));
        EndConversionItem->setTextAlignment(Qt::TopLeftCorner);
        BehaviorItem->setFont(QFont("Helvetica", 13));
        BehaviorItem->setTextAlignment(Qt::TopLeftCorner);
        LeftBitItem->setFont(QFont("Helvetica", 13));
        LeftBitItem->setTextAlignment(Qt::TopLeftCorner);


        configList->setSpacing(15);
        configList->addItem(titleItem);

        configList->addItem(ChannelItem);
        configList->addItem(ResolutionItem);
        configList->addItem(ScanItem);
        configList->addItem(ContinuousItem);
        configList->addItem(DiscontinuousItem);
        configList->addItem(EndConversionItem);
        configList->addItem(BehaviorItem);
        configList->addItem(LeftBitItem);




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
        configList->setStyleSheet("background-color: #E3E0DF; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



//        layout1->addRow(configList);
//        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
//                                  "QListWidget::item { padding: 5px; }"
//                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


        // set the central widget of the main window to the layout
        setCentralWidget(centralWidget);
    }
    void showADC3config(){
        QSettings settings("ADCConfig.txt", QSettings::IniFormat);

        // create the list widget
        QListWidget* configList = new QListWidget(this);
        configList->clear();
        settings.beginGroup("ADC3Configs");

        QString Channel;
        QString Resolution;
        QString Scan;
        QString Continuous;
        QString Discontinuous;
        QString EndConversion;
        QString Behavior;
        QString LeftBit;




        QString ChannelConfig = settings.value("Channel" , Channel).toString();
        QString ResolutionConfig = settings.value("Resolution" , Resolution).toString();
        QString ScanConfig = settings.value("Scan" , Scan).toString();
        QString ContinuousConfig = settings.value("Continuous" , Continuous).toString();
        QString DiscontinuousConfig = settings.value("Discontinuous" , Discontinuous).toString();
        QString EndConversionConfig = settings.value("EndConversion" , EndConversion).toString();
        QString BehaviorConfig = settings.value("Behavior" , Behavior).toString();
        QString LeftBitConfig = settings.value("LeftBit" , LeftBit).toString();


        QListWidgetItem* titleItem = new QListWidgetItem(tr("ADC3 Configurations"), configList);


        QListWidgetItem* ChannelItem = new QListWidgetItem(tr("•  Channel     :     ") +ChannelConfig , configList);
        QListWidgetItem* ResolutionItem = new QListWidgetItem(tr("•  Resolution       :  ") +ResolutionConfig , configList);
        QListWidgetItem* ScanItem = new QListWidgetItem(tr("•  Scan     :    ") +ScanConfig , configList);
        QListWidgetItem* ContinuousItem = new QListWidgetItem(tr("•  Continuous     :    ") +ContinuousConfig , configList);
        QListWidgetItem* DiscontinuousItem = new QListWidgetItem(tr("•  Discontinuous    :    ") +DiscontinuousConfig , configList);
        QListWidgetItem* EndConversionItem = new QListWidgetItem(tr("•  EndConversion    :    ") +EndConversionConfig , configList);
        QListWidgetItem* BehaviorItem = new QListWidgetItem(tr("•  Behavior    :    ") +BehaviorConfig , configList);
        QListWidgetItem* LeftBitItem = new QListWidgetItem(tr("•  LeftBit    :    ") +LeftBitConfig , configList);

        // Set the font and style sheet for the title label
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 18);

        titleItem->setFont(font);
        titleItem->setTextAlignment(Qt::TopLeftCorner);
        QBrush gray(Qt::darkGreen);
        QBrush white(Qt::white);

        titleItem->setBackground(gray);
        titleItem->setForeground(white);

        ChannelItem->setFont(QFont("Helvetica", 13));
        ChannelItem->setTextAlignment(Qt::TopLeftCorner);
        ResolutionItem->setFont(QFont("Helvetica", 13));
        ResolutionItem->setTextAlignment(Qt::TopLeftCorner);
        ScanItem->setFont(QFont("Helvetica", 13));
        ScanItem->setTextAlignment(Qt::TopLeftCorner);
        ContinuousItem->setFont(QFont("Helvetica", 13));
        ContinuousItem->setTextAlignment(Qt::TopLeftCorner);
        DiscontinuousItem->setFont(QFont("Helvetica", 13));
        DiscontinuousItem->setTextAlignment(Qt::TopLeftCorner);
        EndConversionItem->setFont(QFont("Helvetica", 13));
        EndConversionItem->setTextAlignment(Qt::TopLeftCorner);
        BehaviorItem->setFont(QFont("Helvetica", 13));
        BehaviorItem->setTextAlignment(Qt::TopLeftCorner);
        LeftBitItem->setFont(QFont("Helvetica", 13));
        LeftBitItem->setTextAlignment(Qt::TopLeftCorner);


        configList->setSpacing(15);
        configList->addItem(titleItem);

        configList->addItem(ChannelItem);
        configList->addItem(ResolutionItem);
        configList->addItem(ScanItem);
        configList->addItem(ContinuousItem);
        configList->addItem(DiscontinuousItem);
        configList->addItem(EndConversionItem);
        configList->addItem(BehaviorItem);
        configList->addItem(LeftBitItem);




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
        configList->setStyleSheet("background-color: #E3E0DF; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



//        layout1->addRow(configList);
//        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
//                                  "QListWidget::item { padding: 5px; }"
//                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


        // set the central widget of the main window to the layout
        setCentralWidget(centralWidget);
    }


    void showGPIOOUTPUTconfig(){
        QSettings settings("GPIOConfig.txt", QSettings::IniFormat);

        // create the list widget
        QListWidget* configList = new QListWidget(this);
        configList->clear();
        settings.beginGroup("GPIOOUTPUTConfigs");

        QString PIN;
        QString Mode;
        QString GPIO;
        QString Speed;

        QString User;




        QString PINConfig = settings.value("PIN" , PIN).toString();
        QString ModeConfig = settings.value("Mode" , Mode).toString();
        QString GPIOConfig = settings.value("GPIO" , GPIO).toString();
        QString SpeedConfig = settings.value("Speed" , Speed).toString();
        QString UserLabelConfig = settings.value("User" , User).toString();


        QListWidgetItem* titleItem = new QListWidgetItem(tr("GPIO OUTPUT Configurations"), configList);


        QListWidgetItem* PINItem = new QListWidgetItem(tr("•  PIN     :     ") +PINConfig , configList);
        QListWidgetItem* ModeItem = new QListWidgetItem(tr("•  Mode       :  ") +ModeConfig , configList);
        QListWidgetItem* GPIOItem = new QListWidgetItem(tr("•  GPIO     :    ") +GPIOConfig , configList);
        QListWidgetItem* SpeedItem = new QListWidgetItem(tr("•  Speed     :    ") +SpeedConfig , configList);
        QListWidgetItem* UserLabelItem = new QListWidgetItem(tr("•  UserLabel    :    ") +UserLabelConfig , configList);

        // Set the font and style sheet for the title label
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 18);

        titleItem->setFont(font);
        titleItem->setTextAlignment(Qt::TopLeftCorner);
        QBrush gray(Qt::darkGreen);
        QBrush white(Qt::white);

        titleItem->setBackground(gray);
        titleItem->setForeground(white);

        PINItem->setFont(QFont("Helvetica", 13));
        PINItem->setTextAlignment(Qt::TopLeftCorner);
        ModeItem->setFont(QFont("Helvetica", 13));
        ModeItem->setTextAlignment(Qt::TopLeftCorner);
        GPIOItem->setFont(QFont("Helvetica", 13));
        GPIOItem->setTextAlignment(Qt::TopLeftCorner);
        SpeedItem->setFont(QFont("Helvetica", 13));
        SpeedItem->setTextAlignment(Qt::TopLeftCorner);
        UserLabelItem->setFont(QFont("Helvetica", 13));
        UserLabelItem->setTextAlignment(Qt::TopLeftCorner);


        configList->setSpacing(15);
        configList->addItem(titleItem);

        configList->addItem(PINItem);
        configList->addItem(ModeItem);
        configList->addItem(GPIOItem);
        configList->addItem(SpeedItem);
        configList->addItem(UserLabelItem);




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
        configList->setStyleSheet("background-color: #E3E0DF; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



//        layout1->addRow(configList);
//        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
//                                  "QListWidget::item { padding: 5px; }"
//                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


        // set the central widget of the main window to the layout
        setCentralWidget(centralWidget);
    }
    void showGPIOINPUTconfig(){
        QSettings settings("GPIOConfig.txt", QSettings::IniFormat);

        // create the list widget
        QListWidget* configList = new QListWidget(this);
        configList->clear();
        settings.beginGroup("GPIOINPUTConfigs");

        QString PIN;
        QString GPIO;
        QString User;




        QString PINConfig = settings.value("PIN" , PIN).toString();
        QString GPIOConfig = settings.value("GPIO" , GPIO).toString();
        QString UserLabelConfig = settings.value("User" , User).toString();


        QListWidgetItem* titleItem = new QListWidgetItem(tr("GPIO INPUT Configurations"), configList);


        QListWidgetItem* PINItem = new QListWidgetItem(tr("•  PIN     :     ") +PINConfig , configList);
        QListWidgetItem* GPIOItem = new QListWidgetItem(tr("•  GPIO     :    ") +GPIOConfig , configList);
        QListWidgetItem* UserLabelItem = new QListWidgetItem(tr("•  User Label    :    ") +UserLabelConfig , configList);

        // Set the font and style sheet for the title label
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 18);

        titleItem->setFont(font);
        titleItem->setTextAlignment(Qt::TopLeftCorner);
        QBrush gray(Qt::darkGreen);
        QBrush white(Qt::white);

        titleItem->setBackground(gray);
        titleItem->setForeground(white);

        PINItem->setFont(QFont("Helvetica", 13));
        PINItem->setTextAlignment(Qt::TopLeftCorner);
        GPIOItem->setFont(QFont("Helvetica", 13));
        GPIOItem->setTextAlignment(Qt::TopLeftCorner);
        UserLabelItem->setFont(QFont("Helvetica", 13));
        UserLabelItem->setTextAlignment(Qt::TopLeftCorner);


        configList->setSpacing(15);
        configList->addItem(titleItem);

        configList->addItem(PINItem);
        configList->addItem(GPIOItem);
        configList->addItem(UserLabelItem);




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
        configList->setStyleSheet("background-color: #E3E0DF; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



//        layout1->addRow(configList);
//        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
//                                  "QListWidget::item { padding: 5px; }"
//                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


        // set the central widget of the main window to the layout
        setCentralWidget(centralWidget);
    }
    void showDACOUT1config(){
        QSettings settings("DACConfig.txt", QSettings::IniFormat);

        // create the list widget
        QListWidget* configList = new QListWidget(this);
        configList->clear();
        settings.beginGroup("DAC1Configs");
//        settings.beginGroup("DAC2Configs");

        QString Channel;
        QString Mode;
        QString Buffer;
        QString Trigger;
        QString Trimming;

//        QString Channel2;




        QString ChannelConfig = settings.value("Channel" , Channel).toString();
//        QString Channel2Config = settings.value("Channel2" , Channel2).toString();

        QString ModeConfig = settings.value("Mode" , Mode).toString();
        QString BufferLabelConfig = settings.value("Buffer" , Buffer).toString();
        QString TriggerLabelConfig = settings.value("Trigger" , Trigger).toString();
        QString TrimmingLabelConfig = settings.value("Trimming" , Trimming).toString();

        qDebug() << "selected option:" << ModeConfig;
        qDebug() << "selected option:" << BufferLabelConfig;
        qDebug() << "selected option:" << TriggerLabelConfig;
        qDebug() << "selected option:" << TrimmingLabelConfig;



        QListWidgetItem* titleItem = new QListWidgetItem(tr("DAC OUT1 Configurations"), configList);


        QListWidgetItem* ChannelItem = new QListWidgetItem(tr("•  Channel OUT1     :     ") +ChannelConfig , configList);
//        QListWidgetItem* Channel2Item = new QListWidgetItem(tr("•  Channel OUT2     :     ") +Channel2Config , configList);

        QListWidgetItem* ModeItem = new QListWidgetItem(tr("•  Mode     :    ") +ModeConfig , configList);
        QListWidgetItem* BufferLabelItem = new QListWidgetItem(tr("•  Buffer Label    :    ") +BufferLabelConfig , configList);
        QListWidgetItem* TriggerLabelItem = new QListWidgetItem(tr("•  Trigger Label    :    ") +TriggerLabelConfig , configList);
        QListWidgetItem* TrimmingLabelItem = new QListWidgetItem(tr("•  Trimming Label    :    ") +TrimmingLabelConfig , configList);





        qDebug() << "Mode option:" << ChannelItem;
//        qDebug() << "Mode option:" << Channel2Item;
        qDebug() << "Mode option:" << ModeItem;
        qDebug() << "Mode option:" << BufferLabelItem;
        qDebug() << "Mode option:" << TriggerLabelItem;
        qDebug() << "Mode option:" << TrimmingLabelItem;

        // Set the font and style sheet for the title label
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 18);

        titleItem->setFont(font);
        titleItem->setTextAlignment(Qt::TopLeftCorner);
        QBrush gray(Qt::darkGreen);
        QBrush white(Qt::white);

        titleItem->setBackground(gray);
        titleItem->setForeground(white);

        ChannelItem->setFont(QFont("Helvetica", 13));
        ChannelItem->setTextAlignment(Qt::TopLeftCorner);
//        Channel2Item->setFont(QFont("Helvetica", 13));
//        Channel2Item->setTextAlignment(Qt::TopLeftCorner);
        ModeItem->setFont(QFont("Helvetica", 13));
        ModeItem->setTextAlignment(Qt::TopLeftCorner);
        BufferLabelItem->setFont(QFont("Helvetica", 13));
        BufferLabelItem->setTextAlignment(Qt::TopLeftCorner);
        TriggerLabelItem->setFont(QFont("Helvetica", 13));
        TriggerLabelItem->setTextAlignment(Qt::TopLeftCorner);
        TrimmingLabelItem->setFont(QFont("Helvetica", 13));
        TrimmingLabelItem->setTextAlignment(Qt::TopLeftCorner);


        configList->setSpacing(15);
        configList->addItem(titleItem);

        configList->addItem(ChannelItem);
//        configList->addItem(Channel2Item);

        configList->addItem(ModeItem);
        configList->addItem(BufferLabelItem);
        configList->addItem(TriggerLabelItem);
        configList->addItem(TrimmingLabelItem);




        configList->show();

        settings.endGroup();
//        settings.endGroup();


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
        configList->setStyleSheet("background-color: #E3E0DF; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



//        layout1->addRow(configList);
//        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
//                                  "QListWidget::item { padding: 5px; }"
//                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


        // set the central widget of the main window to the layout
        setCentralWidget(centralWidget);
    }
    void showDACOUT2config(){
        QSettings settings("DACConfig.txt", QSettings::IniFormat);

        // create the list widget
        QListWidget* configList = new QListWidget(this);
        configList->clear();
        settings.beginGroup("DAC2Configs");
//        settings.beginGroup("DAC2Configs");

        QString Channel2;
        QString Mode;
        QString Buffer;
        QString Trigger;
        QString Trimming;

//        QString Channel22;




        QString Channel2Config = settings.value("Channel2" , Channel2).toString();
//        QString Channel22Config = settings.value("Channel22" , Channel22).toString();

        QString ModeConfig = settings.value("Mode" , Mode).toString();
        QString BufferLabelConfig = settings.value("Buffer" , Buffer).toString();
        QString TriggerLabelConfig = settings.value("Trigger" , Trigger).toString();
        QString TrimmingLabelConfig = settings.value("Trimming" , Trimming).toString();

        qDebug() << "selected option:" << ModeConfig;
        qDebug() << "selected option:" << BufferLabelConfig;
        qDebug() << "selected option:" << TriggerLabelConfig;
        qDebug() << "selected option:" << TrimmingLabelConfig;



        QListWidgetItem* titleItem = new QListWidgetItem(tr("DAC OUT2 Configurations"), configList);


        QListWidgetItem* Channel2Item = new QListWidgetItem(tr("•  Channel2 OUT1     :     ") +Channel2Config , configList);
//        QListWidgetItem* Channel22Item = new QListWidgetItem(tr("•  Channel2 OUT2     :     ") +Channel22Config , configList);

        QListWidgetItem* ModeItem = new QListWidgetItem(tr("•  Mode     :    ") +ModeConfig , configList);
        QListWidgetItem* BufferLabelItem = new QListWidgetItem(tr("•  Buffer Label    :    ") +BufferLabelConfig , configList);
        QListWidgetItem* TriggerLabelItem = new QListWidgetItem(tr("•  Trigger Label    :    ") +TriggerLabelConfig , configList);
        QListWidgetItem* TrimmingLabelItem = new QListWidgetItem(tr("•  Trimming Label    :    ") +TrimmingLabelConfig , configList);





        qDebug() << "Mode option:" << Channel2Item;
//        qDebug() << "Mode option:" << Channel22Item;
        qDebug() << "Mode option:" << ModeItem;
        qDebug() << "Mode option:" << BufferLabelItem;
        qDebug() << "Mode option:" << TriggerLabelItem;
        qDebug() << "Mode option:" << TrimmingLabelItem;

        // Set the font and style sheet for the title label
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 18);

        titleItem->setFont(font);
        titleItem->setTextAlignment(Qt::TopLeftCorner);
        QBrush gray(Qt::darkGreen);
        QBrush white(Qt::white);

        titleItem->setBackground(gray);
        titleItem->setForeground(white);

        Channel2Item->setFont(QFont("Helvetica", 13));
        Channel2Item->setTextAlignment(Qt::TopLeftCorner);
//        Channel22Item->setFont(QFont("Helvetica", 13));
//        Channel22Item->setTextAlignment(Qt::TopLeftCorner);
        ModeItem->setFont(QFont("Helvetica", 13));
        ModeItem->setTextAlignment(Qt::TopLeftCorner);
        BufferLabelItem->setFont(QFont("Helvetica", 13));
        BufferLabelItem->setTextAlignment(Qt::TopLeftCorner);
        TriggerLabelItem->setFont(QFont("Helvetica", 13));
        TriggerLabelItem->setTextAlignment(Qt::TopLeftCorner);
        TrimmingLabelItem->setFont(QFont("Helvetica", 13));
        TrimmingLabelItem->setTextAlignment(Qt::TopLeftCorner);


        configList->setSpacing(15);
        configList->addItem(titleItem);

        configList->addItem(Channel2Item);
//        configList->addItem(Channel2Item);

        configList->addItem(ModeItem);
        configList->addItem(BufferLabelItem);
        configList->addItem(TriggerLabelItem);
        configList->addItem(TrimmingLabelItem);




        configList->show();

        settings.endGroup();
//        settings.endGroup();


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
        configList->setStyleSheet("background-color: #E3E0DF; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



//        layout1->addRow(configList);
//        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
//                                  "QListWidget::item { padding: 5px; }"
//                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


        // set the central widget of the main window to the layout
        setCentralWidget(centralWidget);
    }

    void showFrequencyMesureconfig(){
        QSettings settings("FrequencyMesureConfig.txt", QSettings::IniFormat);

        // create the list widget
        QListWidget* configList = new QListWidget(this);
        configList->clear();
        settings.beginGroup("FrequencyMesureConfigs");
//        settings.beginGroup("DAC2Configs");

        QString Channel;
        QString Prescaler;
        QString Counter;
        QString AutoReload;
        QString Clock;
        QString Repitition;
        QString Preload;





        QString ChannelConfig = settings.value("Channel" , Channel).toString();

        QString PrescalerConfig = settings.value("Prescaler" , Prescaler).toString();
        QString CounterLabelConfig = settings.value("Counter" , Counter).toString();
        QString AutoReloadLabelConfig = settings.value("AutoReload" , AutoReload).toString();
        QString ClockLabelConfig = settings.value("Clock" , Clock).toString();
        QString RepititionConfig = settings.value("Repitition" , Repitition).toString();
        QString PreloadConfig = settings.value("Preload" , Preload).toString();

        qDebug() << "selected option:" << PrescalerConfig;
        qDebug() << "selected option:" << CounterLabelConfig;
        qDebug() << "selected option:" << AutoReloadLabelConfig;
        qDebug() << "selected option:" << ClockLabelConfig;



        QListWidgetItem* titleItem = new QListWidgetItem(tr("Frequency Mesure Configurations"), configList);


        QListWidgetItem* ChannelItem = new QListWidgetItem(tr("•  Channel OUT1     :     ") +ChannelConfig , configList);

        QListWidgetItem* PrescalerItem = new QListWidgetItem(tr("•  Prescaler     :    ") +PrescalerConfig , configList);
        QListWidgetItem* CounterLabelItem = new QListWidgetItem(tr("•  Counter Label    :    ") +CounterLabelConfig , configList);
        QListWidgetItem* AutoReloadLabelItem = new QListWidgetItem(tr("•  AutoReload Label    :    ") +AutoReloadLabelConfig , configList);
        QListWidgetItem* ClockLabelItem = new QListWidgetItem(tr("•  Clock Label    :    ") +ClockLabelConfig , configList);
        QListWidgetItem* RepititionItem = new QListWidgetItem(tr("•  Repitition   :    ") +RepititionConfig , configList);
        QListWidgetItem* PreloadItem = new QListWidgetItem(tr("•  Preload    :    ") +PreloadConfig , configList);





        qDebug() << "Prescaler option:" << ChannelItem;
        qDebug() << "Prescaler option:" << PrescalerItem;
        qDebug() << "Prescaler option:" << CounterLabelItem;
        qDebug() << "Prescaler option:" << AutoReloadLabelItem;
        qDebug() << "Prescaler option:" << ClockLabelItem;

        // Set the font and style sheet for the title label
        QFontDatabase fontDatabase;
        QStringList fontFamilies = fontDatabase.families();

        // Choose the first available font as the best font
        QString bestFont = fontFamilies.first();

        // Create a font object with the best font and size
        QFont font(bestFont, 18);

        titleItem->setFont(font);
        titleItem->setTextAlignment(Qt::TopLeftCorner);
        QBrush gray(Qt::darkGreen);
        QBrush white(Qt::white);

        titleItem->setBackground(gray);
        titleItem->setForeground(white);

        ChannelItem->setFont(QFont("Helvetica", 13));
        ChannelItem->setTextAlignment(Qt::TopLeftCorner);
//        Channel2Item->setFont(QFont("Helvetica", 13));
//        Channel2Item->setTextAlignment(Qt::TopLeftCorner);
        PrescalerItem->setFont(QFont("Helvetica", 13));
        PrescalerItem->setTextAlignment(Qt::TopLeftCorner);
        CounterLabelItem->setFont(QFont("Helvetica", 13));
        CounterLabelItem->setTextAlignment(Qt::TopLeftCorner);
        AutoReloadLabelItem->setFont(QFont("Helvetica", 13));
        AutoReloadLabelItem->setTextAlignment(Qt::TopLeftCorner);
        ClockLabelItem->setFont(QFont("Helvetica", 13));
        ClockLabelItem->setTextAlignment(Qt::TopLeftCorner);
        RepititionItem->setFont(QFont("Helvetica", 13));
        RepititionItem->setTextAlignment(Qt::TopLeftCorner);
        PreloadItem->setFont(QFont("Helvetica", 13));
        PreloadItem->setTextAlignment(Qt::TopLeftCorner);

        configList->setSpacing(15);
        configList->addItem(titleItem);

        configList->addItem(ChannelItem);

        configList->addItem(PrescalerItem);
        configList->addItem(CounterLabelItem);
        configList->addItem(AutoReloadLabelItem);
        configList->addItem(ClockLabelItem);
        configList->addItem(RepititionItem);
        configList->addItem(PreloadItem);




        configList->show();

        settings.endGroup();
//        settings.endGroup();


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
        configList->setStyleSheet("background-color: #E3E0DF; font-size: 14px; border: 1px solid #ccc; padding: 5px;text-align: center;");



//        layout1->addRow(configList);
//        configList->setStyleSheet("QListWidget { background-color: white; border: 1px solid gray; }"
//                                  "QListWidget::item { padding: 5px; }"
//                                  "QListWidget::item:hover { background-color: #E6F9FF; }");


        // set the central widget of the main window to the layout
        setCentralWidget(centralWidget);
    }





};

#endif // CONFIGMODE_H
