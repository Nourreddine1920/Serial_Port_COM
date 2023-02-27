#ifndef STARTING_SCREEN_H
#define STARTING_SCREEN_H

#include <QMainWindow>
#include "uart.h"


namespace Ui {
class starting_screen;
}

class starting_screen : public QMainWindow
{
    Q_OBJECT

public:
    explicit starting_screen(QWidget *parent = nullptr);
    ~starting_screen();

private slots:
    void on_pushButton_startapplication_clicked();

private:
    Ui::starting_screen *ui;
    Uart *Uartscreen ;
};

#endif // STARTING_SCREEN_H
