/**
 * @author Moumita Ahmad
 */

#include "familytree.h"
#include <QDebug>

FamilyTree::~FamilyTree() {
    delete m_admin;
    for(User* user : m_viewers) {
        delete user;
    }
    for(User* user : m_editors) {
        delete user;
    }
}

int FamilyTree::getId() const {
    return m_id;
}

QString FamilyTree::getFamilyName() {
    return m_name;
}

User* FamilyTree::getAdmin() {
    return m_admin;
}

QVector<User*> FamilyTree::getEditors() {
    return m_editors;
}

QVector<User*> FamilyTree::getViewers() {
    return m_viewers;
}

void FamilyTree::addEditor(User* editor) {
    m_editors.append(editor);
}

void FamilyTree::addViewer(User* viewer) {
    m_viewers.append(viewer);
}
