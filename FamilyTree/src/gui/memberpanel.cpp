#include "memberpanel.h"
#include "ui_memberpanel.h"
#include "famitem.h"
#include "QPushButton"

MemberPanel::MemberPanel(domain::ILogic* pLogic, QWidget *parent) :
    m_pLogic(pLogic),
    QWidget(parent),
    ui(new Ui::MemberPanel)
{
    ui->setupUi(this);
}

MemberPanel::~MemberPanel()
{
    delete ui;
}

void MemberPanel::setupMemberPanel()
{
    resetUI();
    m_displayedFamily = m_pLogic->getFamilyTreeByID(m_pLogic->getCurrentFamilyID());
    m_allMembers = m_pLogic->getMembersByFamily(m_displayedFamily->getId());


    for(int i=0; i<m_allMembers->length(); i++) {
        ui->membersGrid->addWidget(new QPushButton(m_allMembers->at(i)->getName()), 0, i); //TODO: new famItem
    }
    // plus item
    ui->membersGrid->addWidget(new QPushButton("+"), 1, 0);
}

void MemberPanel::resetUI() {
    // TODO
    while (auto item = ui->membersGrid->layout()->takeAt(0)) {
        delete item;
    }
}

