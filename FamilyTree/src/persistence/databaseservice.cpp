#include "./persistence/databaseservice.h"
#include "./value-objects/user.h"
#include "./value-objects/familytree.h"

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

        User* user = new User(id, name, password);
        qDebug() << user->getId() << ": " << user->getName() << " > " << user->getPassword();
    }
}

void fillDatabase() {
    // table user
    QSqlQuery q1;
    if(q1.exec("CREATE TABLE IF NOT EXISTS user("
               "id INTEGER PRIMARY KEY, "
               "name VARCHAR (50) NOT NULL UNIQUE, "
               "password VARCHAR (50) NOT NULL"
               ");")) {
        qDebug() << "Table user created!";
    } else {
        qDebug() << q1.lastError();
        return;
    }
    printTableUser();

    // table familytree
    QSqlQuery q2;
    if(q2.exec("CREATE TABLE IF NOT EXISTS familytree("
               "id INTEGER PRIMARY KEY, "
               "name VARCHAR (50) NOT NULL UNIQUE, "
               "adminID INTEGER NOT NULL"
               ");")) {
        qDebug() << "Table familytree created!";
    } else {
        qDebug() << q2.lastError();
        return;
    }

    // table member
    QSqlQuery q3;
    if(q3.exec("CREATE TABLE IF NOT EXISTS member("
               "id INTEGER PRIMARY KEY, "
               "name VARCHAR (50) NOT NULL, "
               "birth VARCHAR (50) NOT NULL, "
               "death VARCHAR (50), "
               "gender VARCHAR (50), " // ENUM('female', 'male', 'diverse', 'unknown')
               "biografie VARCHAR (50), "
               "picturePath VARCHAR (50), "
               "partnerID INTEGER NOT NULL, "
               "familyID INTEGER NOT NULL"
               ");")) {
        qDebug() << "Table member created!";
    } else {
        qDebug() << q3.lastError();
        return;
    }

    // table parent
    QSqlQuery q4;
    if(q4.exec("CREATE TABLE IF NOT EXISTS hasParent("
               "childID INTEGER NOT NULL, "
               "parentID INTEGER NOT NULL"
               ");")) {
        qDebug() << "Table hasParent created!";
    } else {
        qDebug() << q4.lastError();
        return;
    }

    // table rights
    QSqlQuery q5;
    if(q5.exec("CREATE TABLE IF NOT EXISTS hasRights("
               "familyID INTEGER NOT NULL, "
               "userID INTEGER NOT NULL, "
               "authorization VARCHAR (50) NOT NULL" // ENUM('viewer', 'editor')
               ");")) {
        qDebug() << "Table hasRigths created!";
    } else {
        qDebug() << q5.lastError();
        return;
    }
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

FamilyTree* selectFamilyByID(QString familyID) {
    QSqlQuery q;
    q.exec("SELECT * FROM familytree WHERE id=" + familyID + ";");
    int id = q.value(0).toInt();
    QString name = q.value(1).toString();
    QString adminID = q.value(2).toString();

    QSqlQuery q1;
    q1.exec("SELECT * FROM user WHERE id=" + adminID + ";");
    QString adminName = q1.value(1).toString();
    QString adminPassword = q1.value(2).toString();
    User* admin = new User(q1.value(0).toInt(), adminName, adminPassword);

    FamilyTree* family = new FamilyTree(id, name, admin);
    return family;
}

User* selectUserByID(QString userID) {
    // print table user
    QSqlQuery q;
    q.exec("SELECT * FROM user WHERE id=" + userID + ";");
    int id = q.value(0).toInt();
    QString name = q.value(1).toString();
    QString password = q.value(2).toString();

    User* user = new User(id, name, password);
    return user;
}

void printFamilyTable() {
    // print table user
    qDebug() << ">> FamilyTree table:";
    QSqlQuery q;
    q.exec("SELECT * FROM familytree;");
    while(q.next()) {
        int id = q.value(0).toInt();
        QString name = q.value(1).toString();
        QString adminID = q.value(2).toString();

        QSqlQuery q1;
        q1.exec("SELECT * FROM user WHERE id=" + adminID + ";");
        int userId = q1.value(0).toInt();
        QString userName = q.value(1).toString();
        QString password = q.value(2).toString();
        User* admin = new User(userId, userName, password);

        FamilyTree* family = new FamilyTree(id, name, admin);
        qDebug() << family->getId() << ": " << family->getFamilyName() << ", " << family->getAdmin()->getName();
    }
}

void printHasRightsTable() {
    qDebug() << ">> hasRights table:";
    QSqlQuery q;
    q.exec("SELECT * FROM hasRights;");
    while(q.next()) {
        QString familyID = q.value(0).toString();
        QString userID = q.value(1).toString();
        QString authorization = q.value(2).toString();

        FamilyTree *family = selectFamilyByID(familyID);
        User* user = selectUserByID(userID);
        if(authorization == 'editor') {
            family->addEditor(user);
        } else {
            family->addViewer(user);
        }
        qDebug() << "In family " << family->getFamilyName() << " " << user->getName() << " = " << authorization;
    }
}

void database::saveFamily(QString name, int adminID, QVector<int> editorIDs, QVector<int> viewerIDs) {
    // insert into familytree
    QSqlQuery q;
    q.prepare("INSERT INTO familytree(name, adminID) VALUES(:name, :adminID);");
    q.bindValue(":name", name);
    q.bindValue(":adminID", adminID);

    if(q.exec()) {
        qDebug() << "New family entered!";
    } else {
        qDebug() << q.lastError();
        return;
    }
    int id = q.value(0).toInt();

    // insert connections
    QSqlQuery q1;
    for(int i = 0; i<editorIDs.length(); i++) {
        q1.prepare("INSERT INTO hasRights(familyID, userID, authorization) VALUES(:familyID, :userID, :authorization);");
        q1.bindValue(":familyID", editorIDs[i]);
        q1.bindValue(":userID", id);
        q1.bindValue(":authorization", 'editor');

        if(q1.exec()) {
            qDebug() << "New editor entered!";
        } else {
            qDebug() << q1.lastError();
            return;
        }
    }

    for(int i = 0; i<viewerIDs.length(); i++) {
        q1.prepare("INSERT INTO hasRights(familyID, userID, authorization) VALUES(:familyID, :userID, :authorization);");
        q1.bindValue(":familyID", viewerIDs[i]);
        q1.bindValue(":userID", id);
        q1.bindValue(":authorization", 'viewer');

        if(q1.exec()) {
            qDebug() << "New viewer entered!";
        } else {
            qDebug() << q1.lastError();
            return;
        }
    }

    printFamilyTable();
    printHasRightsTable();
}
