#ifndef DASH_H
#define DASH_H

#include <QDialog>
#include <QStackedWidget>
#include <QLabel>
#include <QWidget>

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
    void openWidget()
    {
        QWidget *widget = new QWidget(this);
        //setCentralWidget(widget);
        QWidget::setWindowIconText("UART Configurations ");
        QLabel *label = new QLabel("Hello, world!", widget);


    }


private:
    Ui::Dash *ui;
    QStackedWidget *stackedWidget;
};

#endif // DASH_H
