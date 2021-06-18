#include "ILogic.h"
#include "./persistence/databaseservice.h"

// databse
void domain::connectToDatabase() {
    database::connectToDatabase();
}

void domain::printDatabase() {
    database::printTableUser();
    database::printFamilyTable();
    database::printHasRightsTable();
}

// user
User* domain::createUser(QString& name, QString& password) {
    return database::saveUser(name, password);
}

// family tree
FamilyTree* domain::createFamily(QString& name, User* admin) { // , QVector<User*> editors, QVector<User*> viewers
    FamilyTree* family = database::saveFamily(name, admin);
    /*for(int i=0; i<editors.length(); i++) {
        database::saveEditor(family->getId(), editors.at(i));
        family->addEditor(editors.at(i));
    }
    for(int i=0; i<viewers.length(); i++) {
        database::saveEditor(family->getId(), viewers.at(i));
        family->addViewer(viewers.at(i));
    }*/
    return family;
}

FamilyTree* domain::addEditor(FamilyTree* family, User* user) {
    database::saveEditor(family->getId(), user);
    family->addEditor(user);
    return family;
}

FamilyTree* domain::addViewer(FamilyTree* family, User* user) {
    database::saveViewer(family->getId(), user);
    family->addViewer(user);
    return family;
}

