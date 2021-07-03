#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include "domain/ILogic.h"

namespace Ui {
class Homepage;
}

class Homepage : public QWidget
{
    Q_OBJECT

public:
    domain::ILogic* m_pLogic;

    explicit Homepage(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~Homepage();

private:
    Ui::Homepage *ui;
};

#endif // HOMEPAGE_H
