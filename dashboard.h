#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include<QFormLayout>
#include<QtSerialPort/QSerialPortInfo>
#


namespace Ui {
class Dashboard;
}

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();
private slots :
    void openWidget()
    {
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

                // Create Layout form
                QFormLayout* layout = new QFormLayout(this);

               // Create the baud rate label and combo box

               QLabel* baudRateLabel = new QLabel(tr("Baud Rate"), this);
               QComboBox* baudRateComboBox = new QComboBox(this);
               QList<qint32> baudRates = info.standardBaudRates(); // What baudrates does my computer support ?
               QList<QString> stringBaudRates;
                for(int i = 0 ; i < baudRates.size() ; i++){
                    stringBaudRates.append(QString::number(baudRates.at(i)));
                }
               baudRateComboBox->addItems(stringBaudRates);
               baudRateComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
               // Set the minimum width to 100 pixels
               baudRateComboBox->setMinimumWidth(10);
               baudRateLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               baudRateComboBox->setStyleSheet("font: 15px; color: green; background-color: white;");


               layout->addRow(baudRateLabel, baudRateComboBox);

               // Create the parity label and combo box

               QLabel* parityLabel = new QLabel(tr("Parity"), this);
               QComboBox* parityComboBox = new QComboBox(this);
               parityComboBox->addItems(QStringList() << "None" << "Odd" << "Even");
               parityLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               parityComboBox->setStyleSheet("font: 15px; color: green; background-color: white;");

               layout->addRow(parityLabel, parityComboBox);


               // Create the stop bits label and combo box

               QLabel* stopBitsLabel = new QLabel(tr("Stop Bits"), this);
               QComboBox* stopBitsComboBox = new QComboBox(this);
               stopBitsComboBox->addItems(QStringList() << "1" << "1.5" << "2");
               stopBitsLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               stopBitsComboBox->setStyleSheet("font: 15px; color: green; background-color: white;");

               layout->addRow(stopBitsLabel, stopBitsComboBox);


               // Create the data bits label and combo box

               QLabel* DataBitsLabel = new QLabel(tr("Data Bits"), this);
               QComboBox* DataBitsComboBox = new QComboBox(this);
               DataBitsComboBox->addItems(QStringList() << "5" << "6" << "7" << "8");
               DataBitsLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               DataBitsComboBox->setStyleSheet("font: 15px; color: green; background-color: white;");

               // Create the flow control label and combo box

               layout->addRow(DataBitsLabel, DataBitsComboBox);
               QLabel* FlowControlLabel = new QLabel(tr("Flow Control"), this);
               QComboBox* FlowControlComboBox = new QComboBox(this);
               FlowControlComboBox->addItems(QStringList() << "No Flow Control" << "Hardware Flow Control" << "Software Flow Control " );
               FlowControlLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FlowControlComboBox->setStyleSheet("font: 15px; color: green; background-color: white;");

               layout->addRow(FlowControlLabel, FlowControlComboBox);

               // Create the vertical layout and add the form layout to it
               QVBoxLayout* verticalLayout = new QVBoxLayout(this);
               verticalLayout->addStretch();
               verticalLayout->addLayout(layout);
               verticalLayout->addStretch();

               // Create the horizontal layout and add the vertical layout to it
               QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
               horizontalLayout->addStretch();
               horizontalLayout->addLayout(verticalLayout);
               horizontalLayout->addStretch();

               // Set the widget layout to the horizontal layout

               widget->setLayout(horizontalLayout);








    }
private:
    Ui::Dashboard *ui;
    QSerialPortInfo info;

};

#endif // DASHBOARD_H
