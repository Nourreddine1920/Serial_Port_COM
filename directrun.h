#ifndef DIRECTRUN_H
#define DIRECTRUN_H

#include <QMainWindow>

namespace Ui {
class DirectRun;
}

class DirectRun : public QMainWindow
{
    Q_OBJECT

public:
    explicit DirectRun(QWidget *parent = nullptr);
    ~DirectRun();

private:
    Ui::DirectRun *ui;

public slots :
    void addActionToMenu(QString menuItem, QString actionName);

};

#endif // DIRECTRUN_H
