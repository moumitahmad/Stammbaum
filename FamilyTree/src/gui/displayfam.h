#ifndef DISPLAYFAM_H
#define DISPLAYFAM_H

#include <QWidget>
#include "./domain/ILogic.h"

namespace Ui {
class DisplayFam;
}

class DisplayFam : public QWidget
{
    Q_OBJECT

public:
    domain::ILogic* m_pLogic;
    explicit DisplayFam(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~DisplayFam();

private:
    Ui::DisplayFam *ui;
};

#endif // DISPLAYFAM_H
