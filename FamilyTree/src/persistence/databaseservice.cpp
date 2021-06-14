#include "./persistence/databaseservice.h"
#include "./value-objects/user.h"

#include "QDebug"

#include "QSqlDatabase"
#include "QSqlQuery"
#include "QSqlError"


void printTableUser() {
    // print table user
    QSqlQuery q;
    q.exec("SELECT * FROM user;");
    while(q.next()) {
        int id = q.value(0).toInt();
        QString name = q.value(1).toString();
        QString password = q.value(2).toString();

        User user(id, name, password);
        qDebug() << user.getId() << ": " << user.getName() << " > " << user.getPassword();
    }
}

void fillDatabase() {
    QSqlQuery q1;
    if(q1.exec("CREATE TABLE IF NOT EXISTS user(id INTEGER PRIMARY KEY, name VARCHAR (50) NOT NULL UNIQUE, password VARCHAR (50) NOT NULL);")) {
        qDebug() << "Table user created!";
    } else {
        qDebug() << q1.lastError();
        return;
    }

    printTableUser();
}

void database::connectToDatabase() {
    // connect to database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("qsqlite");

    // test connection
    bool success = db.open();
    qDebug() << "Database connection established: " << success;

    fillDatabase();
}

void database::saveUser(QString name, QString password) {
    // fill table user with new values
    QSqlQuery q;
    q.prepare("INSERT INTO user(name, password) VALUES(:name, :password);");
    q.bindValue(":name", name);
    q.bindValue(":password", password);

    if(q.exec()) {
        qDebug() << "New user entered!";
    } else {
        qDebug() << q.lastError();
        return;
    }

    printTableUser();

}

