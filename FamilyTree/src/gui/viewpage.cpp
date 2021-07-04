#include "viewpage.h"
#include "ui_viewpage.h"
#include "applicationwindow.h"
#include "displayfam.h"
#include <QDebug>


ViewPage::ViewPage(domain::ILogic *pLogic, ApplicationWindow *appWindow, QWidget *parent) {
    QWidget(parent),
    m_appWindow(appWindow),
    m_pLogic(pLogic),
    ui(new Ui::ViewPage)
{
    ui->setupUi(this);
    DisplayFam* df = new DisplayFam(m_pLogic, this);
    ui->gridLayout->addWidget(df);
    QObject::connect(ui->goToEditButton, &QPushButton::clicked, this, &ViewPage::openEditPage);
}

ViewPage::~ViewPage() {
    delete ui;
}

void ViewPage::openEditPage() {
    qDebug() << "Switch to Edit Mode";
    m_appWindow->openEditPage();
}

