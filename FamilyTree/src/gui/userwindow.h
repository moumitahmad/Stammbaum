#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include "./domain/ILogic.h"
#include "./gui/mainwindow.h"

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

private slots:
    void switchToCreateNewUser();
    void switchToLogIn();
    void createNewUser();
    void logInUser();
    void quit();

private:
    Ui::UserWindow *ui;
};

#endif // USERWINDOW_H