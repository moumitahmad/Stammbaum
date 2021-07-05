#ifndef EDITPAGE_H
#define EDITPAGE_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class EditPage;
}

class EditPage : public QWidget
{
    Q_OBJECT

public:
    domain::ILogic* m_pLogic;
    FamilyTree* m_displayedFamily;

    explicit EditPage(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~EditPage();

    void setFamily(int family) const;

signals:
    void switchToView();

private slots:
    void uploadPicture();
    void saveChanges();
    void discardChanges();
    void openViewPage();

private:
    Ui::EditPage *ui;
};

#endif // EDITPAGE_H
