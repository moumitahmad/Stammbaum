#ifndef ILOGIC_H
#define ILOGIC_H

#include <QString>
#include <QVector>

#include "./value-objects/familytree.h"
#include "./value-objects/member.h"
#include "./value-objects/user.h"

namespace domain {
    class IUserLogic {
        User* createUser(QString& name, QString& password);
        User* loginUser(QString& name, QString password);

        QVector<User*> getEditorsByFamilyID(int familyID); // Admin + Editors
        QVector<User*> getViewersByFamilyID(int familyID);
    };

    class IFamilyLogic {
        QVector<FamilyTree*> getFamilyTreesByUserID(int userID);
        FamilyTree* getFamilyTreesByID(int familyID);
    };

    class IMemberLogic {
        QVector<Member*> getMembersByFamily(int familyID);
        void updateMemberFromFamily(int familyID);
    };
}

#endif // ILOGIC_H
