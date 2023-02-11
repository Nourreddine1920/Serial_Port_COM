#ifndef UART_H
#define UART_H

#include <QMainWindow>
#include<QtSerialPort/QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class Uart; }
QT_END_NAMESPACE

class Uart : public QMainWindow
{
    Q_OBJECT

public:
    Uart(QWidget *parent = nullptr);
    ~Uart();

private:
    Ui::Uart *ui;
    QSerialPortInfo info;
};
#endif // UART_H
