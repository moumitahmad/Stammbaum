#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./domain/ILogic.h"
#include "applicationwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    domain::ILogic* m_pLogic;
    ApplicationWindow* m_pApp;

    MainWindow(domain::ILogic* pLogic, ApplicationWindow* pApp, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void switchToCreateNewUser();
    void switchToLogIn();
    void createNewUser();
    void logInUser();
    void quit();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
