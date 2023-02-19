//#include "uart.h"
#include  "dash.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Uart w;
    Dash d;
    d.setWindowIcon(QIcon("icon.png"));

    //w.show();
    d.show();
    return a.exec();
}
