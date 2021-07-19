/**
 * @author Gurleen Kour, Moumita Ahmad
 */

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
    explicit UserWindow(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~UserWindow();

    void hideErrors();

private slots:
    void switchToCreateNewUser();
    void switchToLogIn();
    void createNewUser();
    void logInUser();

private:
    domain::ILogic* m_pLogic;
    MainWindow* m_pApp;

    Ui::UserWindow *ui;
};

#endif // USERWINDOW_H
