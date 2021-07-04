#include "editpage.h"
#include "ui_editpage.h"
#include "applicationwindow.h"

EditPage::EditPage(domain::ILogic* pLogic, ApplicationWindow* appWindow, QWidget *parent) :
    QWidget(parent),
    m_appWindow(appWindow),
    m_pLogic(pLogic),
    ui(new Ui::EditPage)
{
    ui->setupUi(this);
    QObject::connect(ui->ButtonView, &QPushButton::clicked, this, &EditPage::openViewPage);
}

EditPage::~EditPage()
{
    delete ui;
}

void EditPage::openViewPage(){
    m_appWindow->openViewPage();
}
