#ifndef ILOGIC_H
#define ILOGIC_H

#include <QString>
#include <QVector>

#include "./value-objects/familytree.h"
#include "./value-objects/member.h"
#include "./value-objects/user.h"

namespace domain {
    // database gernal
    void connectToDatabase();
    void printDatabase();


    // user
    User* createUser(QString& name, QString& password);
    User* loginUser(QString& name, QString& password);


    // family tree
    FamilyTree* createFamily(QString& name, User* admin); //, QVector<User*> editors = new QVector<User*>, QVector<User*> viewers = new QVector<User*>
    FamilyTree* addEditor(FamilyTree* family, User* user);
    FamilyTree* addViewer(FamilyTree* family, User* user);

    QVector<FamilyTree*> getFamilyTreesByUserID(int userID);
    FamilyTree* getFamilyTreesByID(int familyID);


    // member
    QVector<Member*> getMembersByFamily(int familyID);
    void updateMemberFromFamily(int familyID);
}

#endif // ILOGIC_H
