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
    ViewPage* m_vp;
    EditPage* m_ep;

    explicit ApplicationWindow(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~ApplicationWindow();

    void openViewPage(int familyID);
    void openEditPage(int familyID);

private slots:
    void logout();

private:
    Ui::ApplicationWindow *ui;
};

#endif // APPLICATIONWINDOW_H
