#ifndef DATABASESERVICE_H
#define DATABASESERVICE_H

#include "QString"
/*
GUI <- Ifc -> Logic <- Ifc -> Datenbank

class IBusinessLogic
        public:
        std::vector<Person> get.....();
*/

namespace database {
    void connectToDatabase();
    void saveUser(QString name, QString password);
}

#endif // DATABASESERVICE_H
