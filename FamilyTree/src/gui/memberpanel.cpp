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

    if(m_allMembers) {
        QPushButton* member;
        for(int i=0; i<m_allMembers->length(); i++) {
            member = new QPushButton(m_allMembers->at(i)->getName());
            QObject::connect(member, &QPushButton::clicked, std::bind(&MemberPanel::memberChoosen, this, m_allMembers->at(i)->getID()));
            ui->membersGrid->addWidget(member, 0, i); //TODO: new famItem
        }
    }
    // plus item
    QPushButton* plus = new QPushButton("+");
    QObject::connect(plus, &QPushButton::clicked, this, &MemberPanel::addNewMember);
    ui->membersGrid->addWidget(plus, 1, 0);
}

void MemberPanel::resetUI() {
    // TODO
    while (auto item = ui->membersGrid->layout()->takeAt(0)) {
        delete item;
    }
}

void MemberPanel::changeMember(int id) {
    emit memberChoosen(id);
}

void MemberPanel::addNewMember() {
    emit memberChoosen(-1);
}

