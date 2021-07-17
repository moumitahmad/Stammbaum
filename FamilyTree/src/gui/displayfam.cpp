#include "displayfam.h"
#include "ui_displayfam.h"
#include <QDebug>
#include <QGraphicsItem>


DisplayFam::DisplayFam(domain::ILogic* pLogic, QWidget *parent) :
    QWidget(parent),
    m_pLogic(pLogic),
    ui(new Ui::DisplayFam)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

 //   this->update();


//    int currentFamily = m_pLogic->getCurrentFamilyID();
//    QVector<Member*>* familyMembers = m_pLogic->getMembersByFamily(1);   //currentFamily);
//    Member* treeStart;


//    for(Member* m: *familyMembers) {
//        if (m->getParents().length()<1) {
//            treeStart=m;
//            break;
//        }
//    }
//    QVector<Member*> allChildren = treeStart->getChildren();





//        int startx = -100;
//        int starty = -100;
//        int startxSave = startx;
//        int startySave = starty;
//        int widthRect = 100;
//        QPen redpen(Qt::red);


//        item = new famItem(startx,starty,widthRect,widthRect, treeStart);
//        scene->addItem(item);


//          if (treeStart->getPartner()) {
//              item = new famItem(startx+200,starty,widthRect,widthRect, treeStart->getPartner());
//              scene->addItem(item); //hier eventuell noch einige berechnungen und variablen einfügen
//              startx += 200;
//              line = scene->addLine(startxSave+widthRect,startySave+widthRect/2, startx,starty+widthRect/2,redpen);
//              line = scene->addLine(50, -50, 50, 50, redpen);
//          } // Else wenn es nur ein elternteil gibt andernfalls könnte man ein icom mit unbekannt einfügen wenn elternteil nicht bekannt ist



//    // eltern zeichnen
//    // kinder zeichnen
//        int middlex = 50;
//        int middley = 50;
//        int childrenSize = allChildren.size();

//        if(childrenSize % 2) { //ungerade
//            int lineStart = middlex;
//            int lineEnd = middlex;
//            if (childrenSize>1) {
//                lineStart -= 200*(childrenSize-1)/2;
//                lineEnd += 200*(childrenSize-1)/2;
//                line = scene->addLine(lineStart,middley,lineEnd,middley,redpen);
//            }

//           for (int i=0;i<childrenSize;i++) {
//               line = scene->addLine(lineStart+200*i,middley,lineStart+200*i,middley+50,redpen);
//               item = new famItem(lineStart-50+200*i,middley+50,widthRect,widthRect, allChildren[i]);
//               scene->addItem(item);
//           }
//        } else if (!(childrenSize % 2)) { // gerade
//            qDebug() << childrenSize;
//            int lineStart = middlex-100;
//            int lineEnd = middlex+100;

//            if (childrenSize>2) {
//                lineStart -= (childrenSize/2-1)*200;
//                lineEnd += (childrenSize/2-1)*200;
//            }
//            line = scene->addLine(lineStart,middley,lineEnd,middley,redpen);
//            for (int i=0;i<childrenSize;i++) {
//                line = scene->addLine(lineStart+200*i,middley,lineStart+200*i,middley+50,redpen);
//                item = new famItem(lineStart-50+200*i,middley+50,widthRect,widthRect, allChildren[i]);
//                scene->addItem(item);
//            }

//        }





    //wenn es noch kinder von kindern gibt, buttons einfügen




//    QBrush redBrush(Qt::red);
//    QBrush blueBrush(Qt::blue);
//    QPen blackpen(Qt::black);
//    QPen redpen(Qt::red);
//    blackpen.setWidth(6);
//    redpen.setWidth(6);
//    //int foo[] = { 1, 2, 3, 4, 5 }; // Eltern Array laden
// //   int arrSize = sizeof(foo)/sizeof(foo[0]);
//    int arrSize = 2;
//    int startx = -100;
//    int starty = -100;
//    int startxSave = startx;
//    int startySave = starty;
//    int widthRect = 100;

//    rect = scene->addRect(-300,100,100,100,blackpen);
//    rect->setFlag(QGraphicsItem::ItemIsSelectable);

