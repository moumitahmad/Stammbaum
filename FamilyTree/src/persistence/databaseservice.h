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
        int saveUser(QString& name, QString& password);
        User* getUserByName(QString& userName);
        User* getUserByID(int id);

        // family tree
        int saveFamily(QString& name, User* admin);
        void deleteFamilyByID(const int familyID);
        void saveEditor(int familyID, User* editor);
        void saveViewer(int familyID, User* viewer);
        QVector<User*>* getViewersByFamilyID(int family);
        QVector<User*>* getEditorsByFamilyID(int family);

        void saveEditorFromFamily(int userId, int familyID);
        void deleteEditorFromFamily(int userId, int familyID);
        void saveViewerFromFamily(int userId, int familyID);
        void deleteViewerFromFamily(int userId, int familyID);

        QVector<FamilyTree*>* getFamilyTreesByUserID(int userID);
        FamilyTree* getFamilyTreeByID(int familyID);

        // member
        Member* getMemberByID(const int id);
        QVector<Member*>* getMemberByFamID(const int id);
        int saveMember(const QString& name, const QString& birth, const QString& death, const QString& gender, const QString& biografie, int partnerID, int familyID);
        void updateMember(Member* member, const QString& change, const QString& position);

        // relationships
        void updatePartnerFromMember(Member* partner, Member* member);
        void deletePartnerFromMember(Member* member);

        void saveParentChildRelationship(Member* child, Member* parent);
        QVector<Member*> getChildrenFromMemberID(const int id);
        void deleteParentChildRelationship(Member* parent, Member* child);
    };
}

#endif // DATABASESERVICE_H
