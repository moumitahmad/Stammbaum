#include "user.h"

int User::getId() const {
    return m_id;
}

const QString User::getName() const {
    return m_name;
}

const QString User::getPassword() const {
    return m_password;
}
