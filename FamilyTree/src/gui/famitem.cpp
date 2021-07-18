#include "famitem.h"
#include <QDebug>
#include <QImage>


// ---------------------- GROUP ------------------
famItem::famItem(int xPos, int yPos, int width, int height, Member* member, DisplayFam* parent) :
    m_parent(parent),
    m_xPos(xPos),
    m_yPos(yPos),
    m_width(width),
    m_heigth(height),
    m_member(member)
{
    Pressed = false;
    QString path = "../src/images/"; //+ m_member->getImagePath;
    //if(!m_member->getImagePath)
    path += "defaultMember.png";
    QImage img(path);


    m_imageItem = new itemPart(m_xPos, m_yPos, m_width, m_heigth/2, m_member, img);
    m_item = new itemPart(m_xPos, m_yPos+m_heigth/2, m_width, m_heigth/2, m_member);

    this->addToGroup(m_imageItem);
    this->addToGroup(m_item);
}

void famItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (Pressed) {
        QPen pen2(QColor(245, 121, 0), 3);
        painter->setPen(pen2);
    }
}

void famItem::setPressed(const bool &pressed)
{
    m_imageItem->setPressed(false);
    m_item->setPressed(false);
}

void famItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    qDebug() << "IS PRESSED";
    m_parent->memberSelected(m_member->getID());
    m_imageItem->setPressed(true);
    m_item->setPressed(true);
    update();
}



// ------------------- PART ----------------------
itemPart::itemPart(int xPos, int yPos, int width, int height, Member* member, QImage image) :
    m_xPos(xPos),
    m_yPos(yPos),
    m_width(width),
    m_heigth(height),
    m_member(member),
    m_image(image)
{
    Pressed = false;
    //qDebug() << "ITEMPART"; // TODO: wird die ganze zeit aufgerufen

}

QRectF itemPart::boundingRect() const {
    return QRectF(m_xPos,m_yPos,m_width,m_heigth);
}

void itemPart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

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
        QPen pen2(QColor(245, 121, 0), 5);
        painter->setPen(pen2);
    }
    painter->drawRect(rect);
}

void itemPart::setPressed(const bool &pressed)
{
    Pressed = pressed;
    update();
}

void itemPart::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    qDebug() << "PART IS PRESSED";
    //memberChoosen(m_member->getID());
    update();
}
