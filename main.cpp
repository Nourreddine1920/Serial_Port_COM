//#include "uart.h"
#include  "dash.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Uart w;
    Dash d;
    //w.show();
    d.show();
    return a.exec();
}
