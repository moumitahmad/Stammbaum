#include "famitem.h"
#include <QDebug>
#include <QImage>


// ---------------------- GROUP ------------------
famItem::famItem(int xPos, int yPos, int width, int height, Member* member) :
    m_xPos(xPos),
    m_yPos(yPos),
    m_width(width),
    m_heigth(height),
    m_member(member)
{
    Pressed = false;

    QImage defaultImg("/home/moumita/C++/AA_Project/Stammbaum/FamilyTree/src/images/defaultMember.png");


    m_imageItem = new itemPart(m_xPos, m_yPos, m_width, m_heigth/2, m_member, defaultImg);
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

void famItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    qDebug() << "IS PRESSED";
    //emit memberChoosen(m_member->getID());
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
        QString text = m_member->getName() + "\n" + age + "\n" + "Gender: " + m_member->getGender() + "\n" + m_member->getBiografie();
        painter->setFont(QFont("Sawasdee", 11));
        painter->drawText(rect, Qt::AlignLeft, text);
    } else {
        painter->drawImage(rect, m_image);
    }

    if (Pressed) {
        QPen pen2(QColor(245, 121, 0), 3);
        painter->setPen(pen2);
    }

    painter->drawRect(rect);
}

void itemPart::setPressed(const bool &pressed)
{
    Pressed = pressed;
}

void itemPart::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    qDebug() << "PART IS PRESSED";
    //emit memberChoosen(m_member->getID());
    update();
}
