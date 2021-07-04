#ifndef ILOGIC_H
#define ILOGIC_H

#include <QString>
#include <QVector>

#include "./value-objects/familytree.h"
#include "./value-objects/member.h"
#include "./value-objects/user.h"

#include "../persistence/databaseservice.h"


namespace domain {

    class ILogic  {
        database::IDatabase* m_pDB;
        User* m_currentUser;
        int m_currentFamilyID;

    public:
        ILogic(database::IDatabase* pDB): m_pDB(pDB){}

        User* getCurrentUser() const;
        void setCurrentUser(User* user);

        int getCurrentFamilyID() const;
        void setCurrentFamilyID(const int familyID);

        // database general
        void connectToDatabase();
        void printDatabase();


        // user
        User* createUser(QString& name, QString& password);
        User* loginUser(QString& name, QString& password);


        // ----------- FAMILY TREE
        FamilyTree* createFamily(QString& name, User* admin); //, QVector<User*> editors = new QVector<User*>, QVector<User*> viewers = new QVector<User*>
        FamilyTree* addEditor(FamilyTree* family, User* user);
        FamilyTree* addViewer(FamilyTree* family, User* user);

        QVector<FamilyTree*>* getFamilyTreesByUserID(int adminID);


        // ---------- MEMBER
        // create
        Member* createMember(FamilyTree* family, const QString& name, const QString& birth = "Unknown",
                const QString& death = "Unknown", const QString& gender = "Unknown",
                const QString& biografie = nullptr, Member* partner = new Member(),
                QVector<Member*>* children = new QVector<Member*>);

        // select
        QVector<Member*>* getMembersByFamily(int familyID);

        // update
        Member* updateMemberData(Member* member, const QString& change, const DB_COL_NAME position);
        // possible positions are: name, bith, death, gender, biografie
        Member* savePartnerFromMember(Member* member, Member* partner);
        Member* deletePartnerFromMember(Member* member, Member* partner);
        Member* saveParentChildRelationship(Member* parent, Member* child);
        Member* deleteParentChildRelationship(Member* parent, Member* child);
    };

}

#endif // ILOGIC_H
