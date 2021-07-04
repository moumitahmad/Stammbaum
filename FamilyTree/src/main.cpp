/**
* @author Gurleen Kour, Alisa Schumann, Moumita Ahmad
* Contact: gkour@stud.hs-bremen.de, aschumann@stud.hs-bremen.de, mahmad@stud.hs-bremen.de
*/

#include <QApplication>
#include <QDebug>

#include "gui/mainwindow.h"
#include "gui/applicationwindow.h"
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
    pLogic->saveParentChildRelationship(member2, newChild);
    pLogic->deleteParentChildRelationship(member2, newChild);
    Member* newPartner = pLogic->createMember(family, "New Partner");
    pLogic->savePartnerFromMember(member1, newPartner);
    pLogic->deletePartnerFromMember(member1, newPartner);
}

void fillDatabase(domain::ILogic* pLogic) {
    QString username = "Test User";
    QString password = "qwertzuiop";
    QString famName1 = "Ahmad";
    QString famName2 = "Erben";
    User* user = pLogic->createUser(username, password);
    FamilyTree* fam1 = pLogic->createFamily(famName1, user);
    pLogic->createFamily(famName2, user);
    User* editor = pLogic->createUser(famName1, password);
    pLogic->addEditor(fam1, editor);
}

int main(int argc, char *argv[]) {
    database::IDatabase* pDB = new database::IDatabase();
    domain::ILogic* pLogic = new domain::ILogic(pDB);

    pLogic->connectToDatabase();
 //   testDatabase(pLogic);
    //fillDatabase(pLogic);
    QApplication a(argc, argv);
    ApplicationWindow* app;
    MainWindow w(pLogic, app);
    w.show();
    return a.exec();
}
