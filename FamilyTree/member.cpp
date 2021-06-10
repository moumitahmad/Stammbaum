#include "member.h"

void Member::updateMember(const QString &name, QString &birth, QString &death, gender g, QString &biografie) {
    m_name = name;
    m_birth = birth;
    m_death = death;
    m_gender = g;
    m_biografie = biografie;
}

void Member::updatePartner(const Member *partner) {
    m_partner = partner;

}

void Member::updateParents(const Member *parent1, const Member *parent2) {
    m_parent1 = parent1;
    m_parent2 = parent2;
}

void Member::addChild(const Member *child) {
    m_children.append(child);
}
