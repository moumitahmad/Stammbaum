#ifndef FAMILYTREE_H
#define FAMILYTREE_H

#include "user.h"
#include <QVector>

class FamilyTree {
public:
    FamilyTree(int id, QString name, User* admin): m_id(id), m_name(name), m_admin(admin) {}
    ~FamilyTree();

    // methodes
    int getId();
    QString getFamilyName();
    User* getAdmin();
    QVector<User*> getEditors();
    QVector<User*> getViewers();

    void addEditor(User* editor);
    void addViewer(User* viewer);

private:
    int m_id;
    QString m_name;
    User* m_admin;
    QVector<User*> m_editors;
    QVector<User*> m_viewers;
};

#endif // FAMILYTREE_H
