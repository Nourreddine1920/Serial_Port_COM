#ifndef RUNMODE_H
#define RUNMODE_H

#include <QMainWindow>

namespace Ui {
class Runmode;
}

class Runmode : public QMainWindow
{
    Q_OBJECT

public:
    explicit Runmode(QWidget *parent = nullptr);
    ~Runmode();

private:
    Ui::Runmode *ui;


public slots :
    void returnDashboard();
    void addActionToMenu(QString menuItem, QString actionName);


};

#endif // RUNMODE_H
