#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "./persistence/databaseservice.h"

#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QDebug>
#include "./domain/ILogic.h"

MainWindow::MainWindow(domain::ILogic* pLogic, ApplicationWindow* pApp, QWidget *parent):
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

    // hide error and additional messages
    ui->errorLabelNameNotValid->hide();
    ui->errorLabelPasswordNotValid->hide();
    ui->errorLabelNameTaken->hide();
}

void MainWindow::switchToLogIn() {
    ui->stackedWidget->setCurrentIndex(0);
    ui->accountCreatedLabel->show();

    // hide error and additional messages
    ui->errorLabelLogin->hide();
    ui->placeholder->hide();
}

void MainWindow::createNewUser(){
    QString username;
    QString password;

    // check if username is at least 5 characters long
    if(ui->in_new_username->toPlainText().size() < 5) {
        ui->errorLabelNameNotValid->show();
        ui->in_new_username->clear();
        ui->in_new_password->clear();
    } else {
        username = ui->in_new_username->toPlainText();
    }

    //check if password is at least 7 characters long
    if(ui->in_new_password->toPlainText().size() < 7) {
        ui->errorLabelPasswordNotValid->show();
        ui->in_new_password->clear();
    } else {
        password = ui->in_new_password->toPlainText();
    }

    // try to create user
    if(username == "" || password == "" || m_pLogic->createUser(username,password) == nullptr){
        ui->errorLabelNameTaken->show();
        qDebug() << "User already exists!";
        qDebug() << username;
        qDebug() << password;
    } else {
        ui->stackedWidget->setCurrentIndex(0);
        qDebug() << "User created!";

        // return to login window
        ui->stackedWidget->setCurrentIndex(0);
        ui->accountCreatedLabel->show();
    }
}


void MainWindow::logInUser(){
    QString username = ui->in_username->toPlainText();
    QString password = ui->in_password->toPlainText();

    if(m_pLogic->loginUser(username, password)) {
        ui->errorLabelLogin->hide();
        qDebug() << "Successfully logged-in!";
        m_pApp = new ApplicationWindow(m_pLogic);
        m_pApp->show();
        this->close();

    } else {
        ui->errorLabelLogin->show();
        ui->in_password->clear();
        ui->in_username->clear();
    }
}

void MainWindow::quit(){
    this->close();
    exit(EXIT_SUCCESS);
}
