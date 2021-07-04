#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QMainWindow>
#include "./domain/ILogic.h"
#include "editpage.h"
#include "viewpage.h"

namespace Ui {
    class ApplicationWindow;
}

class ApplicationWindow : public QMainWindow
{
    Q_OBJECT

public:
    domain::ILogic* m_pLogic;

    explicit ApplicationWindow(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~ApplicationWindow();

    void openViewPage();
    void openEditPage();

private slots:
    void logout();

private:
    Ui::ApplicationWindow *ui;
};

#endif // APPLICATIONWINDOW_H
