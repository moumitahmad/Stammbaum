#include "viewpage.h"
#include "ui_viewpage.h"
#include "applicationwindow.h"

#include <QDebug>

ViewPage::ViewPage(domain::ILogic* pLogic, QWidget *parent) :
    QWidget(parent),
    m_pLogic(pLogic),
    ui(new Ui::ViewPage)
{
    ui->setupUi(this);
    //QObject::connect(ui->editButton, &QPushButton::clicked, this, &ViewPage::openEditPage);
}

ViewPage::~ViewPage() {
    delete ui;
}

void ViewPage::openEditPage() {
    qDebug() << "Switch to Edit Mode";
    openEditPage();
}
