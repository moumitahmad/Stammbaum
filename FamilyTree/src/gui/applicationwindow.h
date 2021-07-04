#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QMainWindow>
#include "./domain/ILogic.h"

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

    void openViewPage(int familyID);

private:
    Ui::ApplicationWindow *ui;
};

#endif // APPLICATIONWINDOW_H
