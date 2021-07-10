#include "editpanel.h"
#include "ui_editpanel.h"
#include <QDebug>
#include <qfiledialog.h>

const QString DEFAULT_DATE = "31.12.9999";

EditPanel::EditPanel(domain::ILogic* pLogic, QWidget *parent) :
    QWidget(parent),
    m_pLogic(pLogic),
    ui(new Ui::EditPanel)
{
    ui->setupUi(this);

    ui->ErrorMessage->hide();

    QObject::connect(ui->ButtonAddPicture, &QPushButton::clicked, this, &EditPanel::uploadPicture);
    QObject::connect(ui->ButtonSave, &QPushButton::clicked, this, &EditPanel::saveMember);
    QObject::connect(ui->ButtonCancel, &QPushButton::clicked, this, &EditPanel::discardChanges);
    QObject::connect(ui->ButtonDelete, &QPushButton::clicked, this, &EditPanel::deleteMember);
}

EditPanel::~EditPanel()
{
    delete ui;
}

void EditPanel::setupEditPanel(int memberID) {
    qDebug() << "Member Choosen: " << memberID;
    m_displayedFamily = m_pLogic->getFamilyTreeByID(m_pLogic->getCurrentFamilyID());

    if(memberID != -1) { // update Member
        ui->ButtonSave->setText("Update");
        m_editedMember = m_pLogic->getMemberByID(memberID);
    } else {
        ui->ButtonDelete->hide();
        m_editedMember = new Member(); // save default member in m_editedMember so that compairisons work
    }

    // show all potential partners and parents
    QVector<Member*>* membersFromFam = m_pLogic->getMembersByFamily(m_displayedFamily->getId());
    if(membersFromFam != nullptr) {
        int index = 0;
        for(Member* p : *membersFromFam) {
            qDebug() << p->getName();
            if(p->getName() != m_editedMember->getName()) {
                ui->ChoosePartner->addItem(p->getName());
                ui->ChoosePartner->setItemData(index, p->getID());
                ui->In_FirstParent->addItem(p->getName());
                ui->In_FirstParent->setItemData(index, p->getID());
                ui->In_SecondParent->addItem(p->getName());
                ui->In_SecondParent->setItemData(index, p->getID());
                index++;
            }
        }
    }

    // TODO: fill-in exsisting data
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

void EditPanel::saveMember(){
    ui->ErrorMessage->hide();
    // data from userinput
    QString name = ui->In_Name->text();
    QString birth = ui->ChoosenBirth->text();
    QString death = ui->ChoosenDeath->text();
    QString gender = ui->ChooseGender->currentText();
    QString biografie = ui->TextBiography->toPlainText();
    int partnerID = ui->ChoosePartner->currentData().toInt();
    int parent1ID = ui->In_FirstParent->currentData().toInt();
    int parent2ID = ui->In_SecondParent->currentData().toInt();
    qDebug() << name << " | " << birth << " | " << death << " | " << gender << " | " << biografie << " | " << partnerID << " | " << parent1ID << " | " << parent2ID;

    // verify name
    if(name.length() == 0) { // name is not filled in
        ui->ErrorMessage->setText("<html><head/><body><p><span style='color:#ef2929;'>A name is requiered for every member.</span></p></body></html>");
        ui->ErrorMessage->show();
        return;
    }

    // TODO: verify dates

    // add defaults
    if(birth == DEFAULT_DATE) {
        birth = "Unknown";
    }
    if(death == DEFAULT_DATE) {
        death = "Unknown";
    }
    if(biografie.length() == 0) {
        biografie = nullptr;
    }

    if(m_editedMember->getName() != "") { // member already exsists
        qDebug() << "Update member: " << m_editedMember->getName();
        //m_pLogic->updateMemberData(m_editedMember);
    } else { // new Member
        qDebug() << "create new member";
        qDebug() << name << " | " << birth << " | " << death << " | " << gender << " | " << biografie;
        m_pLogic->createMember(m_displayedFamily, name, birth, death, gender, biografie);

        // save relationships
        if(partnerID != 0) {
            m_pLogic->savePartnerFromMember(m_editedMember, m_pLogic->getMemberByID(partnerID));
        }
        if(parent1ID != 0) {
            m_pLogic->saveParentChildRelationship(m_pLogic->getMemberByID(parent1ID), m_editedMember);
        }
        if(parent2ID != 0) {
            m_pLogic->saveParentChildRelationship(m_pLogic->getMemberByID(parent2ID), m_editedMember);
        }
    }
    emit closePanel();
}

void EditPanel::discardChanges(){
    ui->In_Name->clear();
    ui->ChoosenBirth->clear();
    ui->ChoosenDeath->clear();
    ui->ChooseGender->setCurrentIndex(0);
    ui->TextBiography->clear();
    ui->ChoosePartner->setCurrentIndex(0);
    ui->In_FirstParent->setCurrentIndex(0);
    ui->In_SecondParent->setCurrentIndex(0);
}

void EditPanel::deleteMember() {

}
