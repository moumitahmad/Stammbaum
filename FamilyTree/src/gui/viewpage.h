#ifndef VIEWPAGE_H
#define VIEWPAGE_H

#include <QWidget>
#include "userwindow.h"
#include "./value-objects/familytree.h"

namespace Ui {
class ViewPage;
}

class ViewPage : public QWidget
{
    Q_OBJECT

public:
    MainWindow* m_appWindow;
    domain::ILogic* m_pLogic;
    FamilyTree* m_displayedFamily;

    explicit ViewPage(domain::ILogic* pLogic, MainWindow* appWindow, QWidget *parent = nullptr);
    ~ViewPage();

private slots:
    void openEditPage();
    void addEditor();
    void addViewer();
    void deleteFamily();

private:
    Ui::ViewPage *ui;
};

#endif // VIEWPAGE_H
