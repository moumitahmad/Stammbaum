#include "member.h"
#include <QDebug>

int Member::getID() const {
    return m_id;
}

const QString& Member::getName() const {
    return m_name;
}

Member *Member::getPartner() const {
    return m_partner;
}

void Member::setName(const QString &name) {
    m_name = name;
}

void Member::setBirth(const QString &birth) {
    m_birth = birth;
}

void Member::setDeath(const QString &death) {
    m_death = death;
}

void Member::setGender(const QString &gender) {
    m_gender = gender;
}

void Member::setBiografie(const QString &biografie) {
    m_biografie = biografie;
}

void Member::setPartner(Member *partner) {
    m_partner = partner;
}

void Member::addParent(Member* parent) {
    if(m_parents.length()==2) {
        throw new std::logic_error("The child already has two parents, please remove one first");
    }
    m_parents.push_back(parent);
}

void Member::deleteParent(Member* parent) {
    int i = m_parents.indexOf(parent);
    if(i == -1) {
        qDebug() << "Parent does not exsist";
        throw new std::logic_error("Parent does not exsist.");
    } else {
        m_parents.remove(i);
    }
}

bool Member::isAlive() const {
    if(m_death == nullptr)
        return false;
    return true;
}

void Member::addChild(Member* child) {
    m_children.push_back(child);
}

void Member::deleteChild(Member* child) {
    int i = m_children.indexOf(child);
    if(i == -1) {
        qDebug() << "Parent does not exsist";
        throw new std::logic_error("Parent does not exsist.");
    } else {
        m_children.remove(i);
    }
}

// OPERATORS
/*bool Member::operator ==(Member *other) {
    return m_id == other->getID();
}

bool Member::operator !=(Member *other) {
    return !(this == other);
}*/
