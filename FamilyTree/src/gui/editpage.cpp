#include "editpage.h"
#include "ui_editpage.h"
#include "displayfam.h"
#include "editpanel.h"

#include <QDebug>

EditPage::EditPage(domain::ILogic* pLogic, QWidget *parent) :
    QWidget(parent),
    m_pLogic(pLogic),
    ui(new Ui::EditPage)
{
    ui->setupUi(this);
    QObject::connect(ui->ButtonViewFamily, &QPushButton::clicked, this, &EditPage::openViewPage);

    DisplayFam* df = new DisplayFam(m_pLogic, this);
    ui->horizontalLayout->layout()->addWidget(df);
    EditPanel* ep = new EditPanel(m_pLogic, this);
    ui->editPanel->layout()->addWidget(ep);

    // signal
    QObject::connect(df, &DisplayFam::memberChoosen, ep, &EditPanel::setupEditPanel);
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
