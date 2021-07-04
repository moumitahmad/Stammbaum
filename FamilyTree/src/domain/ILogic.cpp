#include "ILogic.h"
#include "./persistence/databaseservice.h"
#include <QDebug>
#include <QSqlError>


User *domain::ILogic::getCurrentUser() const {
    return m_currentUser;
}

void domain::ILogic::setCurrentUser(User *user) {
    m_currentUser = user;
}

// databse

void domain::ILogic::connectToDatabase() {
    m_pDB->connectToDatabase();
}

void domain::ILogic::printDatabase() {
    m_pDB->printTableUser();
    m_pDB->printFamilyTable();
    m_pDB->printHasRightsTable();
}

// user //GURLEEN BEARBEITEN
User* domain::ILogic::createUser(QString& name, QString& password) {

    // check if valid username and passwords were entered
    if( name.size() < 5 || password.size() < 7){
        qDebug() << "name or password not valid";
        return nullptr;
    }

    int id = m_pDB->saveUser(name, password);

    // check if user was saved
    if(id == -1){
        qDebug() << "User cannot be created";
        return nullptr;
    } else {
        qDebug() << "User created";
        User* user = new User(id, name, password);
        return user;
    }
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
    } catch(const std::logic_error* exp) {
        qDebug() << "wrong user data";
        qDebug() << "EXCEPTION:" << exp->what();
        return nullptr;
    }
}

// family tree
FamilyTree* domain::ILogic::createFamily(QString& name, User* admin) {
    // validate family name
    qDebug() << name.length();
    if(name.length() < 2) // min 2 characters
        return nullptr;

    int id = m_pDB->saveFamily(name, admin);
    FamilyTree* family = new FamilyTree(id, name, admin);
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

QVector<FamilyTree*>* domain::ILogic::getFamilyTreesByUserID(int adminID) {
    return m_pDB->getFamilyTreesByUserID(adminID);
}

QVector<Member*>* domain::ILogic::getMembersByFamily(int familyID) {
    return m_pDB->getMemberByFamID(familyID);
}

Member* domain::ILogic::createMember(FamilyTree *family, const QString &name, const QString &birth,
        const QString &death, const QString &gender, const QString &biografie, Member *partner,
        QVector<Member*>* children) {
    int id = m_pDB->saveMember(name, birth, death, gender, biografie, partner, family->getId());
    Member* member = new Member(id, name, birth, death, gender, biografie, partner);
    if(!children->empty()) {
        qDebug() << "children exsist";
        for(Member* child : *children) {
            try {
                child->addParent(member);
                member->addChild(child);
                m_pDB->saveParentChildRelationship(child, member);
            } catch(const std::logic_error ex) {
                qDebug() << ex.what();
                return nullptr;
            }
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
        qDebug() << ">> ERROR: The column position does not exsist";
    }
    return member;
}

Member *domain::ILogic::savePartnerFromMember(Member *member, Member *partner) {
    member->setPartner(partner);
    m_pDB->updatePartnerFromMember(partner, member);
    return member;
}

Member *domain::ILogic::deletePartnerFromMember(Member *member, Member *partner) {
    if(member->getPartner()->getID() == partner->getID()) {
        qDebug() << "DELETE";
        member->setPartner(nullptr);
        m_pDB->deletePartnerFromMember(member);
    } else {
        throw new std::logic_error("The Member was never a Partner and can not be deleted.");
    }
    return member;
}

Member *domain::ILogic::saveParentChildRelationship(Member* parent, Member *child) {
    // verify action
    QVector<Member*> savedChildren = parent->getChildren();
    if(!savedChildren.contains(child)) { // if child-parent-connection is not saved
        try {
            child->addParent(parent);
            parent->addChild(child);
            m_pDB->saveParentChildRelationship(parent, child);
        } catch(const std::logic_error ex) {
            qDebug() << ex.what();
        }
    } else {
        throw new std::logic_error("The relationship between the Child and Parent already exsists.");
    }
    return parent;
}

Member *domain::ILogic::deleteParentChildRelationship(Member* parent, Member *child) {
    // verify action
    QVector<Member*> savedChildren = parent->getChildren();
    if(savedChildren.contains(child)) { // if child-parent-connection is saved
        parent->deleteChild(child);
        child->deleteParent(parent);
        m_pDB->deleteParentChildRelationship(parent, child);
    } else {
        throw new std::logic_error("The relationship between the Child and Parent does not exsist and can not be deleted.");
    }
    return parent;
}
