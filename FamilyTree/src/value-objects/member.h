#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
#include <QVector>

/*enum gender {
    female,
    male,
    diverse,
    unknown
};*/

class Member {
public:
    Member() {}
    Member(int id, QString name, QString birth, QString death, QString gender,
        QString biografie, Member* partner):
        m_id(id), m_name(name), m_birth(birth), m_death(death), m_gender(gender),
        m_biografie(biografie), m_partner(partner) {}
    ~Member();

    void updateMember(const QString& name, const QString& birth, const QString& death, const QString& gender, const QString& biografie);

    // getter
    int getID() const;
    const QString& getName() const;

    // Family Connections
    void updatePartner(Member* partner);
    void addChild(Member* child);
    void deleteChild(Member* child);
    void addParent(Member* parent);
    void deleteParent(Member* parent);

private:
    int m_id;
    QString m_name;
    QString m_birth;
    QString m_death;
    QString m_gender;
    QString m_biografie;
    Member* m_partner;
    QVector<Member*> m_parents;
    QVector<Member*> m_children;
};

#endif // MEMBER_H
