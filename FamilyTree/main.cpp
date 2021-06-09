/**
* @author Gurleen Kour, Alisa Schumann, Moumita Ahmad
* Contact: gkour@stud.hs-bremen.de, aschumann@stud.hs-bremen.de, mahmad@stud.hs-bremen.de
*/

#include "mainwindow.h"
#include "user.h"
#include <QApplication>

#include "QDebug"
#include "QString"

#include "QSqlDatabase"
#include "QSqlQuery"
#include "QSqlError"


void fillDatabase() {
    QSqlQuery q1;
    if(q1.exec("CREATE TABLE IF NOT EXISTS user(id INTEGER PRIMARY KEY, name VARCHAR (50) NOT NULL UNIQUE, password VARCHAR (50) NOT NULL);")) {
        qDebug() << "Table user created!";
    } else {
        qDebug() << q1.lastError();
        return;
    }

    // fill Table user
    QSqlQuery q2;
    q2.prepare("INSERT INTO user VALUES(:id, :name, :password);");
    q2.bindValue(":id", 2);
    q2.bindValue(":name", "Test User2");
    q2.bindValue(":password", "password1234");

    if(q2.exec()) {
        qDebug() << "New user entered!";
    } else {
        qDebug() << q1.lastError();
        return;
    }

    // test table
    QSqlQuery q3;
    q3.exec("SELECT * FROM user;");
    while(q3.next()) {
        int id = q3.value(0).toInt();
        QString name = q3.value(1).toString();
        QString password = q3.value(2).toString();

        User user(id, name, password);
        qDebug() << user.getId() << ": " << user.getName();
    }
}

void connectToDatabase() {
    // connect to database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("qsqlite");

    // test connection
    bool success = db.open();
    qDebug() << "Database connection established: " << success;

    fillDatabase();
}

int main(int argc, char *argv[]) {
    connectToDatabase();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
