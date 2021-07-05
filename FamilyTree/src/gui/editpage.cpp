#include "editpage.h"
#include "ui_editpage.h"
#include "mainwindow.h"
#include "displayfam.h"

EditPage::EditPage(domain::ILogic* pLogic, MainWindow* appWindow, QWidget *parent) :
    QWidget(parent),
    m_appWindow(appWindow),
    m_pLogic(pLogic),
    ui(new Ui::EditPage)
{
    ui->setupUi(this);
    DisplayFam* df = new DisplayFam(m_pLogic, this);
    ui->horizontalLayout->addWidget(df);
    QObject::connect(ui->ButtonViewFamily, &QPushButton::clicked, this, &EditPage::openViewPage);
    QObject::connect(ui->ButtonAddPicture, &QPushButton::clicked, this, &EditPage::uploadPicture);
    QObject::connect(ui->ButtonSave, &QPushButton::clicked, this, &EditPage::saveChanges);
    QObject::connect(ui->ButtonCancel, &QPushButton::clicked, this, &EditPage::discardChanges);
}

EditPage::~EditPage()
{
    delete ui;
}

void EditPage::uploadPicture(){

}

void EditPage::saveChanges(){

}

void EditPage::discardChanges(){
    ui->In_Name->clear();
    ui->In_Birth->clear();
    ui->In_Death->clear();
    ui->ChooseGender->setCurrentIndex(0);
    ui->TextBiography->clear();
    ui->ChoosePartner->setCurrentIndex(0);
    ui->ChooseChildren->setCurrentIndex(0);
}

void EditPage::openViewPage(){
    m_appWindow->openViewPage();
}
