

#include <QApplication>
#include "domain/ILogic.h"
#include "./gui/userwindow.h"




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    database::IDatabase* pDB = new database::IDatabase();
    domain::ILogic* pLogic = new domain::ILogic(pDB);
    pLogic->connectToDatabase();
<<<<<<< HEAD

    //MainWindow mw(pLogic);
    UserWindow uw(pLogic);
    uw.show();
=======
    testDatabase(pLogic);
    //fillDatabase(pLogic);
    QApplication a(argc, argv);
    ApplicationWindow* app;
    MainWindow w(pLogic, app);
    w.show();
>>>>>>> c86b16cc78449c6af643b909899119ac01f2f116
    return a.exec();
}
