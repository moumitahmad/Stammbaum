#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./domain/ILogic.h"
#include "editfamilywindow.h"

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
    void switchToCreateNewUser();
    void createNewUser();
    void logInUser();
    void quit();

private:
    Ui::MainWindow *ui;
    editFamilyWindow *edWin;

};
#endif // MAINWINDOW_H
