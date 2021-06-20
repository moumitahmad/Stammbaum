#include "userwindow.h"
#include "ui_userwindow.h"
#include "QDebug"

#include "./domain/ILogic.h"
#include "./persistence/databaseservice.h"


UserWindow::UserWindow(QWidget *parent) :
    QWidget(parent),
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

    if(domain::loginUser(username, password)) {
        ui->errorLabel->hide();
        qDebug() << "entry right";
    } else {
        ui->errorLabel->show();
    }

}




