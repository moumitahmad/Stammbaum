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
            QObject::connect(member, &QPushButton::clicked, std::bind(&QPushButton::setStyleSheet, member, "border: 3px  solid rgb(245, 121, 0)"));
            ui->membersGrid->addWidget(member, 0, i);
        }
    }
    // plus item
    QPushButton* plus = new QPushButton("+");
    QObject::connect(plus, &QPushButton::clicked, this, &MemberPanel::addNewMember);
    ui->membersGrid->addWidget(plus, 1, 0);
}

void clearMembersLayout(QLayout *layout) {
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearMembersLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}

void MemberPanel::resetUI() {
    clearMembersLayout(ui->membersGrid->layout());
}

void MemberPanel::changeMember(int id) {
    emit memberChoosen(id);
}

void MemberPanel::addNewMember() {
    emit memberChoosen(-1);
}

void MemberPanel::activateButton(QPushButton &button)
{
    //std::bind(&QPushButton::setStyleSheet, member, "border: 2px  solid rgb(245, 121, 0)")
}

