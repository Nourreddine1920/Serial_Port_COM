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
    void addActionToMenu(QString menuItem, QString actionName);
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


    }
    void showUART5config(){
                              QListWidget* configList = new QListWidget(this);
                              configList->clear();
                                      QListWidgetItem* titleItem = new QListWidgetItem(tr("I2C1 Configurations"), configList);


                                      QListWidgetItem* TimingItem = new QListWidgetItem(tr("•  Timing     :     ") , configList);
                                      QListWidgetItem* SpeedItem = new QListWidgetItem(tr("•  Speed       :  ") , configList);
                                      QListWidgetItem* FrequencyItem = new QListWidgetItem(tr("•  Frequency     :    ")  , configList);
                                      QListWidgetItem* RiseItem = new QListWidgetItem(tr("•  Rise     :    ") , configList);
                                      QListWidgetItem* FallItem = new QListWidgetItem(tr("•  Fall    :    ")  , configList);
                                      QListWidgetItem* ConverterItem = new QListWidgetItem(tr("•  Converter    :    ")  , configList);
                                      QListWidgetItem* AnalogFilterItem = new QListWidgetItem(tr("•  AnalogFilter    :    ") , configList);


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
    }
    void showI2C1config(){}
    void showI2C2config(){}
    void showADC1config(){}
    void showADC3config(){}




};

#endif // CONFIGMODE_H