//    for (int i =0;i<arrSize;i++) {
//      rect = scene->addRect(startx,starty,widthRect,widthRect,redpen);
//      rect->setFlag(QGraphicsItem::ItemIsSelectable);


//      if (arrSize >1 && i > 0) {

//          line = scene->addLine(startxSave+widthRect,startySave+widthRect/2, startx,starty+widthRect/2,redpen);
//          line = scene->addLine(50, -50, 50, 50, redpen);
//      } // Else wenn es nur ein elternteil gibt andernfalls könnte man ein icom mit unbekannt einfügen wenn elternteil nicht bekannt ist
//      startx += 200;
//  }

//    line = scene->addLine(-50,50,150,50,blackpen);
//    //rechts
//    line = scene->addLine(-50,50,-50,100,blackpen);
//    rect = scene->addRect(-100,100,100,100,blackpen);

//    //links
//    line = scene->addLine(150,50,150,100,blackpen);
//    rect = scene->addRect(100,100,100,100,blackpen);

//    line = scene->addLine(150,50,350,50,blackpen);
//    line = scene->addLine(350,50,350,100,blackpen);
//    rect = scene->addRect(300,100,100,100,blackpen);

//    line = scene->addLine(-50,50,-250,50,blackpen);
//    line = scene->addLine(-250,50,-250,100,blackpen);
//    rect = scene->addRect(-300,100,100,100,blackpen);


}

void DisplayFam::changeView() {
    qDebug() << "changeview function";

    this->update();

}

void DisplayFam::updateDisplay(int memberID) {
    qDebug() << ">> IN DISPLAY: " << memberID;

}

void DisplayFam::paintEvent(QPaintEvent *event) {



    int currentFamily = m_pLogic->getCurrentFamilyID();
    QVector<Member*>* familyMembers = m_pLogic->getMembersByFamily(currentFamily);

//    bool bo = familyMembers->empty();

    if (!familyMembers)
        return;

    Member* treeStart;


    for(Member* m: *familyMembers) {
        if (m->getParents().length()<1) {
            treeStart=m;
            break;
        }
    }
    QVector<Member*> allChildren = treeStart->getChildren();
    int childrenSize = allChildren.size();




        int startx = -200;
        int starty = -200;
        int widthRect = 150;
        int heightRect = 200;
        int distanceX = widthRect;
        int distanceY = heightRect-50;
        QPen redpen(Qt::red);



        item = new famItem(startx,starty,widthRect,heightRect, treeStart);
        scene->addItem(item);


          if (treeStart->getPartner()) {
              item = new famItem(startx+widthRect+distanceX,starty,widthRect,heightRect, treeStart->getPartner());
              scene->addItem(item); //hier eventuell noch einige berechnungen und variablen einfügen
      //        startx += 200;
              line = scene->addLine(startx+widthRect,starty+heightRect/2, startx+widthRect+distanceX,starty+heightRect/2,redpen);
              if(childrenSize>0) {
                 line = scene->addLine(startx+widthRect+distanceX/2, starty+heightRect/2, startx+widthRect+distanceX/2, starty+heightRect/2+distanceY, redpen);
              }
          } else {
              if(childrenSize>0) {
                  line = scene->addLine(startx+widthRect,starty+heightRect/2, startx+widthRect+distanceX/2,starty+heightRect/2,redpen);
                  line = scene->addLine(startx+widthRect+distanceX/2, starty+heightRect/2, startx+widthRect+distanceX/2, starty+heightRect/2+distanceY, redpen);
              }
          }


        int middlex = startx+widthRect/2+distanceX;
        int middley = starty+heightRect/2+distanceY;


//        if(childrenSize=0) {
//            return;

//        } else {
//            return;
//        }

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
               item = new famItem(lineStart-widthRect/2+(distanceX+widthRect)*i,middley+distanceY/2,widthRect,heightRect, allChildren[i]);
               scene->addItem(item);
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
                item = new famItem(lineStart-widthRect/2+distanceX*2*i,middley+distanceY/2,widthRect,heightRect, allChildren[i]);
                scene->addItem(item);
            }

        }
    }





DisplayFam::~DisplayFam()
{
    delete ui;
}

