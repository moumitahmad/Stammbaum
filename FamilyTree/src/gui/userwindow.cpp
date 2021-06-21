#include "userwindow.h"
#include "ui_userwindow.h"
#include "QDebug"


UserWindow::UserWindow( domain::ILogic* pLogic, QWidget *parent) :
    QWidget(parent),
    m_pLogic(pLogic),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    ui->errorLabel->hide();
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::on_pushButton_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if(m_pLogic->loginUser(username, password)) {
        ui->errorLabel->hide();
        qDebug() << "entry right";
    } else {
        ui->errorLabel->show();
    }

}




