#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./domain/ILogic.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    domain::ILogic* m_pLogic;
    MainWindow(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~MainWindow();

    void openHomePage();
    void openViewPage();
    void openEditPage();

private slots:
    void logout();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
