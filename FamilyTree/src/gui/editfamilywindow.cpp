#include "editfamilywindow.h"
#include "ui_editfamilywindow.h"

editFamilyWindow::editFamilyWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editFamilyWindow)
{
    ui->setupUi(this);
}

editFamilyWindow::~editFamilyWindow()
{
    delete ui;
}
