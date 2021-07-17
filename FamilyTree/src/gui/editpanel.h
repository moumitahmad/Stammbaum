#ifndef EDITPANEL_H
#define EDITPANEL_H

#include <QWidget>
#include "domain/ILogic.h"
#include <filesystem>

namespace Ui {
class EditPanel;
}

class EditPanel : public QWidget
{
    Q_OBJECT

public:
    explicit EditPanel(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~EditPanel();

    void setupEditPanel(int memberID);

signals:
    void closePanel();

private slots:
    void selectPicture();
    void removePicture();
    void saveMember();
    void resetUI();
    void deleteMember();
    void toggleBirthDate();
    void toggleDeathDate();
    void toggleSecondParent();

private:
    Ui::EditPanel *ui;
    domain::ILogic* m_pLogic;
    FamilyTree* m_displayedFamily;
    Member* m_editedMember;
    QVector<Member*> m_possibleRelationships;
    QString m_imagePath = "";

    void showPotentionRelationships();
    void showError(const QString& message) const;
    bool relationshipValid(int& partnerID, int& parent1ID, int& parent2ID);
    int getIndexForRelationship(const int memberID) const;
    std::filesystem::path currentImageSymlink; //selectedPicture
};

#endif // EDITPANEL_H
