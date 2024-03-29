#include "configchoice.h"
#include "ui_configchoice.h"
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

ConfigChoice::ConfigChoice(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigChoice)
{
    ui->setupUi(this);
    setFixedSize(width(), height());

    QWidget* configChoice = new QWidget(this);
    QWidget::setWindowTitle("Welcome Application");

    centralWidget()->resize(400,300);
    setCentralWidget(configChoice);

    QImage backgroundImage("C:/Users/nawledbr/Documents/Serial_Port_COM/welcome.png");

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
    QPushButton* sendButton = new QPushButton("Load Configurations");
    QPushButton* receiveButton = new QPushButton("Go to Dashboard Application");

    // Create a layout for the widget
    QVBoxLayout* layout = new QVBoxLayout(configChoice);
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
    configChoice->resize(400,300);

    connect(receiveButton, &QPushButton::clicked, [=]() {

        Dashboard* dashboard = new Dashboard();
        QString styleSheet = "\
        QProgressDialog {\
        background-color: #D3D3D3;\
        color: #454545;\
        font-family: Arial, sans-serif;\
        font-size: 15px;\
        }\
        \
        QProgressDialog QLabel {\
        color: #454545;\
        font-family:Fantasy;\
        font-size: 15px;\
        }\
        \
        QProgressDialog QProgressBar {\
        background-color: #E2DFD2;\
        border: 1px solid #CCCCCC;\
        color: #2AAA8A;\
        }\
        \
        QProgressDialog QPushButton {\
        background-color: #4CAF50;\
        border: 1px solid #388E3C;\
        color: #FFFFFF;\
        padding: 5px;\
        min-width: 70px;\
        }\
        \
        QProgressDialog QPushButton:hover {\
        background-color: #388E3C;\
        }";


        QProgressDialog progressDialog("Waiting...", "", 0, 0 , this);
        QFont font("Georgia", 10); // Police Arial avec une taille de 12 points

        font.setBold(true);
        progressDialog.setFont(font);

        progressDialog.setWindowTitle("Program Download");
        progressDialog.setWindowModality(Qt::WindowModal);
        progressDialog.setStyleSheet(styleSheet);
        progressDialog.setCancelButton(nullptr);
        progressDialog.show();
        QCoreApplication::processEvents();

        progressDelay(2000); // Délai progressif avant l'affichage de la boîte de message

        QString program = "C:/Program Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI.exe"; // Chemin vers le programme cubeprogrammer


        //         Commande pour l'écriture du fichier
                QStringList writeArguments;
                writeArguments << "-c" << "port=swd" << "-w" << "C:/Users/nawledbr/Documents/testBins/read.bin" << "0x08000000";
                QProcess writeProcess;
                writeProcess.start(program, writeArguments);
        //        writeProcess.startDetached(program, writeArguments);

                writeProcess.waitForFinished(-1);

                if (writeProcess.exitStatus() == QProcess::NormalExit && writeProcess.exitCode() == 0)
                {
                QStringList startArguments;
                startArguments << "-c" << "port=swd" << "--start" << "0x08000000";
                QProcess startProcess;
                startProcess.start(program, startArguments);
                startProcess.startDetached(program, startArguments);

                startProcess.waitForFinished(-1);

                // Vérifier si la commande s'est terminée avec succès
                if (startProcess.exitStatus() == QProcess::NormalExit && startProcess.exitCode() == 0)
                {
                // Passer à la page "Run Mode"


        //            /******************************* getting notification ***************************************/



                    QString styleSheet = "\
                        QMessageBox {\
                            background-color: #D3D3D3;\
                            color: #263238;\
                            font-family:Fantasy ;\
                            font-size: 12px;\
                        }\
                        \
                        QMessageBox QLabel {\
                            color: #000000	;\
                        }\
                        \
                        QMessageBox QPushButton {\
                            background-color: #4CAF50;\
                            border: 1px solid #388E3C;\
                            color: #FFFFFF;\
                            padding: 5px;\
                            min-width: 70px;\
                        }\
                        \
                        QMessageBox QPushButton:hover {\
                            background-color: #388E3C;\
                        }";


                        progressDialog.close();



                        QMessageBox msgBox;
                        msgBox.setWindowTitle("Runnig Program");
                        msgBox.setStyleSheet(styleSheet);
                        msgBox.setIcon(QMessageBox::Information);
                        msgBox.setText("Start Program achieved successfully !");
                        msgBox.exec();



                        dashboard->show();
                        this->hide();

        // ...
        }
        }

        else{
                    QString styleSheet = "\
                        QMessageBox {\
                            background-color: #D3D3D3;\
                            color: #263238;\
                            font-family:Fantasy ;\
                            font-size: 12px;\
                        }\
                        \
                        QMessageBox QLabel {\
                            color: #000000	;\
                        }\
                        \
                        QMessageBox QPushButton {\
                            background-color: #4CAF50;\
                            border: 1px solid #388E3C;\
                            color: #FFFFFF;\
                            padding: 5px;\
                            min-width: 70px;\
                        }\
                        \
                        QMessageBox QPushButton:hover {\
                            background-color: #388E3C;\
                        }";


                            QMessageBox msgBox;
                            msgBox.setWindowTitle("Runnig Program");
                            msgBox.setStyleSheet(styleSheet);
                            msgBox.setIcon(QMessageBox::Information);
                            msgBox.setText("Start Program Occured an error ! there is another program running on the board ");
                            msgBox.exec();

                }

        dashboard->show();
        this->hide();

    });
//    connect(sendButton, &QPushButton::clicked, [=]() {

////        DirectRun* run = new DirectRun();
////        QSet<QString> addedUartOptions;
////        QSet<QString> addedI2COptions;
////        QSet<QString> addedSPIOptions;
////        QSet<QString> addedADCOptions;
////        QSet<QString> addedDACOptions;
////        QSet<QString> addedGPIOOptions;
////        QSet<QString> addedTIMEROptions;


////            // Parcourir chaque élément sélectionné
////            for (int i = 0; i < Dashboard::selectedUartOptionsStatic.size(); i++) {
////                QString uartOption = Dashboard::selectedUartOptionsStatic.at(i);
////                if (!addedUartOptions.contains(uartOption)) {
////                      run->addActionToMenu("&UART", uartOption);
////                      addedUartOptions.insert(uartOption);


////                       }




////            }






////            for (int i = 0; i < Dashboard::selectedI2COptionsStatic.size(); i++) {
////                QString I2COption = Dashboard::selectedI2COptionsStatic.at(i);
////                // Vérifier si l'élément a déjà été ajouté pour I2C
////                      if (!addedI2COptions.contains(I2COption)) {
////                          run->addActionToMenu("&I2C", I2COption);
////                          addedI2COptions.insert(I2COption);
////                      }
////            }
////            for (int i = 0; i < Dashboard::selectedSPIOptionsStatic.size(); i++) {
////                QString SPIOption = Dashboard::selectedSPIOptionsStatic.at(i);
////                      if (!addedSPIOptions.contains(SPIOption)) {
////                          run->addActionToMenu("&SPI", SPIOption);
////                          addedSPIOptions.insert(SPIOption);
////                      }
////            }

////            for (int i = 0; i < Dashboard::selectedADCOptionsStatic.size(); i++) {
////                QString ADCOption = Dashboard::selectedADCOptionsStatic.at(i);
////                if (!addedADCOptions.contains(ADCOption)) {
////                   run->addActionToMenu("&ADC", ADCOption);
////                    addedADCOptions.insert(ADCOption);
////                }

////            }

////            for (int i = 0; i < Dashboard::selectedDACOptionsStatic.size(); i++) {
////                QString DACOption = Dashboard::selectedDACOptionsStatic.at(i);
////                if (!addedDACOptions.contains(DACOption)) {
////                   run->addActionToMenu("&DAC", DACOption);
////                    addedDACOptions.insert(DACOption);
////                }
////            }

////            for (int i = 0; i < Dashboard::selectedGPIOOptionsStatic.size(); i++) {
////                QString GPIOOption = Dashboard::selectedGPIOOptionsStatic.at(i);
////                if (!addedGPIOOptions.contains(GPIOOption)) {
////                   run->addActionToMenu("&GPIO", GPIOOption);
////                    addedGPIOOptions.insert(GPIOOption);
////                }
////            }

////            for (int i = 0; i < Dashboard::selectedTIMEROptionsStatic.size(); i++) {
////                QString TIMEROption = Dashboard::selectedTIMEROptionsStatic.at(i);
////                if (!addedTIMEROptions.contains(TIMEROption)) {
////                  run->addActionToMenu("&Frequency Mesure", TIMEROption);
////                    addedTIMEROptions.insert(TIMEROption);
////                }

////            }



//        run->show();
//        this->hide();



//    });

    QMenu* menu = new QMenu("Menu", this);


    connect(sendButton, &QPushButton::clicked, this, &ConfigChoice::handleLoadConfigButton);

}

