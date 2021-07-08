#ifndef DISPLAYFAM_H
#define DISPLAYFAM_H

#include <QWidget>
#include <QGraphicsScene>
#include "./domain/ILogic.h"

namespace Ui {
class DisplayFam;
}

class DisplayFam : public QWidget
{
    Q_OBJECT

public:
    int family;
    domain::ILogic* m_pLogic;
    explicit DisplayFam(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~DisplayFam();

signals:
    void memberChoosen();

private slots:
    void changeMember();

private:
    Ui::DisplayFam *ui;

    QGraphicsScene *scene;
    QGraphicsRectItem *rect;
    QGraphicsRectItem *rect2;
    QGraphicsLineItem *line;
};

#endif // DISPLAYFAM_H
