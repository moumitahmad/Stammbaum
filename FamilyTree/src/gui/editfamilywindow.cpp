#include "editfamilywindow.h"
#include "ui_editfamilywindow.h"
#include "./persistence/databaseservice.h"
#include <QDebug>

editFamilyWindow::editFamilyWindow(domain::ILogic* pLogic, QWidget *parent) :
    QWidget(parent),
    m_pLogic(pLogic),
    ui(new Ui::editFamilyWindow)
{
    ui->setupUi(this);

    //hier muss ein array mit fam geholt werden
    m_pLogic;

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen blackpen(Qt::black);
    QPen redpen(Qt::red);
    blackpen.setWidth(6);
    redpen.setWidth(6);
    int foo[] = { 1, 2, 3, 4, 5 }; // Eltern Array laden
 //   int arrSize = sizeof(foo)/sizeof(foo[0]);
    int arrSize = 2;
    int startx = -100;
    int starty = -100;
    int startxSave = startx;
    int startySave = starty;
    int widthRect = 100;


//    for (int i :foo ) {  FOR LOOP für ELTERN
      for (int i =0;i<arrSize;i++) {
        rect = scene->addRect(startx,starty,widthRect,widthRect,redpen);

        qDebug() << arrSize ;
        if (arrSize >1 && i > 0) {
            qDebug() << "in if" << i;
            line = scene->addLine(startxSave+widthRect,startySave+widthRect/2, startx,starty+widthRect/2,redpen);
            line = scene->addLine(50, -50, 50, 50, redpen);
        } // Else wenn es nur ein elternteil gibt andernfalls könnte man ein icom mit unbekannt einfügen wenn elternteil nicht bekannt ist
        startx += 200;
    }
}

editFamilyWindow::~editFamilyWindow()
{
    delete ui;
}
