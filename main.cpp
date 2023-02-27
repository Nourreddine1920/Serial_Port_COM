#include "starting_screen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    starting_screen w ;
    w.show();
    return a.exec();
}
