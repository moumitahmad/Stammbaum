#ifndef FAMITEM_H
#define FAMITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include "./value-objects/member.h"

class famItem : public QGraphicsItem {

public:
    famItem(int xPos, int yPos, int width, int height, Member* member, QImage image = QImage());

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool Pressed;

    int m_xPos;
    int m_yPos;
    int m_heigth;
    int m_width;
    Member* m_member;
    QImage m_image;

signals:
    void memberChoosen(int id);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

#endif // FAMITEM_H
