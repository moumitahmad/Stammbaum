/**
* @author Gurleen Kour, Alisa Schumann, Moumita Ahmad
* Contact: gkour@stud.hs-bremen.de, aschumann@stud.hs-bremen.de, mahmad@stud.hs-bremen.de
*/

#include "gui/mainwindow.h"
#include "value-objects/user.h"
#include <QApplication>

#include "domain/ILogic.h"

void testDatabase() {
    QString adminName = "TestAdmin";
    QString editorName = "TestEditor";
    QString password = "password";
    QString familyName = "TestFamily";

    User* admin = domain::createUser(adminName, password);
    User* editor = domain::createUser(editorName, password);
    FamilyTree* family = domain::createFamily(familyName, admin);
    family = domain::addEditor(family, editor);
    domain::printDatabase();
}

int main(int argc, char *argv[]) {
    domain::connectToDatabase();
    //testDatabase();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
