#ifndef DISPLAYFAM_H
#define DISPLAYFAM_H

#include <QWidget>
#include <QGraphicsScene>
#include "./domain/ILogic.h"
#include "famitem.h"

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

    void setupForView();
    void setupForEdit();
    void changeView();

signals:
    void memberChoosen(int id); // id=-1 -> new Member

private:
    Ui::DisplayFam *ui;

    QGraphicsScene *scene;
    famItem *item;
    QGraphicsRectItem *rect;
    QGraphicsRectItem *rect2;
    QGraphicsLineItem *line;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // DISPLAYFAM_H
