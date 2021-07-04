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
    domain::ILogic* m_pLogic;
    User* m_currentUser;

    explicit Homepage(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~Homepage();

    void displayFamilies();

private slots:
    void showFamily(int id);
    void addFamily();

private:
    Ui::Homepage *ui;
};

#endif // HOMEPAGE_H