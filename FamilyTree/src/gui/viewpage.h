#ifndef VIEWPAGE_H
#define VIEWPAGE_H

#include <QWidget>
#include "domain/ILogic.h"
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

    explicit ViewPage(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~ViewPage();

    void setFamily(int family) const;

private slots:
    void openEditPage();

private:
    Ui::ViewPage *ui;
};

#endif // VIEWPAGE_H
