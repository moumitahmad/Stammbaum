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

    void setupForView();
    void setupForEdit();
    void changeView();
    void updateDisplay(int memberID);
    void memberSelected(int id);

signals:
    void memberChoosen(int id); // id=-1 -> new Member

private:
    Ui::DisplayFam *ui;
    Member* treeStart;
    QVector<Member*>* familyMembers;
    QGraphicsScene *scene;
    QGraphicsRectItem *rect;
    QGraphicsRectItem *rect2;
    QGraphicsLineItem *line;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // DISPLAYFAM_H
