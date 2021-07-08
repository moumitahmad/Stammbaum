#ifndef EDITPAGE_H
#define EDITPAGE_H

#include <QWidget>
#include "domain/ILogic.h"
#include "./value-objects/familytree.h"

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

    void setupEditPage();

signals:
    void switchToView();

private slots:
    void openViewPage();

private:
    Ui::EditPage *ui;
};

#endif // EDITPAGE_H
