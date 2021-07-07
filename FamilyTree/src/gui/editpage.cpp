#include "editpage.h"
#include "ui_editpage.h"
#include "mainwindow.h"
#include "displayfam.h"

#include <qfiledialog.h>
#include <QDebug>

EditPage::EditPage(domain::ILogic* pLogic, QWidget *parent) :
    QWidget(parent),
    m_pLogic(pLogic),
    ui(new Ui::EditPage)
{
    ui->setupUi(this);
    this->df = new DisplayFam(m_pLogic, this);
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

void EditPage::setFamily(int family) const {
    df->family = family;
}

void EditPage::uploadPicture(){

    QFileDialog *dialog = new QFileDialog();
    dialog->setAcceptMode(QFileDialog::AcceptOpen);
    dialog->setFileMode(QFileDialog::ExistingFile);
    dialog->setDefaultSuffix("jpg");
    dialog->selectMimeTypeFilter("image/jpeg");
    int result = dialog->exec();
    if(result == QDialog::Accepted) {
        // save image address
        QString image = dialog->selectedFiles()[0];
        qDebug() << image;
        // save file in database
        // TO IMPLEMENT
    } else if(result == QDialog::Rejected) {
        dialog->close();
    }
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
    emit switchToView();
}
