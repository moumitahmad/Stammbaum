#include "applicationwindow.h"
#include "ui_applicationwindow.h"

#include "homepage.h"
#include "displayfam.h"

ApplicationWindow::ApplicationWindow(domain::ILogic* pLogic, QWidget *parent) :
    QMainWindow(parent),
    m_pLogic(pLogic),
    ui(new Ui::ApplicationWindow)
{
    ui->setupUi(this);
    Homepage* hp = new Homepage(m_pLogic, this);
    DisplayFam* df = new DisplayFam(m_pLogic, this);

    ui->HomePage->layout()->addWidget(hp);
    ui->EditFamily->layout()->addWidget(df);
    ui->stackedWidget->setCurrentIndex(0);

}

ApplicationWindow::~ApplicationWindow()
{
    delete ui;
}
