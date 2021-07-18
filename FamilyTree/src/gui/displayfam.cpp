#include "displayfam.h"
#include "ui_displayfam.h"
#include <QDebug>
#include <QGraphicsItem>
#include "famitem.h"

famItem *item;
QVector<famItem*> items;

DisplayFam::DisplayFam(domain::ILogic* pLogic, QWidget *parent) :
    QWidget(parent),
    m_pLogic(pLogic),
    ui(new Ui::DisplayFam)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
}

void DisplayFam::changeView() {
    qDebug() << "changeview function";
    startpos = 0;
    paint();
}

void DisplayFam::updateDisplay(int memberID) {
    qDebug() << ">> IN DISPLAY: " << memberID;
    startpos = memberID;
    if (memberID==-1)
        return;

    paint();
}

void DisplayFam::memberSelected(int id) {
    for(famItem* i : items) {
        if(i->m_member->getID() != id) {
            i->setPressed(false);
        }
    }
    emit memberChoosen(id);
}

void DisplayFam::paintEvent(QPaintEvent *event) {
    //paint();
}

void DisplayFam::paint() {
    //reset
    this->scene->clear();
    items.clear();
    //delete item;

    int currentFamily = m_pLogic->getCurrentFamilyID();
    QVector<Member*>* familyMembers = m_pLogic->getMembersByFamily(currentFamily);

    if (!familyMembers)
        return;

    Member* treeStart;

    for(Member* m: *familyMembers) {
        if(startpos == 0) {
            if (m->getParents().length()<1) {
                treeStart = m;
                break;
            }
        } else if(m->getID() == startpos) {
            treeStart = m;
        }
    }

    QVector<Member*> allChildren = treeStart->getChildren();
    int childrenSize = allChildren.size();

    int startx = -200;
    int starty = -200;
    int widthRect = 180;
    int heightRect = 180;
    int distanceX = widthRect;
    int distanceY = heightRect-50;
    QPen redpen(Qt::red);


    item = new famItem(startx, starty, widthRect, heightRect, treeStart, this);
    scene->addItem(item);
    items.push_back(item);

    if (treeStart->getPartner()) {
      item = new famItem(startx+widthRect+distanceX,starty,widthRect,heightRect, treeStart->getPartner(), this);
      scene->addItem(item); //hier eventuell noch einige berechnungen und variablen einfügen
      items.push_back(item);

      line = scene->addLine(startx+widthRect,starty+heightRect/2, startx+widthRect+distanceX,starty+heightRect/2,redpen);
      if(childrenSize>0) {
         line = scene->addLine(startx+widthRect+distanceX/2, starty+heightRect/2, startx+widthRect+distanceX/2, starty+heightRect/2+distanceY, redpen);

      } else {
          return;
      }
    } else {
      if(childrenSize>0) {
          line = scene->addLine(startx+widthRect,starty+heightRect/2, startx+widthRect+distanceX/2,starty+heightRect/2,redpen);
          line = scene->addLine(startx+widthRect+distanceX/2, starty+heightRect/2, startx+widthRect+distanceX/2, starty+heightRect/2+distanceY, redpen);
      } else {
          return;
      }
    }

    int middlex = startx+widthRect/2+distanceX;
    int middley = starty+heightRect/2+distanceY;


    if(childrenSize % 2) { //ungerade
        int lineStart = middlex;
        int lineEnd = middlex;
        if (childrenSize>1) {
            lineStart -= distanceX+widthRect*(childrenSize-1)/2;
            lineEnd += distanceX+widthRect*(childrenSize-1)/2;
            line = scene->addLine(lineStart,middley,lineEnd,middley,redpen);
        }

       for (int i=0;i<childrenSize;i++) {
           line = scene->addLine(lineStart+(distanceX+widthRect)*i,middley,lineStart+(distanceX+widthRect)*i,middley+distanceY/2,redpen);
           item = new famItem(lineStart-widthRect/2+(distanceX+widthRect)*i,middley+distanceY/2,widthRect,heightRect, allChildren[i], this);
           scene->addItem(item);
           items.push_back(item);
       }
    } else if (!(childrenSize % 2)) { // gerade
        qDebug() << childrenSize;
        int lineStart = middlex-widthRect;
        int lineEnd = middlex+widthRect;

        if (childrenSize>2) {
            lineStart -= (childrenSize/2-1)*(distanceX+widthRect);
            lineEnd += (childrenSize/2-1)*(distanceX+widthRect);
        }
        line = scene->addLine(lineStart,middley,lineEnd,middley,redpen);
        for (int i=0;i<childrenSize;i++) {
            line = scene->addLine(lineStart+distanceX*2*i,middley,lineStart+distanceX*2*i,middley+distanceY/2,redpen);
            item = new famItem(lineStart-widthRect/2+distanceX*2*i,middley+distanceY/2,widthRect,heightRect, allChildren[i], this);
            scene->addItem(item);
            items.push_back(item);
        }

    }
}


DisplayFam::~DisplayFam()
{
    delete ui;
}

