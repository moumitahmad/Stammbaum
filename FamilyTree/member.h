#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
#include <QVector>

enum gender {
    FEMALE,
    MALE,
    DIVERSE,
    UNKNOWN
};

class Member {
public:
    Member(int id, QString name ="Unknown", QString birth = "Unknown", QString death = nullptr,
           gender g = UNKNOWN, QString biografie = nullptr, Member* partner = nullptr,
           Member* parent1 = nullptr, Member* parent2 = nullptr):
        m_id(id), m_name(name), m_birth(birth), m_death(death), m_gender(g), m_biografie(biografie),
        m_partner(partner), m_parent1(parent1), m_parent2(parent2) {}
    ~Member();

    void updateMember(const QString& name, const QString& birth, const QString& death, const gender g, const QString& biografie);

    // Connections
    void updatePartner(Member* &partner);
    void updateParents(Member* &parent1, Member* &parent2);
    void addChild(Member* &child);
private:
    int m_id;
    QString m_name;
    QString m_birth;
    QString m_death;
    gender m_gender;
    QString m_biografie;
    Member* m_partner;
    Member* m_parent1;
    Member* m_parent2;
    QVector<Member*> m_children;
};

#endif // MEMBER_H
