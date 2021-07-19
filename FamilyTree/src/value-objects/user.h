/**
 * @author Moumita Ahmad
 */

#ifndef USER_H
#define USER_H

#include <QString>

class User {
public:
    User(int id, QString& name, QString& password): m_id(id), m_name(name), m_password(password) {}
    ~User(){}

    int getId() const;
    const QString getName() const;
    const QString getPassword() const;

private:
    int m_id;
    QString m_name;
    QString m_password;

};

#endif // USER_H
