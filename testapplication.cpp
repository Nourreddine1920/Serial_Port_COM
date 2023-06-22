#include "testapplication.h"
#include "ui_testapplication.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "uart.h"
#include "dashboard.h"
#include "directrun.h"
#include <QAction>
#include <QMenu>
#include <QProcess>
#include <QElapsedTimer>
#include <QCoreApplication>
#include <QProgressDialog>
#include "runmode.h"
#include "sequenceapplication.h"
#include <QMenuBar>
#include "sequenceapplication.h"
testApplication::testApplication(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::testApplication)
{
    ui->setupUi(this);

    QWidget* testapplication = new QWidget(this);
    QWidget::setWindowTitle("test Application");

    centralWidget()->resize(400,300);
    setCentralWidget(testapplication);

    QImage backgroundImage("C:/Users/nawledbr/Documents/Serial_Port_COM/2.png");

    // Création d'un label pour afficher l'image
//    QWidget window;

    QLabel* backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap::fromImage(backgroundImage));

    // Configuration de la position et de la taille du label d'arrière-plan
    backgroundLabel->setGeometry(0, 0, width(), height());
    backgroundLabel->setScaledContents(true); // Adapter l'image à la taille du label

    // Assurez-vous que le label d'arrière-plan est en dessous des autres widgets
    backgroundLabel->lower();

    Uart* uart = Uart::getInstance();
    QSerialPort* serialPort = uart->getSerialPort();



    // Create controls for configuring the SPI interface
    // Create buttons for sending and receiving data
    QPushButton* sendButton = new QPushButton("Go to sequence application");
    QPushButton* receiveButton = new QPushButton("Go to test IPs");

    // Create a layout for the widget
    QVBoxLayout* layout = new QVBoxLayout(testapplication);
    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(sendButton);
    buttonLayout->addWidget(receiveButton);
//    layout->addLayout(buttonLayout);

    layout->addStretch();

    // Add the horizontal layout with the buttons to the bottom of the vertical layout
    layout->addLayout(buttonLayout);

    // Set the layout of the window
    setLayout(layout);

    // Add a stretch to push the buttons to the bottom of the vertical layout

//    titleLabel->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");
//                iconLabel->setStyleSheet("font-weight: bold; color: white; background-color: #328930; ");


    QString styleSheet2 =
        "QPushButton {"
        "    background-color: white;"
        "    border: none;"
        "    color: #0000cd;"
        "    padding: 3px 3px;"
        "    text-align: center;"
        "    text-decoration: none;"
        "    font-size: 16px;"
        "    margin: 4px 2px;"
        "    border-radius: 10px;"
        "}"
        ""
        "QPushButton:hover {"
        "    background-color: #32CD32			;"
        "}";


    receiveButton->setStyleSheet(styleSheet2);
    sendButton->setStyleSheet(styleSheet2);


