/**
 * @author Moumita Ahmad
 */

#include "viewpage.h"
#include "ui_viewpage.h"
#include "mainwindow.h"
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

    // display page
    m_df = new DisplayFam(m_pLogic, this);
    ui->displayFamilyPanel_2->layout()->addWidget(m_df);
    // members panel
    m_mp = new MemberPanel(m_pLogic, this);
    ui->allMembersPanel->addWidget(m_mp);
    QObject::connect(m_mp, &MemberPanel::memberChoosen, m_df, &DisplayFam::updateDisplay);
    // admin panel
    m_ap = new AdminPanel(m_pLogic, this);
}

ViewPage::~ViewPage() {
    delete ui;
    delete m_pLogic;
    delete m_displayedFamily;
    delete m_currentUser;
    delete m_ap;
    delete m_df;
    delete m_mp;
}

void ViewPage::setupViewPage() {
    m_ap->show();
    ui->ButtonEditFamily->show();
    m_displayedFamily = m_pLogic->getFamilyTreeByID(m_pLogic->getCurrentFamilyID());
    m_currentUser = m_pLogic->getCurrentUser();
    ui->ViewFamilyWelcome->setText("<html><head/><body><p><span style='color:#3465a4;'>Welcome to your family: " + m_displayedFamily->getFamilyName() + "</span></p></body></html>");

    if(m_currentUser->getId() == m_displayedFamily->getAdmin()->getId()) { // user is admin
        qDebug() << "Current User = Admin";
        ui->adminPanel->addWidget(m_ap);
        ui->horizontalLayout->setStretchFactor(ui->adminPanel, 1);
        ui->horizontalLayout->setStretchFactor(ui->displayFamilyPanel_2, 3);
        QObject::connect(m_ap, &AdminPanel::switchToHome, this, &ViewPage::openHomePage);
        m_ap->setupAdminPanel();
    } else if(m_pLogic->userIsViewer(m_currentUser, m_displayedFamily)) { // user is viewer
        qDebug() << "Current User = Viewer";
        m_ap->hide();
        ui->ButtonEditFamily->hide();
    } else { // user is editor
        qDebug() << "Current User = Editor";
        m_ap->hide();
    }
    m_mp->setupMemberPanel();
}

void ViewPage::drawFamily() {
    m_df->changeView();
}

void ViewPage::openEditPage() {
    emit switchToEdit();
}

void ViewPage::openHomePage() {
    emit switchToHome();
}


