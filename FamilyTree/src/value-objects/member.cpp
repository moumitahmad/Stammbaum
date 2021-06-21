#include "member.h"
#include <QDebug>

int Member::getID() const {
    return m_id;
}

const QString& Member::getName() const {
    return m_name;
}

void Member::addParent(Member* parent) {
    m_parents.append(parent);
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

void Member::updateMember(const QString &name, const QString &birth, const QString &death, const QString& gender, const QString &biografie) {
    m_name = name;
    m_birth = birth;
    m_death = death;
    m_gender = gender;
    m_biografie = biografie;
}

void Member::updatePartner(Member *partner) {
    m_partner = partner;
}

void Member::addChild(Member* child) {
    m_children.append(child);
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
