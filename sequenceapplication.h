#ifndef SEQUENCEAPPLICATION_H
#define SEQUENCEAPPLICATION_H

#include <QMainWindow>
#include <QListWidget>

namespace Ui {
class sequenceApplication;
}

class sequenceApplication : public QMainWindow
{
    Q_OBJECT

public:
    explicit sequenceApplication(QWidget *parent = nullptr);
    QListWidget* selectedItemsListWidget;

    ~sequenceApplication();

public slots:
    void returnDashboard();
    void addActionToMenu(QString menuItem, QString actionName);
    void onSubMenuSelected();
private:
    Ui::sequenceApplication *ui;

};

#endif // SEQUENCEAPPLICATION_H
