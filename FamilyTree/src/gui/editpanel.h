#ifndef EDITPANEL_H
#define EDITPANEL_H

#include <QWidget>
#include "domain/ILogic.h"

namespace Ui {
class EditPanel;
}

class EditPanel : public QWidget
{
    Q_OBJECT

public:
    domain::ILogic* m_pLogic;
    FamilyTree* m_displayedFamily;
    Member* m_editedMember;
    QVector<Member*>* m_membersFromFam;

    explicit EditPanel(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~EditPanel();

    void setupEditPanel(int memberID);

signals:
    void closePanel();

private slots:
    void uploadPicture();
    void saveMember();
    void resetUI();
    void deleteMember();
    void toggleBirthDate();
    void toggleDeathDate();

private:
    Ui::EditPanel *ui;
};

#endif // EDITPANEL_H
