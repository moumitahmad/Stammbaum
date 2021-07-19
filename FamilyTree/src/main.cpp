/**
 * @author Moumita Ahmad
 */

#include <QApplication>
#include "domain/ILogic.h"
#include "./gui/userwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    database::IDatabase* pDB = new database::IDatabase();
    domain::ILogic* pLogic = new domain::ILogic(pDB);
    pLogic->connectToDatabase();

    UserWindow uw(pLogic);
    uw.show();
    return a.exec();
}
