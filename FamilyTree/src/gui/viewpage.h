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

   void getDisplayedFamily();

signals:
    void switchToEdit();
    void switchToHome();

private slots:
    void openEditPage();
    void addEditor();
    void addViewer();
    void deleteFamily();

private:
    Ui::ViewPage *ui;
};

#endif // VIEWPAGE_H
