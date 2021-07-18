#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include "./domain/ILogic.h"
#include "mainwindow.h"

namespace Ui {
class UserWindow;
}

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    domain::ILogic* m_pLogic;
    MainWindow* m_pApp;

    explicit UserWindow(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~UserWindow();

    void hideErrors();

private slots:
    void switchToCreateNewUser();
    void switchToLogIn();
    void createNewUser();
    void logInUser();

private:
    Ui::UserWindow *ui;
};

#endif // USERWINDOW_H
