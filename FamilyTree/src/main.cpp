/**
* @author Gurleen Kour, Alisa Schumann, Moumita Ahmad
* Contact: gkour@stud.hs-bremen.de, aschumann@stud.hs-bremen.de, mahmad@stud.hs-bremen.de
*/

#include "gui/mainwindow.h"
#include "value-objects/user.h"
#include <QApplication>

#include "persistence/databaseservice.h"

void testDatabase() {
    QVector<int> editors;
    QVector<int> viewers;
    QString name = "Erben";
    database::saveFamily(name, 1, editors, viewers);
}

int main(int argc, char *argv[]) {
    database::connectToDatabase();
    testDatabase();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
