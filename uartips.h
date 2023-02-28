#ifndef UARTIPS_H
#define UARTIPS_H

#include <QDialog>

namespace Ui {
class Uartips;
}

class Uartips : public QDialog
{
    Q_OBJECT

public:
    explicit Uartips(QWidget *parent = nullptr);
    ~Uartips();

private slots:
    void on_commandLinkButton_clicked();

    void on_btnStaticUART_clicked();

private:
    Ui::Uartips *ui;
};

#endif // UARTIPS_H
