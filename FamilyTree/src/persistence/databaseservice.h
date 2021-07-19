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
        bool userIsViewer(int userID, int familyID);

        // family tree
        int saveFamily(QString& name, User* admin);
        void deleteFamilyByID(const int familyID);
        void saveEditor(int familyID, User* editor);
        void upgradeUserRigths(int familyID, User* editor);
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
        QVector<Member*>* getMembersByFamID(const int id);
        Member* getPartnerFromMember(const int memberID);
        QVector<Member*>* getParentsFromMemberID(const int memberID);
        QVector<Member*>* setCPRelations(QVector<Member*>* family);
        int saveMember(const QString& name, const QString& birth, const QString& death, const QString& gender, const QString& image, int familyID);
        void updateMemberData(Member* member);
        void deleteMember(Member* member);

        // relationships
        void updatePartnerFromMember(Member* partner, Member* member);
        void deletePartnerFromMember(Member* member);

        void saveParentChildRelationship(Member* child, Member* parent);
        QVector<Member*> getChildrenFromMemberID(const int id);
        void deleteParentChildRelationship(Member* parent, Member* child);
    };
}

#endif // DATABASESERVICE_H
