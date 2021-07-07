#include "adminpanel.h"
#include "ui_adminpanel.h"
#include <QDebug>
#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QTextLine>

AdminPanel::AdminPanel(domain::ILogic* pLogic, QWidget *parent) :
    QWidget(parent),
    m_pLogic(pLogic),
    ui(new Ui::AdminPanel)
{
    ui->setupUi(this);

    QObject::connect(ui->ButtonAddEditor, &QPushButton::clicked, this, &AdminPanel::addEditor);
    QObject::connect(ui->ButtonAddViewer, &QPushButton::clicked, this, &AdminPanel::addViewer);
    QObject::connect(ui->ButtonDeleteFamily, &QPushButton::clicked, this, &AdminPanel::deleteFamily);
}

AdminPanel::~AdminPanel()
{
    delete ui;
}

void AdminPanel::setupAdminPanel() {
    m_displayedFamily = m_pLogic->getFamilyTreeByID(m_pLogic->getCurrentFamilyID());
}


void AdminPanel::addEditor(){

    QDialog* d = new QDialog();
    QVBoxLayout* vbox = new QVBoxLayout();
    QLineEdit* nameLineEdit = new QLineEdit();
    nameLineEdit->setPlaceholderText("Enter editor username");

    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    vbox->addWidget(nameLineEdit);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);

    int result = d->exec();
    if(result == QDialog::Accepted) {
       //
       QString username = nameLineEdit->text();

    } else if(result == QDialog::Rejected) {
        d->close();
    }
}

void AdminPanel::addViewer(){

    QDialog* d = new QDialog();
    QVBoxLayout* vbox = new QVBoxLayout();
    QLineEdit* nameLineEdit = new QLineEdit();
    nameLineEdit->setPlaceholderText("Enter viewer username");

    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    vbox->addWidget(nameLineEdit);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);

    int result = d->exec();
    if(result == QDialog::Accepted) {
       //
       QString username = nameLineEdit->text();

    } else if(result == QDialog::Rejected) {
        d->close();
    }
}

void AdminPanel::deleteFamily(){
    qDebug() << m_displayedFamily->getId();
    m_pLogic->deleteFamily(m_displayedFamily);
    // return to home
    emit switchToHome();
}
