#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "./persistence/databaseservice.h"

#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QObject::connect(ui->newUserButton, &QPushButton::clicked, this, &MainWindow::createNewUser);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createNewUser() {
    QDialog* d = new QDialog();
    QVBoxLayout* vbox = new QVBoxLayout();
    QLineEdit* nameLineEdit = new QLineEdit();
    nameLineEdit->setPlaceholderText("Enter username");
    QLineEdit* passwordLineEdit = new QLineEdit();
    passwordLineEdit->setPlaceholderText("Enter password");

    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
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
        database::saveUser(name, password);
    }
}


void MainWindow::on_loginButton_clicked()
{
    userwindow = new UserWindow();
    userwindow -> show();
}
