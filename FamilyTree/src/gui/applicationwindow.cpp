#include "applicationwindow.h"
#include "ui_applicationwindow.h"

ApplicationWindow::ApplicationWindow(domain::ILogic* pLogic, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ApplicationWindow)
{
    ui->setupUi(this);
}

ApplicationWindow::~ApplicationWindow()
{
    delete ui;
}
