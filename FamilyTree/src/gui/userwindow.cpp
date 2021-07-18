//Gurleen Kour

#include "userwindow.h"
#include "ui_userwindow.h"

#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QDebug>

UserWindow::UserWindow(domain::ILogic* pLogic, QWidget *parent) :
    QMainWindow(parent),
    m_pLogic(pLogic),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    this->hideErrors();

    //additional settings
    ui->in_password->setEchoMode(QLineEdit::Password);
    ui->in_new_password->setEchoMode(QLineEdit::Password);

    QObject::connect(ui->newUserButton, &QPushButton::clicked, this, &UserWindow::switchToCreateNewUser);
    QObject::connect(ui->backButton, &QPushButton::clicked, this, &UserWindow::switchToLogIn);
    QObject::connect(ui->loginButton, &QPushButton::clicked, this, &UserWindow::logInUser);
    QObject::connect(ui->newUserButton_2, &QPushButton::clicked, this, &UserWindow::createNewUser);
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::hideErrors() {
    // hide error and additional messages
    ui->errorLabelLogin->hide();
    ui->errorLabelNameNotValid->hide();
    ui->errorLabelNameTaken->hide();
    ui->errorLabelPasswordNotValid->hide();
    ui->accountCreatedLabel->hide();
    ui->placeholder->hide();
}

void UserWindow::switchToCreateNewUser() {
    ui->stackedWidget->setCurrentIndex(1);

    // hide error and additional messages
    ui->errorLabelNameNotValid->hide();
    ui->errorLabelPasswordNotValid->hide();
    ui->errorLabelNameTaken->hide();
}

void UserWindow::switchToLogIn() {
    if(ui->stackedWidget->currentIndex() == 1)
        ui->accountCreatedLabel->show();
    else
        ui->accountCreatedLabel->hide();
    ui->stackedWidget->setCurrentIndex(0);

    // hide error and additional messages
    ui->errorLabelLogin->hide();
    ui->placeholder->hide();
}

void UserWindow::createNewUser(){
    hideErrors();
    QString username;
    QString password;

    // check if username is at least 5 characters long
    if(ui->in_new_username->text().size() < 5) {
        ui->errorLabelNameNotValid->show();
        ui->in_new_username->clear();
        ui->in_new_password->clear();
    } else {
        username = ui->in_new_username->text();
    }

    //check if password is at least 7 characters long
    if(ui->in_new_password->text().size() < 7) {
        ui->errorLabelPasswordNotValid->show();
        ui->in_new_password->clear();
    } else {
        password = ui->in_new_password->text();
    }

    // try to create user
    if(m_pLogic->createUser(username, password) == nullptr){
        if(username.size() > 5 && password > 7){
            ui->errorLabelNameTaken->show();
            qDebug() << "User already exists!";
        }
    } else {
        ui->stackedWidget->setCurrentIndex(0);
        qDebug() << "User created!";

        // return to login window
        ui->stackedWidget->setCurrentIndex(0);
        ui->accountCreatedLabel->show();
    }
}


void UserWindow::logInUser(){
    hideErrors();
    QString username = ui->in_username->text();
    QString password = ui->in_password->text();

    User* user = m_pLogic->loginUser(username, password);
    if(user) {
        ui->errorLabelLogin->hide();
        qDebug() << "Successfully logged-in!";
        m_pLogic->setCurrentUser(user);
        m_pApp = new MainWindow(m_pLogic);
        m_pApp->show();
        this->hide();

    } else {
        ui->errorLabelLogin->show();
        ui->in_password->clear();
        ui->in_username->clear();
    }
}

void UserWindow::quit(){
    this->close();
    exit(EXIT_SUCCESS);
}
