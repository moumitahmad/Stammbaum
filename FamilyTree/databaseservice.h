#ifndef DATABASESERVICE_H
#define DATABASESERVICE_H

#include "QString"

namespace database {
    void connectToDatabase();
    void saveUser(QString name, QString password);
}

#endif // DATABASESERVICE_H
