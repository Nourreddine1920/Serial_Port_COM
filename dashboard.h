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
    void ADCConfig (){
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

                // Create Layout form for ADC
                QFormLayout* layout = new QFormLayout(this);



               // Create the Mode label and combo box

               QLabel* ChannelLabel = new QLabel(tr("Select Channel"), this);
               QComboBox* ChannelComboBox = new QComboBox(this);

               ChannelComboBox->addItems(QStringList() << "IN2" << "IN3" << "IN4" <<"IN5" << "IN6" << "IN7" << "IN8" << "IN9" << "IN10" << "IN11" << "IN14" << "IN15" << "IN16" << "IN17" <<"IN18" <<"IN19");
               // Create the second QComboBox and add it as an item to the first combo box
               QComboBox* ChannelSelectionMode = new QComboBox();
               ChannelSelectionMode->addItems(QStringList() << "Option 1" << "Option 2" << "Option 3");
               //ChannelComboBox->addItem("New Selection", QVariant::fromValue(ChannelSelectionMode));

               ChannelComboBox->setItemData(0, QVariant::fromValue(ChannelSelectionMode), Qt::UserRole);

               ChannelComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
               // Set the minimum width to 100 pixels
               ChannelComboBox->setMinimumWidth(10);
               ChannelLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ChannelComboBox->setStyleSheet("font: Arial 15px; color: gray; background-color: white;");


               layout->addRow(ChannelLabel, ChannelComboBox);

               // Create the Resolution Bit label and combo box

               QLabel* ResolutionLabel = new QLabel(tr("ADC Resolution Bit"), this);
               QComboBox* ResolutionComboBox = new QComboBox(this);
               ResolutionComboBox->addItems(QStringList() << "ADC 8-Bit Resolution" << "ADC 10-Bit Resolution" << "ADC 12-Bit Resolution" << "ADC 14-Bit Resolution" << "ADC 16-Bit Resolution"<< "ADC 12-Bit Optimized Resolution" << "ADC 14-Bit Optimized Resolution"  );
               ResolutionLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ResolutionComboBox->setStyleSheet("font:Arial 15px; color: gray; background-color: white;");

               layout->addRow(ResolutionLabel, ResolutionComboBox);


               // Create the Conversion Modes =====  "Scan Mode"  Frequency label and combo box

               QLabel* ScanLabel = new QLabel(tr("Scan Conversion Mode"), this);
               QComboBox* ScanComboBox = new QComboBox(this);
               ScanComboBox->addItems(QStringList() << "Disabled" );
               ScanLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ScanComboBox->setStyleSheet("font: Arial 15px; color: gray; background-color: white;");

               layout->addRow(ScanLabel, ScanComboBox);


                // Create the Conversion Modes =====  "Continuous Mode"  Frequency label and combo box

               QLabel* ContinuousLabel = new QLabel(tr("Continuous Conversion Mode"), this);
               QComboBox* ContinuousComboBox = new QComboBox(this);


               ContinuousComboBox->addItems(QStringList() << "Enabled" << "Disabled");

               ContinuousLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ContinuousComboBox->setStyleSheet("font:Arial 15px; color: gray; background-color: white;");
               layout->addRow(ContinuousLabel, ContinuousComboBox);


               // Create the Conversion Modes =====  "Discontinuous Mode"  label and combo box

              QLabel* DiscontinuousLabel = new QLabel(tr("Discontinuous Conversion Mode"), this);
              QComboBox* DiscontinuousComboBox = new QComboBox(this);


              DiscontinuousComboBox->addItems(QStringList() << "Enabled" << "Disabled");

              DiscontinuousLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
              DiscontinuousComboBox->setStyleSheet("font:Arial 15px; color: gray; background-color: white;");
              layout->addRow(DiscontinuousLabel, DiscontinuousComboBox);


              // Create the End Conversion Mode label and combo box

             QLabel* EndConversionLabel = new QLabel(tr("End of Conversion Mode"), this);
             QComboBox* EndConversionComboBox = new QComboBox(this);


             EndConversionComboBox->addItems(QStringList() << "End of Single Conversion" << "End of sequence Conversion");

             EndConversionLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
             EndConversionComboBox->setStyleSheet("font:Arial 15px; color: gray; background-color: white;");
             layout->addRow(EndConversionLabel, EndConversionComboBox);


             // Create the Overrun Behavior Mode label and combo box

            QLabel* BehaviorLabel = new QLabel(tr("Overrun Behavior"), this);
            QComboBox* BehaviorComboBox = new QComboBox(this);


            BehaviorComboBox->addItems(QStringList() << "Overrun Data Preserved" << "Overrun Data Overwritten");

            BehaviorLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
            BehaviorComboBox->setStyleSheet("font:Arial 15px; color: gray; background-color: white;");
            layout->addRow(BehaviorLabel, BehaviorComboBox);



               // Create the Left Bit label and combo box

               QLabel* LeftBitLabel = new QLabel(tr("Left Bit Shift"), this);
               QComboBox* LeftBitComboBox = new QComboBox(this);
               LeftBitComboBox->addItems(QStringList() << "No Bit Shift" << "1 Bit Shift" << "2 Bit Shift"<<  "3 Bit Shift" << "4 Bit Shift" <<"5 Bit Shift" << "6 Bit Shift" <<"7 Bit Shift" <<"8 Bit Shift" <<"9 Bit Shift" <<"10 Bit Shift" <<"11 Bit Shift" << "12 Bit Shift" <<"13 Bit Shift" <<"14 Bit Shift" << "15 Bit Shift" );
               LeftBitLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               LeftBitComboBox->setStyleSheet("font: Arial 15px; color: gray; background-color: white;");

               //QSpacerItem* spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);


               layout->addRow(LeftBitLabel, LeftBitComboBox);
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
    void DACConfig (){
        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);

                // Create Layout form for DAC
                QFormLayout* layout = new QFormLayout(this);



               // Create the OUT1 Connected to channel and combo box

               QLabel* ChannelLabel = new QLabel(tr("OUT1 Connected to "), this);
               QComboBox* ChannelComboBox = new QComboBox(this);

               ChannelComboBox->addItems(QStringList() << "Disable" << "Only External Pin" << "Only on Chip Analog Peripherals" <<"Both external Pin and on Chip Analog" );


               ChannelLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               ChannelComboBox->setStyleSheet("font: Arial 15px; color: gray; background-color: white;");


               layout->addRow(ChannelLabel, ChannelComboBox);
               layout->setContentsMargins(0, 0, 0, 0);
               layout->setSpacing(30);

               connect(ChannelComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                       this, &Dashboard::ShowingDACConfigs);




               // Create the OUT1 Connected to channel and combo box

               QLabel* Channel2Label = new QLabel(tr("OUT2 Connected to "), this);
               QComboBox* Channel2ComboBox = new QComboBox(this);

               Channel2ComboBox->addItems(QStringList() << "Disable" << "Only External Pin" << "Only on Chip Analog Peripherals" <<"Both external Pin and on Chip Analog" );


               Channel2Label->setStyleSheet("font: bold 15px; color: black; background-color: white;");
               Channel2ComboBox->setStyleSheet("font: Arial 15px; color: gray; background-color: white;");


               layout->addRow(Channel2Label, Channel2ComboBox);
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


    // Layout Form the DAC Configuration

    void ShowingDACConfigs(){

        QWidget *widget = new QWidget(this);
        setCentralWidget(widget);


        QFormLayout* layout = new QFormLayout(this);

        // --------------Mode selected for the OUT1--------------------//

        QLabel* ModeLabel = new QLabel(tr("Mode selected"), this);
        QComboBox* ModeComboBox = new QComboBox(this);

        ModeComboBox->addItems(QStringList() << "Normal Mode" << "Sample and Hold Mode" );


        ModeLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        ModeComboBox->setStyleSheet("font: Arial 15px; color: gray; background-color: white;");


        layout->addRow(ModeLabel, ModeComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);

        // --------------Output Buffer for the OUT1--------------------//

        QLabel* BufferLabel = new QLabel(tr(" Output Buffer "), this);
        QComboBox* BufferComboBox = new QComboBox(this);

        BufferComboBox->addItems(QStringList() << "Enable" << "Disable" );


        BufferLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        BufferComboBox->setStyleSheet("font: Arial 15px; color: gray; background-color: white;");


        layout->addRow(BufferLabel, BufferComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);


        // --------------Trigger for the OUT1--------------------//

        QLabel* TriggerLabel = new QLabel(tr(" Trigger "), this);
        QComboBox* TriggerComboBox = new QComboBox(this);

        TriggerComboBox->addItems(QStringList() << "None" << "TIMER1 Trigger OUT event " << "TIMER1 Trigger OUT event " << "TIMER1 Trigger OUT event " << "TIMER2 Trigger OUT event " << "TIMER4 Trigger OUT event " << "TIMER5 Trigger OUT event " << "TIMER6 Trigger OUT event " << "TIMER7 Trigger OUT event " << "TIMER8 Trigger OUT event " << "TIMER15 Trigger OUT event" << "LPTIMER1 Trigger OUT event" << "LPTIMER2 Trigger OUT event" << "Software Trigger");


        TriggerLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        TriggerComboBox->setStyleSheet("font: Arial 15px; color: gray; background-color: white;");


        layout->addRow(TriggerLabel, TriggerComboBox);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(30);


        // --------------Trimming for the OUT1--------------------//

        QLabel* TrimmingLabel = new QLabel(tr(" Trimming "), this);
        QComboBox* TrimmingComboBox = new QComboBox(this);

        TrimmingComboBox->addItems(QStringList() << "Factory Trimming" << "User Trimming" );


        TrimmingLabel->setStyleSheet("font: bold 15px; color: black; background-color: white;");
        TrimmingComboBox->setStyleSheet("font: Arial 15px; color: gray; background-color: white;");


        layout->addRow(TrimmingLabel, TrimmingComboBox);
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
