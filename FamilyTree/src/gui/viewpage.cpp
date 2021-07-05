#include "viewpage.h"
#include "ui_viewpage.h"
#include "applicationwindow.h"
#include "displayfam.h"
#include <QDebug>
#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QTextLine>

ViewPage::ViewPage(domain::ILogic* pLogic, ApplicationWindow* appWindow, QWidget *parent) :
    QWidget(parent),
    m_appWindow(appWindow),
    m_pLogic(pLogic),
    ui(new Ui::ViewPage)
{
    ui->setupUi(this);
    DisplayFam* df = new DisplayFam(m_pLogic, this);
    ui->horizontalLayout->addWidget(df);
    QObject::connect(ui->ButtonAddEditor, &QPushButton::clicked, this, &ViewPage::addEditor);
    QObject::connect(ui->ButtonAddViewer, &QPushButton::clicked, this, &ViewPage::addViewer);
    QObject::connect(ui->ButtonDeleteFamily, &QPushButton::clicked, this, &ViewPage::deleteFamily);
    QObject::connect(ui->ButtonEditFamily, &QPushButton::clicked, this, &ViewPage::openEditPage);
}

ViewPage::~ViewPage() {
    delete ui;
}

void ViewPage::openEditPage() {
    qDebug() << "Switch to Edit Mode";
    FamilyTree* tr = new FamilyTree(m_pLogic->getCurrentFamilyID(), "noname", m_pLogic->getCurrentUser());
    //display tree;
    m_appWindow->openEditPage();
}

void ViewPage::addEditor(){

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

void ViewPage::addViewer(){

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

void ViewPage::deleteFamily(){
    qDebug() << m_displayedFamily->getId();
    m_pLogic->deleteFamily(m_displayedFamily);
    //return to home
    m_appWindow->openHomePage();
}

