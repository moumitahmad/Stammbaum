/**
 * @author Moumita Ahmad
 */

#ifndef MEMBERPANEL_H
#define MEMBERPANEL_H

#include <QWidget>
#include "domain/ILogic.h"
#include "QPushButton"

namespace Ui {
class MemberPanel;
}

class MemberPanel : public QWidget
{
    Q_OBJECT

public:
    explicit MemberPanel(domain::ILogic* pLogic, QWidget *parent = nullptr, const bool& inEdit = false);
    ~MemberPanel();

    void setupMemberPanel();
    void resetUI();
    void updatePanel();

signals:
    void memberChoosen(int id); // id=-1 -> new Member

private slots:
    void changeMember(int id);
    void addNewMember();

private:
    Ui::MemberPanel *ui;
    FamilyTree* m_displayedFamily;
    QVector<Member*> m_allMembers;
    const bool m_inEdit;
    domain::ILogic* m_pLogic;
};

#endif // MEMBERPANEL_H
