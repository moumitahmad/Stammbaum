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
        Member* getMemberByID(const int id);
        Member* saveMember(const QString& name, const QString& birth, const QString& death, const QString& gender, const QString& biografie, Member* partner, int familyID);
        Member* updateMember(const int id, const QString& change, const QString& position);

        // relationships
        Member* savePartnerFromMember(Member* partner, Member* member);
        Member* updatePartnerFromMember(Member* partner, Member* member); // overrides the saved parnter

        Member* saveChildFromMember(Member* child, Member* parent);
        QVector<Member*> getChildrenFromMemberID(const int id);
        Member* deleteChildFromMember(Member* parent, Member* child);
    };
}

#endif // DATABASESERVICE_H
