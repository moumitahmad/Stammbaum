#ifndef EDITFAMILYWINDOW_H
#define EDITFAMILYWINDOW_H


#include "./domain/ILogic.h"
#include <QWidget>
#include <QGraphicsScene>

namespace Ui {
class editFamilyWindow;
}

class editFamilyWindow : public QWidget
{
    Q_OBJECT

public:
    domain::ILogic* m_pLogic;

    explicit editFamilyWindow(domain::ILogic* pLogic, QWidget *parent = nullptr);
    ~editFamilyWindow();

private:
    Ui::editFamilyWindow *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rect;
    QGraphicsRectItem *rect2;
    QGraphicsLineItem *line;
};

#endif // EDITFAMILYWINDOW_H
