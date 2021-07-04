#include "applicationwindow.h"
#include "ui_applicationwindow.h"
#include "homepage.h"
#include "editpage.h"
#include "viewpage.h"


#include <QDebug>
#include "mainwindow.h"

ApplicationWindow::ApplicationWindow(domain::ILogic* pLogic, QWidget *parent) :
    QMainWindow(parent),
    m_pLogic(pLogic),
    ui(new Ui::ApplicationWindow)
{
    ui->setupUi(this);
    Homepage* hp = new Homepage(m_pLogic, this);
    ViewPage* vp = new ViewPage(m_pLogic, this);
    EditPage* ep = new EditPage(m_pLogic, this);
    //DisplayFam* df = new DisplayFam(m_pLogic, this);

    ui->HomePage->layout()->addWidget(hp);
    ui->ViewFamily->layout()->addWidget(vp);
    ui->EditFamily->layout()->addWidget(ep);
    ui->stackedWidget->setCurrentIndex(1);

    QObject::connect(ui->actionLogout, &QAction::triggered, this, &ApplicationWindow::logout);
}

ApplicationWindow::~ApplicationWindow()
{
    delete ui;
}

void ApplicationWindow::logout() {
    qDebug() << "logout";
    MainWindow* login = new MainWindow(m_pLogic, this);
    login->show();
    this->close();
}

void ApplicationWindow::openViewPage(int familyID) {
    qDebug() << familyID;
    ui->stackedWidget->setCurrentIndex(2);
    // TODO: create view page here and pass id in constructor

}

void ApplicationWindow::openEditPage(int familyID) {
    qDebug() << familyID;
    ui->stackedWidget->setCurrentIndex(3);
    // TODO: create view page here and pass id in constructor
}

