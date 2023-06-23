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
};

#endif // SEQUENCEAPPLICATION_H
