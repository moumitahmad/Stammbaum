/**
 * @author Moumita Ahmad
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include "userwindow.h"

MainWindow::MainWindow(domain::ILogic* pLogic, QWidget *parent):
    QMainWindow(parent),
    m_pLogic(pLogic),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_hp = new Homepage(m_pLogic, this);
    m_vp = new ViewPage(m_pLogic, this);
    m_ep = new EditPage(m_pLogic, this);

    ui->HomePage->layout()->addWidget(m_hp);
    ui->ViewFamily->layout()->addWidget(m_vp);
    ui->EditFamily->layout()->addWidget(m_ep);
    ui->stackedWidget->setCurrentIndex(0);

    // signals
    QObject::connect(m_hp, &Homepage::switchToView, this, &MainWindow::openViewPage);
    QObject::connect(m_ep, &EditPage::switchToView, this, &MainWindow::openViewPage);
    QObject::connect(m_vp, &ViewPage::switchToEdit, this, &MainWindow::openEditPage);
    QObject::connect(m_vp, &ViewPage::switchToHome, this, &MainWindow::openHomePage);

    QObject::connect(m_hp, &Homepage::drawFamily, m_ep, &EditPage::drawFamily);
    QObject::connect(m_hp, &Homepage::drawFamily, m_vp, &ViewPage::drawFamily);

    QObject::connect(ui->actionHome, &QAction::triggered, this, &MainWindow::openHomePage);
    QObject::connect(ui->actionLogout, &QAction::triggered, this, &MainWindow::logout);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_hp;
    delete m_vp;
    delete m_ep;
}


void MainWindow::logout() {
    qDebug() << "logout";
    UserWindow* login = new UserWindow(m_pLogic);
    login->show();
    this->hide();
}

void MainWindow::openHomePage() {
    ui->stackedWidget->setCurrentIndex(0);
    m_hp->displayFamilies();
}

void MainWindow::openViewPage() {
    ui->stackedWidget->setCurrentIndex(1);
    m_vp->setupViewPage();
}

void MainWindow::openEditPage() {
    ui->stackedWidget->setCurrentIndex(2);
    m_ep->setupEditPage();
}
