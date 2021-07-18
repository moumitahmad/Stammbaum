#ifndef FAMITEM_H
#define FAMITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include "./value-objects/member.h"
#include "displayfam.h"

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

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

};



// ------------------- GROUP ----------------
class famItem : public QGraphicsItemGroup {

public:
    famItem(int xPos, int yPos, int width, int height, Member* member, DisplayFam* parent);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setPressed(const bool& pressed);
    Member* m_member;
private:
    DisplayFam* m_parent;
    bool Pressed;
    int m_xPos;
    int m_yPos;
    int m_heigth;
    int m_width;
    QImage m_image;
    itemPart* m_imageItem;
    itemPart* m_item;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

/* BUtton */

//class famItemBtn : public QGraphicsItem {

//public:
//    famItemBtn(int xPos, int yPos, Member* member);
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//    void setPressed(const bool& pressed);
//    Member* m_member;
//private:
//    DisplayFam* m_parent;
//    bool Pressed;
//    int m_xPos;
//    int m_yPos;
//    int m_heigth;
//    int m_width;
//    QImage m_image;
//    itemPart* m_imageItem;
//    itemPart* m_item;

//protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);

//};


#endif // FAMITEM_H