void ConfigChoice::handleLoadConfigButton()
{
checkGroupAndAddSubMenu();
//QString program = "C:/Program Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI.exe"; // Chemin vers le programme cubeprogrammer

////        // Commande pour l'upload du fichier
////        QStringList uploadArguments;
////        uploadArguments << "-c" << "port=swd" << "--upload" << "0x08000000" << "128000" << "C:/Users/nawledbr/Desktop/testBins/read.bin";
////        QProcess::startDetached(program, uploadArguments);

//// Commande pour l'écriture du fichier
//QStringList writeArguments;
//writeArguments << "-c" << "port=swd" << "-w" << "C:/Users/nawledbr/Desktop/testBins/read.bin" << "0x08000000";
//QProcess::startDetached(program, writeArguments);

//// Commande pour démarrer l'exécution
//QStringList startArguments;
//startArguments << "-c" << "port=swd" << "--start" << "0x08000000";
//QProcess::startDetached(program, startArguments);
//QString program = "C:/Program Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI.exe"; // Chemin vers le programme cubeprogrammer

//QStringList writeArguments;
//writeArguments << "-c" << "port=swd" << "-w" << "C:/Users/nawledbr/Desktop/testBins/read.bin" << "0x08000000";
//QProcess writeProcess;
//writeProcess.startDetached(program, writeArguments);
//writeProcess.waitForFinished(-1);

//// Vérifier si la commande s'est terminée avec succès
//if (writeProcess.exitStatus() == QProcess::NormalExit && writeProcess.exitCode() == 0)
//{
//// Commande pour démarrer l'exécution
//QStringList startArguments;
//startArguments << "-c" << "port=swd" << "--start" << "0x08000000";
//QProcess startProcess;
//startProcess.startDetached(program, startArguments);
//startProcess.waitForFinished(-1);

//}

}

