#ifndef CONFIGMODE_H
#define CONFIGMODE_H

#include <QMainWindow>

namespace Ui {
class ConfigMode;
}

class ConfigMode : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigMode(QWidget *parent = nullptr);
    ~ConfigMode();

private:
    Ui::ConfigMode *ui;

public slots :
    void returnDashboard();

};

#endif // CONFIGMODE_H
