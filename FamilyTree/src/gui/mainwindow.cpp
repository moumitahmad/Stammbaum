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
    ui->errorLabel->hide();
    QObject::connect(ui->newUserButton, &QPushButton::clicked, this, &MainWindow::createNewUser);
    QObject::connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::logInUser);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createNewUser() {
    ui->stackedWidget->setCurrentIndex(1);
    //ANPASSEN
    /*
    QDialog* d = new QDialog();
    QVBoxLayout* vbox = new QVBoxLayout();
    QLineEdit* nameLineEdit = new QLineEdit();
    nameLineEdit->setPlaceholderText("Enter username");
    QLineEdit* passwordLineEdit = new QLineEdit();
    passwordLineEdit->setPlaceholderText("Enter password");

    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QObject::connect(buttonBox, &QDialogButtonBox::accepted, d, &QDialog::accept);
    //QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    vbox->addWidget(nameLineEdit);
    vbox->addWidget(passwordLineEdit);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);

    int result = d->exec();
    if(result == QDialog::Accepted) {
        // create new user
        QString name = nameLineEdit->text();
        QString password = passwordLineEdit->text();
        qDebug() << "New User" << "name: " << name << ", password: " << password;
        m_pLogic->createUser(name, password);
    }*/
}


void MainWindow::logInUser()
{
    userwindow = new UserWindow(m_pLogic);
    userwindow -> show();
}