void ConfigChoice::checkGroupAndAddSubMenu()
{
    QSettings settings("UARTConfig.txt", QSettings::IniFormat); // Spécifiez le nom de votre fichier de configuration ici
    QSettings settingsSPI("SPIConfig.txt", QSettings::IniFormat); // Spécifiez le nom de votre fichier de configuration ici
    QSettings settingsADC("ADCConfig.txt", QSettings::IniFormat); // Spécifiez le nom de votre fichier de configuration ici
    QSettings settingsDAC("DACConfig.txt", QSettings::IniFormat); // Spécifiez le nom de votre fichier de configuration ici
    QSettings settingsI2C("I2CConfig.txt", QSettings::IniFormat); // Spécifiez le nom de votre fichier de configuration ici
    QSettings settingsTIM("FrequencyMesureConfig.txt", QSettings::IniFormat); // Spécifiez le nom de votre fichier de configuration ici
    QSettings settingsGPIO("GPIOConfig.txt", QSettings::IniFormat); // Spécifiez le nom de votre fichier de configuration ici

    DirectRun* run = new DirectRun();
    QStringList groupNames = settings.childGroups(); // Récupère la liste des noms de groupes dans le fichier
    QStringList groupNamesSPI = settingsSPI.childGroups(); // Récupère la liste des noms de groupes dans le fichier
    QStringList groupNamesADC = settingsADC.childGroups(); // Récupère la liste des noms de groupes dans le fichier
    QStringList groupNamesDAC= settingsDAC.childGroups(); // Récupère la liste des noms de groupes dans le fichier
    QStringList groupNamesI2C = settingsI2C.childGroups(); // Récupère la liste des noms de groupes dans le fichier
    QStringList groupNamesTIM = settingsTIM.childGroups(); // Récupère la liste des noms de groupes dans le fichier
    QStringList groupNamesGPIO = settingsGPIO.childGroups(); // Récupère la liste des noms de groupes dans le fichier

    QStringList validGroups;
    QStringList validGroupsSPI;
    QStringList validGroupsADC;
    QStringList validGroupsDAC;
    QStringList validGroupsI2C;
    QStringList validGroupsTIM;
    QStringList validGroupsGPIO;



    /***************************LOAD UART UI*********************************/


    bool hasValuesUART = false; // Variable pour vérifier si UART a des valeurs
    bool hasValuesSPI = false; // Variable pour vérifier si SPI a des valeurs
    bool hasValuesADC = false; // Variable pour vérifier si SPI a des valeurs
    bool hasValuesDAC = false; // Variable pour vérifier si SPI a des valeurs
    bool hasValuesI2C = false; // Variable pour vérifier si SPI a des valeurs
    bool hasValuesTIM = false; // Variable pour vérifier si SPI a des valeurs
    bool hasValuesGPIO = false; // Variable pour vérifier si SPI a des valeurs




    foreach (const QString& groupName, groupNames)
    {
    settings.beginGroup(groupName); // Démarre le groupe spécifié dans le fichier de configuration

    QStringList keys = settings.childKeys(); // Récupère les clés du groupe

    bool hasAllValues = false;

    for (const QString &key : keys) {
    if (key!="Date"){
    if (!settings.value(key).toString().isEmpty()) {
    hasAllValues = true;
    hasValuesUART = true; // Une valeur est présente pour UART

    break;
    }
    }
    }

    settings.endGroup(); // Termine le groupe spécifié dans le fichier de configuration

    if (hasAllValues)
    {
    validGroups.append(groupName);
    }
    }

    foreach (const QString& groupName, validGroups)
    {
    // Ajoute un sous-menu avec le nom du groupe au menu existant
        run->addActionToMenu("&UART", groupName);

        run->show();
        this->hide();

    }

//    QStringList cles = settings.childKeys();

//    // Vérifier s'il y a des valeurs pour les clés du groupe UART
//    bool valeursExistantes = false;
//    for (const QString &cle : cles) {
//    if (!settings.value(cle).toString().isEmpty()) {
//    valeursExistantes = true;
//    break;
//    }
//    }

//    // Si des valeurs existent, ajouter le nom du groupe au sous-menu
//    if (valeursExistantes) {
//            run->addActionToMenu("&UART", groupName);
//    }

// }
    /***************************LOAD SPI UI*********************************/



    foreach (const QString& groupNameSPI, groupNamesSPI)
    {
    settingsSPI.beginGroup(groupNameSPI); // Démarre le groupe spécifié dans le fichier de configuration

    QStringList keysSPI = settingsSPI.childKeys(); // Récupère les clés du groupe

    bool hasAllValuesSPI = false;

    for (const QString &key : keysSPI)
    {
    if (key!="Date"){

    if (!settingsSPI.value(key).toString().isEmpty())
    {
    // La clé n'a pas de valeur dans le groupe
    hasAllValuesSPI = true;
    hasValuesSPI = true; // Une valeur est présente pour SPI

    break;
    }
    }
    }
    settingsSPI.endGroup(); // Termine le groupe spécifié dans le fichier de configuration


    if (hasAllValuesSPI)
    {
    validGroupsSPI.append(groupNameSPI);
    }
    }

    foreach (const QString& groupNameSPI, validGroupsSPI)
    {
    // Ajoute un sous-menu avec le nom du groupe au menu existant
        run->addActionToMenu("&SPI", groupNameSPI);

        run->show();
        this->hide();

    }




    /***************************LOAD ADC UI*********************************/




    foreach (const QString& groupNameADC, groupNamesADC)
    {
    settingsADC.beginGroup(groupNameADC); // Démarre le groupe spécifié dans le fichier de configuration

    QStringList keysADC = settingsADC.childKeys(); // Récupère les clés du groupe

    bool hasAllValuesADC = false;

    for (const QString &key : keysADC)
    {
    if(key!="Date" && key!="Scan"){
    if (!settingsADC.value(key).toString().isEmpty())
    {
    // La clé n'a pas de valeur dans le groupe
    hasAllValuesADC = true;
    hasValuesADC = true;
    break;
    }
    }
    }

    settingsADC.endGroup(); // Termine le groupe spécifié dans le fichier de configuration

    if (hasAllValuesADC)
    {
    validGroupsADC.append(groupNameADC);
    }
    }

    foreach (const QString& groupNameADC, validGroupsADC)
    {
    // Ajoute un sous-menu avec le nom du groupe au menu existant
        run->addActionToMenu("&ADC", groupNameADC);

        run->show();
        this->hide();

    }




    /***************************LOAD DAC UI*********************************/





    foreach (const QString& groupNameDAC, groupNamesDAC)
    {
    settingsDAC.beginGroup(groupNameDAC); // Démarre le groupe spécifié dans le fichier de configuration

    QStringList keysDAC = settingsDAC.childKeys(); // Récupère les clés du groupe

    bool hasAllValuesDAC = false;

    for (const QString &key : keysDAC)
    {
    if(key!="Date"){
    if (!settingsDAC.value(key).toString().isEmpty())
    {
    // La clé n'a pas de valeur dans le groupe
    hasAllValuesDAC = true;
    hasValuesDAC = true;
    break;
    }
    }
    }
    settingsDAC.endGroup(); // Termine le groupe spécifié dans le fichier de configuration

    if (hasAllValuesDAC)
    {
    validGroupsDAC.append(groupNameDAC);
    }
    }

    foreach (const QString& groupNameDAC, validGroupsDAC)
    {
    // Ajoute un sous-menu avec le nom du groupe au menu existant
        run->addActionToMenu("&DAC", groupNameDAC);

        run->show();
        this->hide();

    }


    /***************************LOAD I2C UI*********************************/



    foreach (const QString& groupNameI2C, groupNamesI2C)
    {
    settingsI2C.beginGroup(groupNameI2C); // Démarre le groupe spécifié dans le fichier de configuration

    QStringList keysI2C = settingsI2C.childKeys(); // Récupère les clés du groupe

    bool hasAllValuesI2C = false;

    for (const QString &key : keysI2C)
    {
        if(key!="Date" && key!="AddressMasks" && key!="GeneralCallMode"){
    if (!settingsI2C.value(key).toString().isEmpty())
    {
    // La clé n'a pas de valeur dans le groupe
    hasAllValuesI2C = true;
    hasValuesI2C = true;
    break;
    }
    }
    }

    settingsI2C.endGroup(); // Termine le groupe spécifié dans le fichier de configuration

    if (hasAllValuesI2C)
    {
    validGroupsI2C.append(groupNameI2C);
    }
    }

    foreach (const QString& groupNameI2C, validGroupsI2C)
    {
    // Ajoute un sous-menu avec le nom du groupe au menu existant
        run->addActionToMenu("&I2C", groupNameI2C);

        run->show();
        this->hide();

    }




    /***************************LOAD GPIO UI*********************************/





    foreach (const QString& groupNameGPIO, groupNamesGPIO)
    {
    settingsGPIO.beginGroup(groupNameGPIO); // Démarre le groupe spécifié dans le fichier de configuration

    QStringList keysGPIO = settingsGPIO.childKeys(); // Récupère les clés du groupe

    bool hasAllValuesGPIO = false;

    for (const QString &key : keysGPIO)
    {
    if(key!="Date"){

        if (!settingsGPIO.value(key).toString().isEmpty())
        {
            // La clé n'a pas de valeur dans le groupe
            hasAllValuesGPIO = true;
            hasValuesGPIO = true;
            break;
        }
    }
}
    settingsGPIO.endGroup(); // Termine le groupe spécifié dans le fichier de configuration

    if (hasAllValuesGPIO)
    {
    validGroupsGPIO.append(groupNameGPIO);
    }
    }

    foreach (const QString& groupNameGPIO, validGroupsGPIO)
    {
    // Ajoute un sous-menu avec le nom du groupe au menu existant
        run->addActionToMenu("&GPIO", groupNameGPIO);

        run->show();
        this->hide();

    }



    /***************************LOAD FREQUENCY MESURE  UI*********************************/


    foreach (const QString& groupNameTIM, groupNamesTIM)
    {
    settingsTIM.beginGroup(groupNameTIM); // Démarre le groupe spécifié dans le fichier de configuration

    QStringList keysTIM = settingsTIM.childKeys(); // Récupère les clés du groupe

    bool hasAllValuesTIM = false;

    for (const QString &key : keysTIM)
    {
        if(key!="Date"){

            if (!settingsTIM.value(key).toString().isEmpty())
    {
    // La clé n'a pas de valeur dans le groupe
    hasAllValuesTIM = true;
     hasValuesTIM = true;
    break;
    }
    }
    }

    settingsTIM.endGroup(); // Termine le groupe spécifié dans le fichier de configuration

    if (hasAllValuesTIM)
    {
    validGroupsTIM.append(groupNameTIM);
    }
    }

    foreach (const QString& groupNameTIM, validGroupsTIM)
    {
    // Ajoute un sous-menu avec le nom du groupe au menu existant
        run->addActionToMenu("&Frequency Mesure", groupNameTIM);

        run->show();
        this->hide();

    }


    if (!hasValuesUART && !hasValuesSPI && !hasValuesADC && !hasValuesDAC && !hasValuesI2C && !hasValuesGPIO && !hasValuesTIM)
    {
    // Affiche le message box si aucune valeur n'est présente pour UART et SPI
        /******************************* getting notification ***************************************/



        QString styleSheet = "\
            QMessageBox {\
                background-color: #D3D3D3;\
                color: #263238;\
                font-family:Fantasy ;\
                font-size: 12px;\
            }\
            \
            QMessageBox QLabel {\
                color: #000000	;\
            }\
            \
            QMessageBox QPushButton {\
                background-color: #4CAF50;\
                border: 1px solid #388E3C;\
                color: #FFFFFF;\
                padding: 5px;\
                min-width: 70px;\
            }\
            \
            QMessageBox QPushButton:hover {\
                background-color: #388E3C;\
            }";


                QMessageBox msgBox;
                msgBox.setWindowTitle("Loaded Configurations");
                msgBox.setStyleSheet(styleSheet);
                msgBox.setIcon(QMessageBox::Information);
                msgBox.setText("There is no previous configurations !");
                msgBox.exec();

    }





}
void ConfigChoice::progressDelay(int milliseconds) {
QElapsedTimer timer;
timer.start();

while (timer.elapsed() < milliseconds) {
QCoreApplication::processEvents();
}
}

ConfigChoice::~ConfigChoice()
{
    delete ui;
}
