#ifndef DASH_H
#define DASH_H

#include <QDialog>

namespace Ui {
class Dash;
}

class Dash : public QDialog
{
    Q_OBJECT

public:
    explicit Dash(QWidget *parent = nullptr);
    ~Dash();

private slots:
    void on_UARTbtn_clicked();

private:
    Ui::Dash *ui;
};

#endif // DASH_H
