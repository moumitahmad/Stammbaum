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

Member* domain::ILogic::createMember(FamilyTree *family, const QString &name, const QString &birth,
        const QString &death, const QString &gender, const QString &biografie, Member *partner,
        QVector<Member*>* children) {
    qDebug() << name << birth << death << gender << biografie << partner->getName();
    Member* member = m_pDB->saveMember(name, birth, death, gender, biografie, partner, family->getId());
    if(!children->empty()) {
        qDebug() << "children exsist";
        for(Member* child : *children) {
            member = m_pDB->saveChildFromMember(child, member);
        }
    }
    return member;
}

Member *domain::ILogic::updateMemberData(Member* member, const QString& change, const DB_COL_NAME position) {
    // update Member object
    switch(position) {
    case NAME:
        member->setName(change);
        m_pDB->updateMember(member, change, "name");
        break;
    case BIRTH:
        member->setBirth(change);
        m_pDB->updateMember(member, change, "birth");
        break;
    case DEATH:
        member->setDeath(change);
        m_pDB->updateMember(member, change, "death");
        break;
    case GENDER:
        member->setGender(change);
        m_pDB->updateMember(member, change, "gender");
        break;
    case BIOGRAFIE:
        member->setBiografie(change);
        m_pDB->updateMember(member, change, "biografie");
        break;
    default:
        qDebug() << ">> ERROR: The position does not exsist";
    }

    // update DB
    return member;
}

Member *domain::ILogic::updatePartnerFromMember(Member *member, Member *partner) {
    return nullptr;
}

Member *domain::ILogic::updateParentFromMember(Member* child, Member *parent) {
    return nullptr;
}

Member *domain::ILogic::updateChildFromMember(Member* parent, Member *child) {
    QVector<Member*> savedChildren = m_pDB->getChildrenFromMemberID(parent->getID());
    if(!savedChildren.contains(child)) { // if child-parent-connection is not saved in the database
        return m_pDB->saveChildFromMember(parent, child);
    } else {
        return m_pDB->deleteChildFromMember(parent, child);
    }
}
