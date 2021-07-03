#include "displayfam.h"
#include "ui_displayfam.h"

DisplayFam::DisplayFam(domain::ILogic* pLogic, QWidget *parent) :
    QWidget(parent),
    m_pLogic(pLogic),
    ui(new Ui::DisplayFam)
{
    ui->setupUi(this);
}

DisplayFam::~DisplayFam()
{
    delete ui;
}
