#ifndef VIEWPAGE_H
#define VIEWPAGE_H

#include <QWidget>
#include "domain/ILogic.h"
#include "adminpanel.h"

namespace Ui {
class ViewPage;
}

class ViewPage : public QWidget
{
    Q_OBJECT

public:
    domain::ILogic* m_pLogic;
    FamilyTree* m_displayedFamily;
    User* m_currentUser;
    AdminPanel* m_ap;

    explicit ViewPage(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~ViewPage();

   void setupViewPage();

signals:
    void switchToEdit();
    void switchToHome();

private slots:
    void openEditPage();
    void openHomePage();

private:
    Ui::ViewPage *ui;
};

#endif // VIEWPAGE_H
