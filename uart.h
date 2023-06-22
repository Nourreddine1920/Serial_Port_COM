#ifndef UART_H
#define UART_H

#include <QMainWindow>
#include<QtSerialPort/QSerialPortInfo>
#include<QtSerialPort/QSerialPort>
#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui { class Uart; }
QT_END_NAMESPACE

class Uart : public QMainWindow
{
    Q_OBJECT

public:
    Uart(QWidget *parent = nullptr);
    QSerialPort *getSerialPort() const;
     static Uart* getInstance();


    ~Uart();

private slots:
    void on_pushButton_clicked();

    void on_btnConnect_clicked();

    void on_btnDisconnect_clicked();

    void on_btnRefresh_clicked();

    void on_btnClear_clicked();

    void on_btnSendMsg_clicked();
    void recieveMessage();
    void openLinkedInUrl();
    void openFacebookUrl();
    void openInstagramUrl();
    void openUrl(const QString& url);
    void openGmail();

private:
    QLabel *statusLabel;

    Ui::Uart *ui;
    QSerialPortInfo info;
    QSerialPort *serialPort;
    QString code;
    int codeSize;
    QString buffer;
    static Uart* instance;


};
#endif // UART_H
