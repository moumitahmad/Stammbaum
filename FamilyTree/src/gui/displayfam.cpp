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

    QObject::connect(ui->addMember, &QPushButton::clicked, this, &DisplayFam::addNewMember);
    QObject::connect(ui->updateMember, &QPushButton::clicked, std::bind(&DisplayFam::changeMember, this, 1));


    //hier muss ein array mit fam geholt werden

    QVector<Member*>* familyMembers = m_pLogic->getMembersByFamily(1);

    qDebug() << familyMembers << "members";
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

//    item = new famItem(-100,-100,100,100);
//    scene->addItem(item);



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
    QObject::connect(ui->addMember, &QPushButton::clicked, this, &DisplayFam::addNewMember);
    QObject::connect(ui->updateMember, &QPushButton::clicked, std::bind(&DisplayFam::changeMember, this, 1));
}

void DisplayFam::changeMember(int id) {
    emit memberChoosen(id);
}

void DisplayFam::addNewMember() {
    emit memberChoosen(-1);
}
