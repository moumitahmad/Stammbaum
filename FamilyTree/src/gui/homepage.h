#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include "domain/ILogic.h"
#include "./value-objects/user.h"
#include "mainwindow.h"

namespace Ui {
class Homepage;
}

class Homepage : public QWidget
{
    Q_OBJECT

public:
    MainWindow* m_appWindow;
    domain::ILogic* m_pLogic;
    User* m_currentUser;

    explicit Homepage(domain::ILogic* pLogic, MainWindow* appWindow, QWidget *parent = nullptr);
    ~Homepage();

    void displayFamilies();

signals:
    void switchToView();

private slots:
    void showFamily(int id);
    void addFamily();

private:
    Ui::Homepage *ui;
};

#endif // HOMEPAGE_H