//    titleLabel->setAlignment(Qt::AlignCenter);


    // Add the title label and the icon to the main layout
    testapplication->resize(400,300);

    connect(receiveButton, &QPushButton::clicked, [=]() {

        Runmode* runmode = new Runmode();

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
                              runmode->addActionToMenu("&UART", uartOption);
                              addedUartOptions.insert(uartOption);


                               }




                    }






                    for (int i = 0; i < Dashboard::selectedI2COptionsStatic.size(); i++) {
                        QString I2COption = Dashboard::selectedI2COptionsStatic.at(i);
                        // Vérifier si l'élément a déjà été ajouté pour I2C
                              if (!addedI2COptions.contains(I2COption)) {
                                  runmode->addActionToMenu("&I2C", I2COption);
                                  addedI2COptions.insert(I2COption);
                              }
                    }
                    for (int i = 0; i < Dashboard::selectedSPIOptionsStatic.size(); i++) {
                        QString SPIOption = Dashboard::selectedSPIOptionsStatic.at(i);
                              if (!addedSPIOptions.contains(SPIOption)) {
                                  runmode->addActionToMenu("&SPI", SPIOption);
                                  addedSPIOptions.insert(SPIOption);
                              }
                    }

                    for (int i = 0; i < Dashboard::selectedADCOptionsStatic.size(); i++) {
                        QString ADCOption = Dashboard::selectedADCOptionsStatic.at(i);
                        if (!addedADCOptions.contains(ADCOption)) {
                           runmode->addActionToMenu("&ADC", ADCOption);
                            addedADCOptions.insert(ADCOption);
                        }

                    }

                    for (int i = 0; i < Dashboard::selectedDACOptionsStatic.size(); i++) {
                        QString DACOption = Dashboard::selectedDACOptionsStatic.at(i);
                        if (!addedDACOptions.contains(DACOption)) {
                           runmode->addActionToMenu("&DAC", DACOption);
                            addedDACOptions.insert(DACOption);
                        }
                    }

                    for (int i = 0; i < Dashboard::selectedGPIOOptionsStatic.size(); i++) {
                        QString GPIOOption = Dashboard::selectedGPIOOptionsStatic.at(i);
                        if (!addedGPIOOptions.contains(GPIOOption)) {
                           runmode->addActionToMenu("&GPIO", GPIOOption);
                            addedGPIOOptions.insert(GPIOOption);
                        }
                    }

                    for (int i = 0; i < Dashboard::selectedTIMEROptionsStatic.size(); i++) {
                        QString TIMEROption = Dashboard::selectedTIMEROptionsStatic.at(i);
                        if (!addedTIMEROptions.contains(TIMEROption)) {
                          runmode->addActionToMenu("&Frequency Mesure", TIMEROption);
                            addedTIMEROptions.insert(TIMEROption);
                        }

                    }


        runmode->show();
        this->hide();

    });



    connect(sendButton, &QPushButton::clicked, [=]() {

        testApplication* test = new testApplication();
        sequenceApplication* sequence = new sequenceApplication();

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
                              sequence->addActionToMenu("&UART", uartOption);
                              addedUartOptions.insert(uartOption);


                               }




                    }






                    for (int i = 0; i < Dashboard::selectedI2COptionsStatic.size(); i++) {
                        QString I2COption = Dashboard::selectedI2COptionsStatic.at(i);
                        // Vérifier si l'élément a déjà été ajouté pour I2C
                              if (!addedI2COptions.contains(I2COption)) {
                                  sequence->addActionToMenu("&I2C", I2COption);
                                  addedI2COptions.insert(I2COption);
                              }
                    }
                    for (int i = 0; i < Dashboard::selectedSPIOptionsStatic.size(); i++) {
                        QString SPIOption = Dashboard::selectedSPIOptionsStatic.at(i);
                              if (!addedSPIOptions.contains(SPIOption)) {
                                  sequence->addActionToMenu("&SPI", SPIOption);
                                  addedSPIOptions.insert(SPIOption);
                              }
                    }

                    for (int i = 0; i < Dashboard::selectedADCOptionsStatic.size(); i++) {
                        QString ADCOption = Dashboard::selectedADCOptionsStatic.at(i);
                        if (!addedADCOptions.contains(ADCOption)) {
                           sequence->addActionToMenu("&ADC", ADCOption);
                            addedADCOptions.insert(ADCOption);
                        }

                    }

                    for (int i = 0; i < Dashboard::selectedDACOptionsStatic.size(); i++) {
                        QString DACOption = Dashboard::selectedDACOptionsStatic.at(i);
                        if (!addedDACOptions.contains(DACOption)) {
                           sequence->addActionToMenu("&DAC", DACOption);
                            addedDACOptions.insert(DACOption);
                        }
                    }

                    for (int i = 0; i < Dashboard::selectedGPIOOptionsStatic.size(); i++) {
                        QString GPIOOption = Dashboard::selectedGPIOOptionsStatic.at(i);
                        if (!addedGPIOOptions.contains(GPIOOption)) {
                           sequence->addActionToMenu("&GPIO", GPIOOption);
                            addedGPIOOptions.insert(GPIOOption);
                        }
                    }

                    for (int i = 0; i < Dashboard::selectedTIMEROptionsStatic.size(); i++) {
                        QString TIMEROption = Dashboard::selectedTIMEROptionsStatic.at(i);
                        if (!addedTIMEROptions.contains(TIMEROption)) {
                          sequence->addActionToMenu("&Frequency Mesure", TIMEROption);
                            addedTIMEROptions.insert(TIMEROption);
                        }

                    }



        sequence->show();
        this->hide();



    });

}


testApplication::~testApplication()
{
    delete ui;
}
