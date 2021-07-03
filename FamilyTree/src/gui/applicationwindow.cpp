#include "applicationwindow.h"
#include "ui_applicationwindow.h"

#include "homepage.h"

ApplicationWindow::ApplicationWindow(domain::ILogic* pLogic, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ApplicationWindow)
{
    ui->setupUi(this);
    Homepage* hp = new Homepage(m_pLogic, this);
    ui->HomePage->layout()->addWidget(hp);
    ui->stackedWidget->setCurrentIndex(2);
}

ApplicationWindow::~ApplicationWindow()
{
    delete ui;
}
