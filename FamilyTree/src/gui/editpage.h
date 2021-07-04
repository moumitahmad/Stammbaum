#ifndef EDITPAGE_H
#define EDITPAGE_H

#include <QWidget>
#include "applicationwindow.h"

namespace Ui {
class EditPage;
}

class EditPage : public QWidget
{
    Q_OBJECT

public:
    ApplicationWindow* m_appWindow;
    domain::ILogic* m_pLogic;
    FamilyTree* m_displayedFamily;

    explicit EditPage(domain::ILogic* pLogic, ApplicationWindow* appWindow, QWidget *parent = nullptr);
    ~EditPage();

    void setFamily(int family) const;

private slots:
    void openViewPage();

private:
    Ui::EditPage *ui;
};

#endif // EDITPAGE_H
