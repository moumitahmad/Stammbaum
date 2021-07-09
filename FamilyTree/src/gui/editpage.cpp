#include "editpage.h"
#include "ui_editpage.h"
#include "displayfam.h"

#include <QDebug>

EditPage::EditPage(domain::ILogic* pLogic, QWidget *parent) :
    QWidget(parent),
    m_pLogic(pLogic),
    ui(new Ui::EditPage)
{
    ui->setupUi(this);
    QObject::connect(ui->ButtonViewFamily, &QPushButton::clicked, this, &EditPage::openViewPage);

    DisplayFam* df = new DisplayFam(m_pLogic, this);
    ui->displayFamilyPanel->layout()->addWidget(df);

    // signal
    QObject::connect(df, &DisplayFam::memberChoosen, this, &EditPage::openEditPanel);
}

EditPage::~EditPage()
{
    delete ui;
}

void EditPage::setupEditPage() {
    m_displayedFamily = m_pLogic->getFamilyTreeByID(m_pLogic->getCurrentFamilyID());
    ui->LabelViewFamily->setText("<html><head/><body><p><span style='color:#3465a4;'>Edit the family tree: " + m_displayedFamily->getFamilyName() + "</span></p></body></html>");
}

void EditPage::openViewPage(){
    emit switchToView();
}

void EditPage::openEditPanel(int memberID) {
    qDebug() << "in editpage: " << memberID;
    m_ep = new EditPanel(m_pLogic, this);
    m_ep->setupEditPanel(memberID);
    ui->editPanel->layout()->addWidget(m_ep);
}

void EditPage::closeEditPanel() {
    delete m_ep;
}
