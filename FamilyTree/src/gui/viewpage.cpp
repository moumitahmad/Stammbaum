#include "viewpage.h"
#include "ui_viewpage.h"
#include "mainwindow.h"
#include "displayfam.h"
#include <QDebug>
#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QTextLine>

ViewPage::ViewPage(domain::ILogic* pLogic, QWidget *parent) :
    QWidget(parent),
    m_pLogic(pLogic),
    ui(new Ui::ViewPage)
{
    ui->setupUi(this);
    QObject::connect(ui->ButtonEditFamily, &QPushButton::clicked, this, &ViewPage::openEditPage);
}

ViewPage::~ViewPage() {
    delete ui;
    delete m_pLogic;
    delete m_displayedFamily;
    delete m_currentUser;
    delete m_ap;
}

void ViewPage::setupViewPage() {
    qDebug() << "Viewer setup begin";
    ui->ButtonEditFamily->show();
    m_ap = nullptr;
    m_displayedFamily = m_pLogic->getFamilyTreeByID(m_pLogic->getCurrentFamilyID());
    qDebug() << "got family";
    m_currentUser = m_pLogic->getCurrentUser();
    ui->ViewFamilyWelcome->setText("<html><head/><body><p><span style='color:#3465a4;'>Welcome to your family: " + m_displayedFamily->getFamilyName() + "</span></p></body></html>");

    if(m_currentUser->getId() == m_displayedFamily->getAdmin()->getId()) { // user is admin
        qDebug() << "Current User = Admin";
        m_ap = new AdminPanel(m_pLogic, this);
        ui->adminPanel->layout()->addWidget(m_ap);
        ui->horizontalLayout->setStretchFactor(ui->adminPanel, 1);
        ui->horizontalLayout->setStretchFactor(ui->displayFamilyPanel, 3);
        QObject::connect(m_ap, &AdminPanel::switchToHome, this, &ViewPage::openHomePage);
        m_ap->setupAdminPanel();
    } else if(m_pLogic->userIsViewer(m_currentUser, m_displayedFamily)) { // user is viewer
        qDebug() << "Current User = Viewer";
        ui->ButtonEditFamily->hide();
    }

    // display page
    DisplayFam* df = new DisplayFam(m_pLogic, this);
    ui->displayFamilyPanel->layout()->addWidget(df);
    df->setupForView();
    qDebug() << "Viewer setup done";

}

void ViewPage::openEditPage() {
    qDebug() << "Switch to Edit Mode";
    emit switchToEdit();
}

void ViewPage::openHomePage() {
    qDebug() << "Switch to Homepage";
    emit switchToHome();
}


