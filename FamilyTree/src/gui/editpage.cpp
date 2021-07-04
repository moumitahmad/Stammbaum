#include "editpage.h"
#include "ui_editpage.h"
#include "applicationwindow.h"

EditPage::EditPage(domain::ILogic* pLogic, QWidget *parent) :
    QWidget(parent),
    m_pLogic(pLogic),
    ui(new Ui::EditPage)
{
    ui->setupUi(this);
}

EditPage::~EditPage()
{
    delete ui;
}

