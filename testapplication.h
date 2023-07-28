#ifndef TESTAPPLICATION_H
#define TESTAPPLICATION_H

#include <QMainWindow>

namespace Ui {
class testApplication;
}

class testApplication : public QMainWindow
{
    Q_OBJECT

public:
    explicit testApplication(QWidget *parent = nullptr);
    ~testApplication();

public slots:
private:
    Ui::testApplication *ui;
};

#endif // TESTAPPLICATION_H
