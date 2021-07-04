#ifndef VIEWPAGE_H
#define VIEWPAGE_H

#include <QWidget>
#include "./value-objects/familytree.h"

namespace Ui {
class ViewPage;
}

class ViewPage : public QWidget
{
    Q_OBJECT

public:
    domain::ILogic* m_pLogic;
    FamilyTree* m_displayedFamily;

    explicit ViewPage(domain::ILogic* pLogic, FamilyTree* displayedFamily, QWidget *parent = nullptr);
    ~ViewPage();

private slots:
    void openEditPage();

private:
    Ui::ViewPage *ui;
};

#endif // VIEWPAGE_H
