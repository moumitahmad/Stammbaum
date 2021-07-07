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
    ui->userMessage->hide();
}


void AdminPanel::addEditor() {
    ui->userMessage->hide();
    QString username = ui->in_Editor->text();
    qDebug() << username;
    try {
        m_pLogic->addEditor(m_displayedFamily, username);
        ui->userMessage->setText("The new editor has been saved.");
    } catch(const std::logic_error* &ex) {
        qDebug() << ex->what();
        ui->userMessage->setText(ex->what());
    }
    ui->userMessage->show();
    ui->in_Editor->clear();
}

void AdminPanel::addViewer() {
    ui->userMessage->hide();
    QString username = ui->in_Viewer->text();
    qDebug() << username;
    try {
        m_pLogic->addViewer(m_displayedFamily, username);
        ui->userMessage->setText("The new viewer has been saved.");
    } catch(const std::logic_error* &ex) {
        qDebug() << ex->what();
        ui->userMessage->setText(ex->what());
    }
    ui->userMessage->show();
    ui->in_Viewer->clear();
}

void AdminPanel::deleteFamily(){
    qDebug() << m_displayedFamily->getId();
    m_pLogic->deleteFamily(m_displayedFamily);
    // return to home
    emit switchToHome();
}
