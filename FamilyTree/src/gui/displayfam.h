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

signals:
    void memberChoosen(int id); // id=-1 -> new Member

private slots:
    void changeMember(int id);
    void addNewMember();

private:
    Ui::DisplayFam *ui;

    QGraphicsScene *scene;
    QGraphicsRectItem *rect;
    QGraphicsRectItem *rect2;
    QGraphicsLineItem *line;
};

#endif // DISPLAYFAM_H
