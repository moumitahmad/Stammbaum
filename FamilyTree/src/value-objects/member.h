#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
#include <QVector>

enum DB_COL_NAME {
    NAME,
    BIRTH,
    DEATH,
    GENDER,
    BIOGRAFIE
};

class Member {
public:
    Member() {}
    Member(int id, QString name, QString birth, QString death, QString gender,
        QString biografie, Member* partner):
        m_id(id), m_name(name), m_birth(birth), m_death(death), m_gender(gender),
        m_biografie(biografie), m_partner(partner) {}
    ~Member();

    // getter
    int getID() const;
    const QString& getName() const;
    const Member* getPartner() const;

    //setter
    void setName(const QString& name);
    void setBirth(const QString& birth);
    void setDeath(const QString& death);
    void setGender(const QString& gender);
    void setBiografie(const QString& biografie);
    void setPartner(Member* partner);

    // Family Connections
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
