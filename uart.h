#ifndef UART_H
#define UART_H

#include <QMainWindow>
#include<QtSerialPort/QSerialPortInfo>
#include<QtSerialPort/QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class Uart; }
QT_END_NAMESPACE

class Uart : public QMainWindow
{
    Q_OBJECT

public:
    Uart(QWidget *parent = nullptr);
    ~Uart();

private slots:
    void on_pushButton_clicked();

    void on_btnConnect_clicked();

    void on_btnDisconnect_clicked();

    void on_btnRefresh_clicked();

    void on_btnClear_clicked();

    void on_btnSendMsg_clicked();
    void recieveMessage();

private:
    Ui::Uart *ui;
    QSerialPortInfo info;
    QSerialPort serialPort;
    QString code;
    int codeSize;
    QString buffer;


};
#endif // UART_H
