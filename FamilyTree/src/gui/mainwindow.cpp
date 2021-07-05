#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "homepage.h"
#include "editpage.h"
#include "viewpage.h"

#include <QDebug>
#include "userwindow.h"

MainWindow::MainWindow(domain::ILogic* pLogic, QWidget *parent):
    QMainWindow(parent),
    m_pLogic(pLogic),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->setupUi(this);
    Homepage* hp = new Homepage(m_pLogic, this, this);
    //QObject::connect(hp, &Homepage::switchToView, this, ...)
    ViewPage* vp = new ViewPage(m_pLogic, this);
    EditPage* ep = new EditPage(m_pLogic, this);
    //DisplayFam* df = new DisplayFam(m_pLogic, this);

    ui->HomePage->layout()->addWidget(hp);
    ui->ViewFamily->layout()->addWidget(vp);
    ui->EditFamily->layout()->addWidget(ep);
    ui->stackedWidget->setCurrentIndex(0);

    QObject::connect(ui->actionHome, &QAction::triggered, this, &MainWindow::openHomePage);
    QObject::connect(ui->actionLogout, &QAction::triggered, this, &MainWindow::logout);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::logout() {
    qDebug() << "logout";
    UserWindow* login = new UserWindow(m_pLogic);
    login->show();
    this->hide();
}

void MainWindow::openHomePage() {
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::openViewPage() {
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::openEditPage() {
    ui->stackedWidget->setCurrentIndex(2);
}
