#include "famitem.h"
#include <QDebug>
#include <QImage>

famItem::famItem(int xPos, int yPos, int width, int height, Member* member) :
    m_xPos(xPos),
    m_yPos(yPos),
    m_width(width),
    m_heigth(height),
    m_member(member),
    m_image(image)
{
    Pressed = false;
    //qDebug() << m_xPos<<"xpos"; // TODO: wird die ganze zeit aufgerufen

}

QRectF famItem::boundingRect() const {
    return QRectF(m_xPos,m_yPos,m_width,m_heigth);
}

void famItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QRectF rect = boundingRect();
   // QBrush brush(Qt::black);
    QPen pen(Qt::black, 1);
    painter->setPen(pen);
    if(m_image.isNull()) {
        QString age = m_member->getBirth() + " to " + m_member->getDeath();
        QString text = m_member->getName() + "\n" + age + "\n" + "Gender: " + m_member->getGender();
        painter->setFont(QFont("Sawasdee", 11));
        painter->drawText(rect, Qt::AlignCenter, text);
    } else {
        painter->drawImage(rect, m_image);
    }

    if (Pressed) {
        QPen pen2(QColor(245, 121, 0), 3);
        painter->setPen(pen2);
    }
    painter->drawRect(rect);
}

void famItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    //emit memberChoosen(m_member->getID());
    update();
}
