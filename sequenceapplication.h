#ifndef SEQUENCEAPPLICATION_H
#define SEQUENCEAPPLICATION_H

#include <QMainWindow>

namespace Ui {
class sequenceApplication;
}

class sequenceApplication : public QMainWindow
{
    Q_OBJECT

public:
    explicit sequenceApplication(QWidget *parent = nullptr);
    ~sequenceApplication();

public slots:
    void returnDashboard();
    void addActionToMenu(QString menuItem, QString actionName);
private:
    Ui::sequenceApplication *ui;
};

#endif // SEQUENCEAPPLICATION_H
