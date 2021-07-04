#ifndef EDITPAGE_H
#define EDITPAGE_H

#include <QWidget>
#include "domain/ILogic.h"

namespace Ui {
class EditPage;
}

class EditPage : public QWidget
{
    Q_OBJECT

public:
    domain::ILogic* m_pLogic;

    explicit EditPage(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~EditPage();

private:
    Ui::EditPage *ui;
};

#endif // EDITPAGE_H
