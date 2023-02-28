#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include<QFormLayout>
#include<QtSerialPort/QSerialPortInfo>
#include <QSpinBox>
#include <QLineEdit>
#include <QSpacerItem>




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
    void UARTConfig()
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
               baudRateComboBox->setStyleSheet("font: 15px; color: gray; background-color: white;");


               layout->addRow(baudRateLabel, baudRateComboBox);

               // Create the parity label and combo box

               QLabel* parityLabel = new QLabel(tr("Parity"), this);
               QComboBox* parityComboBox = new QComboBox(this);
               parityComboBox->addItems(QStringList() << "None" << "Odd" << "Even");
               parityLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               parityComboBox->setStyleSheet("font: 15px; color: gray; background-color: white;");

               layout->addRow(parityLabel, parityComboBox);


               // Create the stop bits label and combo box

               QLabel* stopBitsLabel = new QLabel(tr("Stop Bits"), this);
               QComboBox* stopBitsComboBox = new QComboBox(this);
               stopBitsComboBox->addItems(QStringList() << "1" << "1.5" << "2");
               stopBitsLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               stopBitsComboBox->setStyleSheet("font: 15px; color: gray; background-color: white;");

               layout->addRow(stopBitsLabel, stopBitsComboBox);


               // Create the data bits label and combo box

               QLabel* DataBitsLabel = new QLabel(tr("Data Bits"), this);
               QComboBox* DataBitsComboBox = new QComboBox(this);
               DataBitsComboBox->addItems(QStringList() << "5" << "6" << "7" << "8");
               DataBitsLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               DataBitsComboBox->setStyleSheet("font: 15px; color: gray; background-color: white;");

               // Create the flow control label and combo box

               layout->addRow(DataBitsLabel, DataBitsComboBox);
               QLabel* FlowControlLabel = new QLabel(tr("Flow Control"), this);
               QComboBox* FlowControlComboBox = new QComboBox(this);
               FlowControlComboBox->addItems(QStringList() << "No Flow Control" << "Hardware Flow Control" << "Software Flow Control " );
               FlowControlLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FlowControlComboBox->setStyleSheet("font: 15px; color: gray; background-color: white;");

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

    void SPIConfig (){
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

                // Create Layout form for SPI
                QFormLayout* layout = new QFormLayout(this);

               // Create the Model label and combo box

               QLabel* ModeLabel = new QLabel(tr("Mode"), this);
               QComboBox* ModeComboBox = new QComboBox(this);

               ModeComboBox->addItems(QStringList() << "Full-Duplex Master" << "Full-Duplex Slave" << "Half-Duplex Master " << "Half-Duplex Slave" );
               ModeComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
               // Set the minimum width to 100 pixels
               ModeComboBox->setMinimumWidth(10);
               ModeLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ModeComboBox->setStyleSheet("font: Arial 15px; color: gray; background-color: white;");


               layout->addRow(ModeLabel, ModeComboBox);

               // Create the NSS label and combo box

               QLabel* NSSLabel = new QLabel(tr("Hardware NSS Signal"), this);
               QComboBox* NSSComboBox = new QComboBox(this);
               NSSComboBox->addItems(QStringList() << "Disable" << "Hardware NSS Input Signal" << "Hardware NSS Output Signal");
               NSSLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               NSSComboBox->setStyleSheet("font:Arial 15px; color: gray; background-color: white;");

               layout->addRow(NSSLabel, NSSComboBox);


               // Create the Frame Format label and combo box

               QLabel* FrameFormatLabel = new QLabel(tr("Frame Format"), this);
               QComboBox* FrameFormatComboBox = new QComboBox(this);
               FrameFormatComboBox->addItems(QStringList() << "Motorola" << "Texas Instruments");
               FrameFormatLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FrameFormatComboBox->setStyleSheet("font: Arial 15px; color: gray; background-color: white;");

               layout->addRow(FrameFormatLabel, FrameFormatComboBox);


               // Create the data size label and combo box

               QLabel* DataSizeLabel = new QLabel(tr("Data Size"), this);
               QSpinBox* DataSizeSpinBox = new QSpinBox(this);
               DataSizeSpinBox->setMinimum(4);
               DataSizeSpinBox->setMaximum(32);

               DataSizeLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               DataSizeSpinBox->setStyleSheet("font:Arial 15px; color: gray; background-color: white;");
               layout->addRow(DataSizeLabel, DataSizeSpinBox);


               // Create the First Bit label and combo box

               QLabel* FirstBitLabel = new QLabel(tr("First Bit"), this);
               QComboBox* FirstBitComboBox = new QComboBox(this);
               FirstBitComboBox->addItems(QStringList() << "LSB" << "MSB"  );
               FirstBitLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FirstBitComboBox->setStyleSheet("font: Arial 15px; color: gray; background-color: white;");

               layout->addRow(FirstBitLabel, FirstBitComboBox);

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
    void I2CConfig (){
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

                // Create Layout form for I2C
                QFormLayout* layout = new QFormLayout(this);



               // Create the Custom Timing label and combo box

               QLabel* TimingLabel = new QLabel(tr("Custom Timing"), this);
               QComboBox* TimingComboBox = new QComboBox(this);

               TimingComboBox->addItems(QStringList() << "Enable" << "Disable");
               TimingComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
               // Set the minimum width to 100 pixels
               TimingComboBox->setMinimumWidth(10);
               TimingLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               TimingComboBox->setStyleSheet("font: Arial 15px; color: gray; background-color: white;");


               layout->addRow(TimingLabel, TimingComboBox);

               // Create the I2C Speed Mode label and combo box

               QLabel* SpeedLabel = new QLabel(tr("I2C Speed Mode"), this);
               QComboBox* SpeedComboBox = new QComboBox(this);
               SpeedComboBox->addItems(QStringList() << "Standart Mode" << "Fast Mode " << "Fast Mode Plus");
               SpeedLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               SpeedComboBox->setStyleSheet("font:Arial 15px; color: gray; background-color: white;");

               layout->addRow(SpeedLabel, SpeedComboBox);


               // Create the Speed Frequency label and combo box

               QLabel* FrequencyLabel = new QLabel(tr("Speed Frequency"), this);
               QComboBox* FrequencyComboBox = new QComboBox(this);
               FrequencyComboBox->addItems(QStringList() << "200 KHz" << "400 KHz " << "1 MHz");






               FrequencyLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FrequencyComboBox->setStyleSheet("font: Arial 15px; color: gray; background-color: white;");

               layout->addRow(FrequencyLabel, FrequencyComboBox);


               // Create the Rise Time label and combo box

               QLabel* RiseLabel = new QLabel(tr("Rise Time"), this);
               QSpinBox* RiseSpinBox = new QSpinBox(this);
               RiseSpinBox->setMinimum(20);
               RiseSpinBox->setMaximum(1000);

               RiseLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               RiseSpinBox->setStyleSheet("font:Arial 15px; color: gray; background-color: white;");
               layout->addRow(RiseLabel, RiseSpinBox);


               // Create the Fall Time label and combo box

               QLabel* FallLabel = new QLabel(tr("Fall Time"), this);
               QSpinBox* FallSpinBox = new QSpinBox(this);
               FallSpinBox->setMinimum(10);
               FallSpinBox->setMaximum(300);

               FallLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               FallSpinBox->setStyleSheet("font:Arial 15px; color: gray; background-color: white;");
               layout->addRow(FallLabel, FallSpinBox);


               // Create the Coefficient of digital converter  label and combo box

               QLabel* ConverterLabel = new QLabel(tr("Coefficient of Digital Converter"), this);
               QSpinBox* ConverterSpinBox = new QSpinBox(this);
               ConverterSpinBox->setMinimum(0);
               ConverterSpinBox->setMaximum(16);

               ConverterLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ConverterSpinBox->setStyleSheet("font:Arial 15px; color: gray; background-color: white;");
               layout->addRow(ConverterLabel, ConverterSpinBox);

               // Create the Analog Filter label and combo box

               QLabel* AnalogFilterLabel = new QLabel(tr("Analog Filter"), this);
               QComboBox* AnalogFilterComboBox = new QComboBox(this);
               AnalogFilterComboBox->addItems(QStringList() << "Enabled" << "Disabled"  );
               AnalogFilterLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               AnalogFilterComboBox->setStyleSheet("font: Arial 15px; color: gray; background-color: white;");

               //QSpacerItem* spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);


               layout->addRow(AnalogFilterLabel, AnalogFilterComboBox);
               layout->setContentsMargins(0, 0, 0, 0);
               layout->setSpacing(30);

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
               widget->setGeometry(500, 500, 600, 500);


    }

private:
    Ui::Dashboard *ui;
    QSerialPortInfo info;

};

#endif // DASHBOARD_H
