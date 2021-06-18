#include "./persistence/databaseservice.h"
#include "./value-objects/user.h"
#include "./value-objects/familytree.h"

#include "QDebug"

#include "QSqlDatabase"
#include "QSqlQuery"
#include "QSqlError"

// --------------- local methodes ---------------
// user
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

void database::printTableUser() {
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

// FamilyTree
void database::printFamilyTable() {
    // print table user
    qDebug() << ">> FamilyTree table:";
    QSqlQuery q;
    if(q.exec("SELECT * FROM familytree;")) {
        qDebug() << "got family";
        while(q.next()) {
            int id = q.value(0).toInt();
            QString name = q.value(1).toString();
            QString adminID = q.value(2).toString();
            qDebug() << name << ", " << adminID;

            QSqlQuery q1;
            if(q1.exec("SELECT * FROM user WHERE id=" + adminID + ";")) {
                int userID = q1.value(0).toInt();
                QString userName = q1.value(1).toString();
                QString password = q1.value(2).toString();
                qDebug() << userID << ", " << userName << ", " << password;
                User* admin = new User(userID, userName, password);

                FamilyTree* family = new FamilyTree(id, name, admin);
                qDebug() << family->getId() << ": " << family->getFamilyName() << ", " << family->getAdmin()->getName();
            } else {
                qDebug() << q1.lastError();
            }
        }
    } else {
        qDebug() << q.lastError();
    }
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

void database::printHasRightsTable() {
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

// database
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


// --------------- database methodes ---------------
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

// User
User* database::saveUser(QString name, QString password) {
    // fill table user with new values
    QSqlQuery q;
    q.prepare("INSERT INTO user(name, password) VALUES(:name, :password);");
    q.bindValue(":name", name);
    q.bindValue(":password", password);

    if(q.exec()) {
        qDebug() << "New user entered!";
    } else {
        qDebug() << q.lastError();
    }
    User* user = new User(q.lastInsertId().toInt(), name, password);
    return user;
}

// FamilyTree
FamilyTree* database::saveFamily(QString name, User* admin) {
    // insert into familytree
    QSqlQuery q;
    q.prepare("INSERT INTO familytree(name, adminID) VALUES(:name, :adminID);");
    q.bindValue(":name", name);
    q.bindValue(":adminID", admin->getId());

    if(q.exec()) {
        qDebug() << "New family entered!";
    } else {
        qDebug() << q.lastError();
    }
    FamilyTree* family = new FamilyTree(q.lastInsertId().toInt(), name, admin);
    return family;
}

void database::saveEditor(int familyID, User* editor) {
    QSqlQuery q;
    q.prepare("INSERT INTO hasRights(familyID, userID, authorization) VALUES(:familyID, :userID, :authorization);");
    q.bindValue(":familyID", familyID);
    q.bindValue(":userID", editor->getId());
    q.bindValue(":authorization", 'editor');

    if(q.exec()) {
        qDebug() << "New editor entered!";
    } else {
        qDebug() << q.lastError();
        return;
    }
}

void database::saveViewer(int familyID, User* viewer) {
    QSqlQuery q;
    q.prepare("INSERT INTO hasRights(familyID, userID, authorization) VALUES(:familyID, :userID, :authorization);");
    q.bindValue(":familyID", familyID);
    q.bindValue(":userID", viewer->getId());
    q.bindValue(":authorization", 'viewer');

    if(q.exec()) {
        qDebug() << "New viewer entered!";
    } else {
        qDebug() << q.lastError();
        return;
    }
}
