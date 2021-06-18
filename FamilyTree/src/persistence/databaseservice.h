#ifndef DATABASESERVICE_H
#define DATABASESERVICE_H

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

    // user
    void saveUser(QString name, QString password);

    // family tree
    void saveFamily(QString name, int adminID, QVector<int> editorIDs, QVector<int> viewerIDs);
    void updateFamily(QString name, int adminID, QVector<int> editorIDs, QVector<int> viewerIDs);

    void saveEditorFromFamily(int userId, int familyID);
    void deleteEditorFromFamily(int userId, int familyID);
    void saveViewerFromFamily(int userId, int familyID);
    void deleteViewerFromFamily(int userId, int familyID);

    // member
    void saveMember(QString& name, QString& birth, QString& death, gender g, QString& biografie, int familyID);
    void updateMember(QString& name, QString& birth, QString& death, gender g, QString& biografie, int familyID);

    // relationships
    void updateParentFromMember(int parentID, int memberID);
    void deleteParentFromMember(int parentID, int memberID);
    void updatePartnerFromMember(int partnerID, int memberID); // overrides the saved parnter
    void saveChildFromMember(int childID, int memberID);
    void deleteChildFromMember(int childID, int memberID);
}

#endif // DATABASESERVICE_H
