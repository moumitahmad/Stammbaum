/**
* @author Gurleen Kour, Alisa Schumann, Moumita Ahmad
* Contact: gkour@stud.hs-bremen.de, aschumann@stud.hs-bremen.de, mahmad@stud.hs-bremen.de
*/

#include <QApplication>
#include <QDebug>

#include "gui/mainwindow.h"
#include "value-objects/user.h"
#include "domain/ILogic.h"
#include "persistence/databaseservice.h"

void testDatabase(domain::ILogic* pLogic) {
    QString adminName = "TestAdmin";
    QString editorName = "TestEditor";
    QString password = "password";
    QString familyName = "TestFamily";

    QString memberName1 = "TestMember";
    QString memberName2 = "TestParent";
    QString birth = "01.09.1968";
    QString death = "02.04.2010";

    // CREATE
    User* admin = pLogic->createUser(adminName, password);
    User* editor = pLogic->createUser(editorName, password);
    FamilyTree* family = pLogic->createFamily(familyName, admin);
    family = pLogic->addEditor(family, editor);
    pLogic->printDatabase();

    Member* member1 = pLogic->createMember(family, memberName1);
    QVector<Member*>* children = new QVector<Member*>;
    children->push_back(member1);
    Member* member2 = pLogic->createMember(family, memberName2, birth, death, "female", nullptr, new Member(), children);

    // UPDATE
    Member* newChild = pLogic->createMember(family, "New Child");
    pLogic->updateMemberData(member1, "NEW NAME", NAME);
    qDebug() << member1->getName();
    pLogic->updateParentChildRelationship(member2, newChild);
    Member* newPartner = pLogic->createMember(family, "New Partner");
    pLogic->updatePartnerFromMember(member1, newPartner);
}


int main(int argc, char *argv[]) {
    database::IDatabase* pDB = new database::IDatabase();
    domain::ILogic* pLogic = new domain::ILogic(pDB);

    pLogic->connectToDatabase();
    testDatabase(pLogic);
    QApplication a(argc, argv);
    MainWindow w(pLogic);
    w.show();
    return a.exec();
}
