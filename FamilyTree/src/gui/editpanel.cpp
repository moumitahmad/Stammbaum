#include "editpanel.h"
#include "ui_editpanel.h"
#include <QDebug>
#include <qfiledialog.h>

EditPanel::EditPanel(domain::ILogic* pLogic, QWidget *parent) :
    QWidget(parent),
    m_pLogic(pLogic),
    ui(new Ui::EditPanel)
{
    ui->setupUi(this);

    QObject::connect(ui->ButtonAddPicture, &QPushButton::clicked, this, &EditPanel::uploadPicture);
    QObject::connect(ui->ButtonSave, &QPushButton::clicked, this, &EditPanel::saveMember);
    QObject::connect(ui->ButtonCancel, &QPushButton::clicked, this, &EditPanel::discardChanges);
}

EditPanel::~EditPanel()
{
    delete ui;
}

void EditPanel::setupEditPanel(int memberID) {
    qDebug() << "Member Choosen: " << memberID;
    m_displayedFamily = m_pLogic->getFamilyTreeByID(m_pLogic->getCurrentFamilyID());
    if(memberID != -1) { // new Member
        m_editedMember = m_pLogic->getMemberByID(memberID);
    }
}

void EditPanel::uploadPicture(){

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

void verifyEnteredData() {

}

void EditPanel::saveMember(){
    verifyEnteredData();
    if(m_editedMember) { // member already exsists
        qDebug() << m_editedMember->getName();
        //m_pLogic->updateMemberData(m_editedMember);
    } else { // new Member
        QString name = "Test";
        m_pLogic->createMember(m_displayedFamily, name);
    }
}

void EditPanel::discardChanges(){
    ui->In_Name->clear();
    ui->In_Birth->clear();
    ui->In_Death->clear();
    ui->ChooseGender->setCurrentIndex(0);
    ui->TextBiography->clear();
    ui->ChoosePartner->setCurrentIndex(0);
    ui->ChooseChildren->setCurrentIndex(0);
}
