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

    // connect test-buttons
    QObject::connect(ui->addMember, &QPushButton::clicked, this, &DisplayFam::addNewMember);
    QObject::connect(ui->updateMember, &QPushButton::clicked, std::bind(&DisplayFam::changeMember, this, 1));


//    int currentFamily = m_pLogic->getCurrentFamilyID();
    QVector<Member*>* familyMembers = m_pLogic->getMembersByFamily(1);   //currentFamily);
    Member* treeStart;


    for(Member* m: *familyMembers) {
        if (m->getParents().length()<1) {
            treeStart=m;
            break;
        }
    }
    QVector<Member*> allChildren = treeStart->getChildren();


    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);


        int startx = -100;
        int starty = -100;
        int startxSave = startx;
        int startySave = starty;
        int widthRect = 100;
        QPen redpen(Qt::red);


        item = new famItem(startx,starty,widthRect,widthRect, treeStart);
        scene->addItem(item);


          if (treeStart->getPartner()) {
              item = new famItem(startx+200,starty,widthRect,widthRect, treeStart->getPartner());
              scene->addItem(item); //hier eventuell noch einige berechnungen und variablen einfügen
              startx += 200;
              line = scene->addLine(startxSave+widthRect,startySave+widthRect/2, startx,starty+widthRect/2,redpen);
              line = scene->addLine(50, -50, 50, 50, redpen);
          } // Else wenn es nur ein elternteil gibt andernfalls könnte man ein icom mit unbekannt einfügen wenn elternteil nicht bekannt ist



    // eltern zeichnen
    // kinder zeichnen
        int middlex = 50;
        int middley = 50;
        int childrenSize = allChildren.size();

        if(childrenSize % 2) { //ungerade
            int lineStart = middlex;
            int lineEnd = middlex;
            if (childrenSize>1) {
                lineStart -= 200*(childrenSize-1)/2;
                lineEnd += 200*(childrenSize-1)/2;
                line = scene->addLine(lineStart,middley,lineEnd,middley,redpen);
            }

           for (int i=0;i<childrenSize;i++) {
               line = scene->addLine(lineStart+200*i,middley,lineStart+200*i,middley+50,redpen);
               item = new famItem(lineStart-50+200*i,middley+50,widthRect,widthRect, allChildren[i]);
               scene->addItem(item);
           }
        } else if (!(childrenSize % 2)) { // gerade
            qDebug() << childrenSize;
            int lineStart = middlex-100;
            int lineEnd = middlex+100;

            if (childrenSize>2) {
                lineStart -= (childrenSize/2-1)*200;
                lineEnd += (childrenSize/2-1)*200;
            }
            line = scene->addLine(lineStart,middley,lineEnd,middley,redpen);
            for (int i=0;i<childrenSize;i++) {
                line = scene->addLine(lineStart+200*i,middley,lineStart+200*i,middley+50,redpen);
                item = new famItem(lineStart-50+200*i,middley+50,widthRect,widthRect, allChildren[i]);
                scene->addItem(item);
            }

        }





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



DisplayFam::~DisplayFam()
{
    delete ui;
}

void DisplayFam::mousePressEvent(QMouseEvent *event) {
    qDebug() << scene->selectedItems();
}

void DisplayFam::setupForView() {
    ui->addMember->hide();
    ui->updateMember->hide();
}

void DisplayFam::setupForEdit() {
    ui->addMember->show();
    ui->updateMember->show();
}

void DisplayFam::changeMember(int id) {
    emit memberChoosen(id);
}

void DisplayFam::addNewMember() {
    emit memberChoosen(-1);
}
