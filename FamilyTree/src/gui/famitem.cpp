#include "famitem.h"
#include <QDebug>

famItem::famItem(int xPos, int yPos, int width, int height, Member* member) :
    m_xPos(xPos),
    m_yPos(yPos),
    m_width(width),
    m_heigth(height),
    m_member(member)
{
    Pressed = false;
    //qDebug() << m_xPos<<"xpos"; // TODO: wird die ganze zeit aufgerufen

}

QRectF famItem::boundingRect() const{
    return QRectF(m_xPos,m_yPos,m_width,m_heigth);
}

void famItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
   // QBrush brush(Qt::black);
    QPen pen(Qt::black, 3);
    painter->setPen(pen);

    if (Pressed) {
        QPen pen2(Qt::red, 3);
        painter->setPen(pen2);
        painter->drawText(rect, Qt::AlignCenter, m_member->getName());
    }
    painter->drawRect(rect);
}

void famItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    update();
}
