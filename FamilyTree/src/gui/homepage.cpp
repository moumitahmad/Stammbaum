#include "homepage.h"
#include "ui_homepage.h"

Homepage::Homepage(domain::ILogic* pLogic, QWidget *parent) :
    QWidget(parent),
    m_pLogic(pLogic),
    ui(new Ui::Homepage)
{
    ui->setupUi(this);
    m_currentUser = pLogic->getCurrentUser();
    ui->welcomeText->setText("Welcome " + m_currentUser->getName() + "!");
}

Homepage::~Homepage()
{
    delete ui;
}
