#include "ILogic.h"
#include "./persistence/databaseservice.h"
#include <QDebug>


// databse
void domain::ILogic::connectToDatabase() {
    m_pDB->connectToDatabase();
}

void domain::ILogic::printDatabase() {
    m_pDB->printTableUser();
    m_pDB->printFamilyTable();
    m_pDB->printHasRightsTable();
}

// user
User* domain::ILogic::createUser(QString& name, QString& password) {
    return m_pDB->saveUser(name, password);
}

User* domain::ILogic::loginUser(QString& name, QString& password) {
    try {
        User* user = m_pDB->getUserByName(name);
        if(user->getPassword() == password) {
            return user;
        } else {
            qDebug() << "wrong password";
            return nullptr;
        }
    } catch(const std::logic_error exp) {
        qDebug() << "wrong username";
        qDebug() << "EXCEPTION:" << exp.what();
        return nullptr;
    }
}

// family tree
FamilyTree* domain::ILogic::createFamily(QString& name, User* admin) { // , QVector<User*> editors, QVector<User*> viewers
    FamilyTree* family = m_pDB->saveFamily(name, admin);
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

FamilyTree* domain::ILogic::addEditor(FamilyTree* family, User* user) {
    m_pDB->saveEditor(family->getId(), user);
    family->addEditor(user);
    return family;
}

FamilyTree* domain::ILogic::addViewer(FamilyTree* family, User* user) {
    m_pDB->saveViewer(family->getId(), user);
    family->addViewer(user);
    return family;
}

Member* domain::ILogic::createMember(FamilyTree* family, QString& name,
        const QString& birth, const QString& death, const QString& gender,
        const QString& biografie, Member *partner, QVector<Member*> *children) {
    Member* member = m_pDB->saveMember(name, birth, death, gender, biografie, partner, family->getId());
    if(!children->empty()) {
        qDebug() << "children exsist";
        for(Member* child : *children) {
            member = m_pDB->saveChildFromMember(child, member);
        }
    }
    return member;
}

