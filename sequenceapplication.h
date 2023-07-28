#ifndef SEQUENCEAPPLICATION_H
#define SEQUENCEAPPLICATION_H

#include <QMainWindow>
#include <QListWidget>
#include <QTextBrowser>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QRadioButton>
#include <QComboBox>
#include <QSpinBox>
#include "uart.h"
#include <QSerialPort>
#include <QDate>
#include <QTime>
#include <QFontDatabase>
#include<QFont>

namespace Ui {
class sequenceApplication;
}

class sequenceApplication : public QMainWindow
{
    Q_OBJECT

public:
    explicit sequenceApplication(QWidget *parent = nullptr);
    QListWidget* selectedItemsListWidget;
    QByteArray packet;
    QByteArray packet1;
    QByteArray packet2;
    QByteArray packet3;
    QByteArray packet4;
    QByteArray packet5;
    QByteArray packet6;

    QByteArray Message;
    QString message;
    QLineEdit* deviceAddressLineEdit;
    QLineEdit* deviceAddressLineEditI2C;
    QLineEdit* deviceAddressLineEditUART;
    QLineEdit* deviceAddressLineEditSPI;
    QLineEdit* deviceAddressLineEditDAC;
    QLineEdit* deviceAddressLineEditTIMER;

    ~sequenceApplication();

public slots:
    void returnDashboard();
    void addActionToMenu(QString menuItem, QString actionName);
    void onSubMenuSelected();

private:
    Ui::sequenceApplication *ui;






private slots :



    void showADCexec();
    void showGPIOexec();
    void showI2Cexec();
    void showDACexec();
    void showTIMERexec();
    void showUARTexec();
    void showSPIexec();


    void sendSequenceframe();
    void on_pushButton_clicked();
};

#endif // SEQUENCEAPPLICATION_H
