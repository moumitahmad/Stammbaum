#ifndef DATABASESERVICE_H
#define DATABASESERVICE_H

#include "./value-objects/user.h"
#include "./value-objects/familytree.h"
#include "./value-objects/member.h"
/*
GUI <- Ifc -> Logic <- Ifc -> Datenbank

class IBusinessLogic
        public:
        std::vector<Person> get.....();
*/

namespace database {
    // general
    void connectToDatabase();
    // print
    void printTableUser();
    void printFamilyTable();
    void printHasRightsTable();

    // user
    User* saveUser(QString name, QString password);

    // family tree
    FamilyTree* saveFamily(QString name, User* admin);
    void saveEditor(int familyID, User* editor);
    void saveViewer(int familyID, User* viewer);

    void saveEditorFromFamily(int userId, int familyID);
    void deleteEditorFromFamily(int userId, int familyID);
    void saveViewerFromFamily(int userId, int familyID);
    void deleteViewerFromFamily(int userId, int familyID);

    // member
    Member* saveMember(QString& name, QString& birth, QString& death, gender g, QString& biografie, int familyID);
    void updateMember(QString& name, QString& birth, QString& death, gender g, QString& biografie, int familyID);

    // relationships
    void updateParentFromMember(int parentID, int memberID);
    void deleteParentFromMember(int parentID, int memberID);
    void updatePartnerFromMember(int partnerID, int memberID); // overrides the saved parnter
    void saveChildFromMember(int childID, int memberID);
    void deleteChildFromMember(int childID, int memberID);
}

#endif // DATABASESERVICE_H
