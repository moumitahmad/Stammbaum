#ifndef FAMITEM_H
#define FAMITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include "./value-objects/member.h"


// ----------------- ITEM ------------------
class itemPart : public QGraphicsItem {

public:
    itemPart(int xPos, int yPos, int width, int height, Member* member, QImage image = QImage());

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setPressed(const bool& pressed);

private:
    bool Pressed;

    int m_xPos;
    int m_yPos;
    int m_heigth;
    int m_width;
    Member* m_member;
    QImage m_image;

};



// ------------------- GROUP ----------------
class famItem : public QGraphicsItemGroup {

public:
    famItem(int xPos, int yPos, int width, int height, Member* member);
private:
    bool Pressed;
    int m_xPos;
    int m_yPos;
    int m_heigth;
    int m_width;
    Member* m_member;
    QImage m_image;
    itemPart* m_imageItem;
    itemPart* m_item;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

};


#endif // FAMITEM_H
