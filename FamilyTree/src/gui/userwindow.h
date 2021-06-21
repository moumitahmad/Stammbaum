#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QWidget>
#include "./domain/ILogic.h"

namespace Ui {
class UserWindow;
}

class UserWindow : public QWidget
{
    Q_OBJECT

public:
    domain::ILogic* m_pLogic;
    explicit UserWindow(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~UserWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::UserWindow *ui;
};

#endif // USERWINDOW_H
