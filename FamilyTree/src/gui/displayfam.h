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
    Member* getTreeStart();
    void closeEditPanel();

signals:
    Member* memberChoosen(int id); // id=-1 -> new Member
    void closeEditPanelSignal();

private:
    Ui::DisplayFam *ui;
    int startpos;
    Member* treeStart;
    QGraphicsScene *scene;
    QGraphicsRectItem *rect;
    QGraphicsRectItem *rect2;
    QGraphicsLineItem *line;    

    void paint();
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // DISPLAYFAM_H
