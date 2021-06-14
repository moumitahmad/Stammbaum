/**
* @author Gurleen Kour, Alisa Schumann, Moumita Ahmad
* Contact: gkour@stud.hs-bremen.de, aschumann@stud.hs-bremen.de, mahmad@stud.hs-bremen.de
*/

#include "gui/mainwindow.h"
#include <QApplication>

#include "persistence/databaseservice.h"

int main(int argc, char *argv[]) {
    database::connectToDatabase();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
