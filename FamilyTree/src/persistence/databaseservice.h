#ifndef DATABASESERVICE_H
#define DATABASESERVICE_H

#include "./value-objects/user.h"
#include "./value-objects/familytree.h"
#include "./value-objects/member.h"


namespace database {
    class IDatabase  {
    public:
        // general
        void connectToDatabase();
        // print
        void printTableUser();
        void printFamilyTable();
        void printHasRightsTable();

        // user
        User* saveUser(QString& name, QString& password);
        User* getUserByName(QString& userName);

        // family tree
        FamilyTree* saveFamily(QString& name, User* admin);
        void saveEditor(int familyID, User* editor);
        void saveViewer(int familyID, User* viewer);

        void saveEditorFromFamily(int userId, int familyID);
        void deleteEditorFromFamily(int userId, int familyID);
        void saveViewerFromFamily(int userId, int familyID);
        void deleteViewerFromFamily(int userId, int familyID);

        // member
        Member* saveMember(QString& name, const QString& birth, const QString& death, const QString& gender, const QString& biografie, Member* partner, int familyID);
        Member* updateMember(QString& name, QString& birth, QString& death, QString& gender, QString& biografie, int familyID);

        // relationships
        Member* savePartnerFromMember(Member* partner, Member* member);
        Member* updatePartnerFromMember(Member* partner, Member* member); // overrides the saved parnter

        Member* saveChildFromMember(Member* child, Member* parent);
        Member* deleteChildFromMember(Member* child, Member* parent);
    };
}

#endif // DATABASESERVICE_H
