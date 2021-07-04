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
    Homepage* hp = new Homepage(m_pLogic, this, this);
    ViewPage* vp = new ViewPage(m_pLogic, this);
    EditPage* ep = new EditPage(m_pLogic, this);
    //DisplayFam* df = new DisplayFam(m_pLogic, this);

    ui->HomePage->layout()->addWidget(hp);
    ui->ViewFamily->layout()->addWidget(vp);
    ui->EditFamily->layout()->addWidget(ep);
    ui->stackedWidget->setCurrentIndex(0);

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

void ApplicationWindow::openHomePage() {
    ui->stackedWidget->setCurrentIndex(0);
}

void ApplicationWindow::openViewPage() {
    ui->stackedWidget->setCurrentIndex(1);
}

void ApplicationWindow::openEditPage() {
    ui->stackedWidget->setCurrentIndex(2);
}

