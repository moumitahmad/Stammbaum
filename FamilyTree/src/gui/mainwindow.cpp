#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "./persistence/databaseservice.h"

#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QDebug>
#include "./domain/ILogic.h"

MainWindow::MainWindow(domain::ILogic* pLogic, QWidget *parent):
    QMainWindow(parent),
    m_pLogic(pLogic),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    // hide error and additional messages
    ui->errorLabelLogin->hide();
    ui->errorLabelNameNotValid->hide();
    ui->errorLabelNameTaken->hide();
    ui->errorLabelPasswordNotValid->hide();
    ui->accountCreatedLabel->hide();
    ui->placeholder->hide();

    QObject::connect(ui->newUserButton, &QPushButton::clicked, this, &MainWindow::switchToCreateNewUser);
    QObject::connect(ui->backButton, &QPushButton::clicked, this, &MainWindow::switchToLogIn);
    QObject::connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::logInUser);
    QObject::connect(ui->newUserButton_2, &QPushButton::clicked, this, &MainWindow::createNewUser);
    QObject::connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::quit);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::switchToCreateNewUser() {
    ui->stackedWidget->setCurrentIndex(1);
    ui->errorLabelNameNotValid->hide();
    ui->errorLabelPasswordNotValid->hide();
}

void MainWindow::switchToLogIn() {
    ui->stackedWidget->setCurrentIndex(0);
    ui->accountCreatedLabel->show();
}

void MainWindow::createNewUser(){
    QString username = ui->in_new_username->toPlainText();
    QString password = ui->in_new_password->toPlainText();

    if(m_pLogic->createUser(username,password) == nullptr){
        //ui->errorLabelCreateUser->show();
        qDebug() << "User already exists!";
    } else {
        ui->stackedWidget->setCurrentIndex(0);
        qDebug() << "User created!";
    }
    ui->stackedWidget->setCurrentIndex(0);
    ui->accountCreatedLabel->show();
}


void MainWindow::logInUser(){
    QString username = ui->in_username->toPlainText();
    QString password = ui->in_password->toPlainText();

    if(m_pLogic->loginUser(username, password)) {
        ui->errorLabelLogin->hide();
        qDebug() << "Succesfully logged in!";
    } else {
        ui->errorLabelLogin->show();
    }

}

void MainWindow::quit(){
    this->close();
    exit(EXIT_SUCCESS);
}
