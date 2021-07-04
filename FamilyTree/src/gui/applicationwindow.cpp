#include "applicationwindow.h"
#include "ui_applicationwindow.h"
#include "homepage.h"
#include "displayfam.h"

#include <QDebug>
#include "mainwindow.h"

ApplicationWindow::ApplicationWindow(domain::ILogic* pLogic, QWidget *parent) :
    QMainWindow(parent),
    m_pLogic(pLogic),
    ui(new Ui::ApplicationWindow)
{
    ui->setupUi(this);
    Homepage* hp = new Homepage(m_pLogic, this);
    DisplayFam* df = new DisplayFam(m_pLogic, this);

    ui->HomePage->layout()->addWidget(hp);
    ui->EditFamily->layout()->addWidget(df);
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

void ApplicationWindow::openViewPage(int familyID) {
    qDebug() << familyID;
    ui->stackedWidget->setCurrentIndex(2);
    // TODO: create view page here and out id in constructor
}

