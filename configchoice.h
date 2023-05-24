#ifndef CONFIGCHOICE_H
#define CONFIGCHOICE_H

#include <QMainWindow>

namespace Ui {
class ConfigChoice;
}

class ConfigChoice : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigChoice(QWidget *parent = nullptr);
    ~ConfigChoice();

public slots:
    void handleLoadConfigButton();
    void checkGroupAndAddSubMenu();
private:
    Ui::ConfigChoice *ui;
};

#endif // CONFIGCHOICE_H
