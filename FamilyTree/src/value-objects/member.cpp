#include "member.h"

void Member::updateMember(const QString &name, const QString &birth, const QString &death, const gender g, const QString &biografie) {
    m_name = name;
    m_birth = birth;
    m_death = death;
    m_gender = g;
    m_biografie = biografie;
}

void Member::updatePartner(Member *partner) {
    m_partner = partner;
}

void Member::updateParents(Member* parent1, Member* parent2) {
    m_parent1 = parent1;
    m_parent2 = parent2;
}

void Member::addChild(Member* child) {
    m_children.append(child);
}
