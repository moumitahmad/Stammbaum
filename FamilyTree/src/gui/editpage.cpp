#include "editpage.h"
#include "ui_editpage.h"


#include <QDebug>

EditPage::EditPage(domain::ILogic* pLogic, QWidget *parent) :
    QWidget(parent),
    m_pLogic(pLogic),
    ui(new Ui::EditPage)
{
    ui->setupUi(this);
    QObject::connect(ui->ButtonViewFamily, &QPushButton::clicked, this, &EditPage::openViewPage);

    m_df = new DisplayFam(m_pLogic, this);
    ui->displayFamilyPanel->addWidget(m_df);

    m_mp = new MemberPanel(m_pLogic, this);
    ui->allMembersPanel->addWidget(m_mp);

    m_ep = new EditPanel(m_pLogic, this);
    ui->editPanel->layout()->addWidget(m_ep);
    ui->horizontalLayout->setStretchFactor(ui->editPanel, 1);
    ui->horizontalLayout->setStretchFactor(ui->mainPanel, 3);
    QObject::connect(m_ep, &EditPanel::closePanel, this, &EditPage::closeEditPanel);
    ui->editPanel->hide();

    // signal
    QObject::connect(m_mp, &MemberPanel::memberChoosen, this, &EditPage::openEditPanel);
    QObject::connect(m_mp, &MemberPanel::memberChoosen, m_df, &DisplayFam::updateDisplay);

}

EditPage::~EditPage()
{
    delete ui;
    delete m_ep;
    delete m_mp;
    delete m_df;
}

void EditPage::drawFamily() {
 //   df->update();
    m_df->changeView();
}

void EditPage::setupEditPage() {
    m_displayedFamily = m_pLogic->getFamilyTreeByID(m_pLogic->getCurrentFamilyID());
    ui->LabelViewFamily->setText("<html><head/><body><p><span style='color:#3465a4;'>Edit the family tree: " + m_displayedFamily->getFamilyName() + "</span></p></body></html>");
    m_mp->setupMemberPanel();
}

void EditPage::openViewPage(){
    emit switchToView();
}

void EditPage::openEditPanel(int memberID) {
    qDebug() << "in editpage: " << memberID;
    ui->editPanel->show();
    m_ep->setupEditPanel(memberID);
}

void EditPage::closeEditPanel() {
    ui->editPanel->hide();
    m_mp->setupMemberPanel();
}
