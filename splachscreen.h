#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QMainWindow>
#include <QProgressBar>

QT_BEGIN_NAMESPACE
namespace Ui { class SplashScreen; }
QT_END_NAMESPACE

class SplashScreen : public QMainWindow
{
    Q_OBJECT

public:
    SplashScreen(QWidget *parent = nullptr);
    ~SplashScreen();

private:
    Ui::SplashScreen *ui;
    QProgressBar *m_progressBar; // Ajout d'un pointeur vers la barre de progression

private slots:
    void handleProgressBar(); // Fonction pour mettre à jour la barre de progression

};
#endif // SPLASHSCREEN_H
