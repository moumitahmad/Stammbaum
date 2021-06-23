#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "userwindow.h"
#include "./domain/ILogic.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    domain::ILogic* m_pLogic;

    MainWindow(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void createNewUser();

    void logInUser();

private:
    Ui::MainWindow *ui;
    UserWindow *userwindow;
};
#endif // MAINWINDOW_H
