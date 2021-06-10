#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
#include <QVector>

enum gender {
    FEMALE,
    MALE,
    UNKNOWN
};

class Member {
public:
    Member(int id, QString& name ="Unknown", QString& birth = "Unknown", QString& death = nullptr,
           gender g = UNKNOWN, QString& biografie = nullptr, Member* partner = nullptr,
           Member* parent1 = nullptr, Member* parent2 = nullptr, QVector<Member> children = nullptr):
        m_id(id), m_name(name), m_birth(birth), m_death(death), m_gender(g), m_biografie(biografie),
        m_partner(partner), m_parent1(parent1), m_parent2(parent2), m_children(children) {}
    ~Member();

    void updateMember(const QString& name = m_name, QString& birth = m_birth, QString& death = m_death,
                 gender g = m_gender, QString& biografie = m_biografie);
    // Connections
    void updatePartner(const Member* partner);
    void updateParents(const Member* parent1 = m_parent1, const Member* parent2 = m_parent2);
    void addChild(const Member* child);
private:
    int id;
    QString m_name;
    QString m_birth;
    QString m_death;
    gender m_gender;
    QString m_biografie;
    Member* m_partner;
    Member* m_parent1;
    Member* m_parent1;
    QVector<Member*> m_children;
};

#endif // MEMBER_H
