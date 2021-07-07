#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QWidget>
#include "domain/ILogic.h"
#include "./value-objects/familytree.h"

namespace Ui {
class AdminPanel;
}

class AdminPanel : public QWidget
{
    Q_OBJECT

public:
    domain::ILogic* m_pLogic;
    FamilyTree* m_displayedFamily;

    explicit AdminPanel(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~AdminPanel();

    void setupAdminPanel();

signals:
    void switchToHome();

private slots:
    void addEditor();
    void addViewer();
    void deleteFamily();

private:
    Ui::AdminPanel *ui;
};

#endif // ADMINPANEL_H
