/**
 * @author Moumita Ahmad
 */

#ifndef EDITPAGE_H
#define EDITPAGE_H

#include <QWidget>
#include "domain/ILogic.h"
#include "./value-objects/familytree.h"
#include "editpanel.h"
#include "displayfam.h"
#include "memberpanel.h"

namespace Ui {
class EditPage;
}

class EditPage : public QWidget
{
    Q_OBJECT

public:
    explicit EditPage(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~EditPage();

    void setupEditPage();
    void drawFamily();

signals:
    void switchToView();

private slots:
    void openViewPage();
    void openEditPanel(int memberID);
    void closeEditPanel();

private:
    domain::ILogic* m_pLogic;
    FamilyTree* m_displayedFamily;
    EditPanel* m_ep;
    DisplayFam* m_df;
    MemberPanel* m_mp;
    Ui::EditPage *ui;
};

#endif // EDITPAGE_H
