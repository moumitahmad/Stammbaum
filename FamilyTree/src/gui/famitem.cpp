/**
<<<<<<< HEAD
 * @author Moumita Ahmad, Alisa Schumman
=======
 * @author Moumita Ahmad, Alisa Schumann
>>>>>>> 38c1036d6ae0488591a64ed5471f946c82c9f520
 */

#include "famitem.h"
#include <QDebug>
#include <QImage>


// ---------------------- GROUP ------------------
famItem::famItem(int xPos, int yPos, int width, int height, Member* member, DisplayFam* parent, const bool& inEdit) :
    m_parent(parent),
    m_inEdit(inEdit),
    m_xPos(xPos),
    m_yPos(yPos),
    m_width(width),
    m_heigth(height),
    m_member(member)
{
    Pressed = false;
    QString path = "../src/images/";
    path.append(m_member->getImage());
    qDebug() << path;
    QImage img(path);


    m_imageItem = new itemPart(m_xPos, m_yPos, m_width, m_heigth/2, m_member, img);
    m_item = new itemPart(m_xPos, m_yPos+m_heigth/2, m_width, m_heigth/2, m_member);

    this->addToGroup(m_imageItem);
    this->addToGroup(m_item);

}

void famItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if(false) qDebug() << option << widget;
    if (Pressed) {
        QPen pen2(QColor(245, 121, 0), 3);
        painter->setPen(pen2);
    }
}

void famItem::setPressed(const bool &pressed)
{
    m_imageItem->setPressed(pressed);
    m_item->setPressed(pressed);
}

void famItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(false) qDebug() << event;
    if(m_inEdit) {
        Pressed = true;
        m_parent->memberSelected(m_member->getID());
        m_imageItem->setPressed(true);
        m_item->setPressed(true);
        update();
    }
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

}

QRectF itemPart::boundingRect() const {
    return QRectF(m_xPos,m_yPos,m_width,m_heigth);
}

void itemPart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if(false) qDebug() << option << widget;
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
    if(false) qDebug() << event;
    Pressed = true;
    qDebug() << "PART IS PRESSED";
    //memberChoosen(m_member->getID());
    update();
}

// ------------------- Button ----------------------

famItemBtn::famItemBtn(int xPos, int yPos, Member* member, bool isChild, DisplayFam *parent):
    m_xPos(xPos),
    m_yPos(yPos),
    m_member(member),
    m_isChild(isChild),
    m_parent(parent)
{
    Pressed = false;
}

QRectF famItemBtn::boundingRect() const {
    return QRectF(m_xPos-40, m_yPos,40,40);
}

void famItemBtn::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if(false) qDebug() << option << widget;
    QRectF rect = boundingRect();
    QPointF points[3];
    if (!m_isChild) {
        points[0] = QPointF(m_xPos-20, m_yPos);
        points[1] = QPointF(m_xPos, m_yPos+40);
        points[2] = QPointF(m_xPos-40, m_yPos+40);

    } else {
        points[0] = QPointF(m_xPos-40, m_yPos);
        points[1] = QPointF(m_xPos, m_yPos);
        points[2] = QPointF(m_xPos-20, m_yPos+40);

    }

    QPen pen(Qt::white, 1);
    QBrush brush(Qt::white);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRect(rect);
    QPen pen2(QColor(52, 101, 164), 1);
    QBrush brush2(QColor(52, 101, 164));
    painter->setPen(pen2);
    painter->setBrush(brush2);
    painter->drawPolygon(points, 3);


}

void famItemBtn::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(false) qDebug() << event;
    if (m_isChild){
        qDebug() << "IS PRESSED child";
        m_parent->updateDisplay(m_member->getID());
    } else {
        qDebug() << "IS PRESSED parent";
        QVector<Member *> mem = m_member->getParents();
        m_parent->updateDisplay(mem[0]->getID());
    }

}
