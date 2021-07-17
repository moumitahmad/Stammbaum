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
    domain::ILogic* m_pLogic;
    FamilyTree* m_displayedFamily;
    QVector<Member*>* m_allMembers;

    explicit MemberPanel(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~MemberPanel();

    void setupMemberPanel();
    void resetUI();
    void updatePanel();

signals:
    void memberChoosen(int id); // id=-1 -> new Member

private slots:
    void changeMember(int id);
    void addNewMember();
    void activateButton(QPushButton& button);

private:
    Ui::MemberPanel *ui;
};

#endif // MEMBERPANEL_H
