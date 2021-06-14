#ifndef ILOGIC_H
#define ILOGIC_H

#include <QString>

namespace domain {
    class IUserLogic {
        void createUser(int id, QString& name, QString& password);
    };

    class IFamilyLogic {

    };

    class IMemberLogic {
        void updateMember();
    };
}

#endif // ILOGIC_H
