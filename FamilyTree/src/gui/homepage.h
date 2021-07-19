/**
 * @author Moumita Ahmad
 */

#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include "domain/ILogic.h"
#include "./value-objects/user.h"

namespace Ui {
class Homepage;
}

class Homepage : public QWidget
{
    Q_OBJECT

public:
    explicit Homepage(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~Homepage();

    void displayFamilies();

signals:
    void switchToView();
    void drawFamily();

private slots:
    void showFamily(int id);
    void addFamily();

private:
    domain::ILogic* m_pLogic;
    User* m_currentUser;

    Ui::Homepage *ui;
};

#endif // HOMEPAGE_H
