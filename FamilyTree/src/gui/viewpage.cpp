#include "viewpage.h"
#include "ui_viewpage.h"
#include "applicationwindow.h"

ViewPage::ViewPage(domain::ILogic* pLogic, FamilyTree* displayedFamily, QWidget *parent) :
    QWidget(parent),
    m_pLogic(pLogic),
    m_displayedFamily(displayedFamily),
    ui(new Ui::ViewPage)
{
    ui->setupUi(this);
    QObject::connect(ui->editButton, &QPushButton::clicked, this, &ViewPage::openEditPage);
}

ViewPage::~ViewPage() {
    delete ui;
}

void ViewPage::openEditPage() {
    qDebug() << "Switch to Edit Mode";
    openEditPage();
}
