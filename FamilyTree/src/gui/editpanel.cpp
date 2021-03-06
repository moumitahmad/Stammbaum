/**
 * @author Moumita Ahmad, Gurleen Kour, Alisa Schumann
 */


#include "editpanel.h"
#include "ui_editpanel.h"
#include <QDebug>
#include <qfiledialog.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <qmessagebox.h>
#include <string>


const std::filesystem::path IMAGES_DIR = "../src/images";
const QString DEFAULTIMG = "defaultMember.png";

EditPanel::EditPanel(domain::ILogic* pLogic, QWidget *parent) :
    QWidget(parent),
    m_pLogic(pLogic),
    ui(new Ui::EditPanel)
{
    ui->setupUi(this);

    ui->ErrorMessage->hide();

    QObject::connect(ui->ButtonAddPicture, &QPushButton::clicked, this, &EditPanel::selectPicture);
    QObject::connect(ui->ButtonRemovePicture, &QPushButton::clicked, this, &EditPanel::removePicture);
    QObject::connect(ui->ButtonSave, &QPushButton::clicked, this, &EditPanel::saveMember);
    QObject::connect(ui->ButtonCancel, &QPushButton::clicked, this, &EditPanel::resetUI);
    QObject::connect(ui->ButtonDelete, &QPushButton::clicked, this, &EditPanel::deleteMember);

    ui->ChoosenBirth->setDateRange(ui->ChoosenBirth->minimumDate(), QDateTime::currentDateTime().date());
    QObject::connect(ui->BirthCheckBox, &QCheckBox::clicked, this, &EditPanel::toggleBirthDate);
    QObject::connect(ui->DeathCheckBox, &QCheckBox::clicked, this, &EditPanel::toggleDeathDate);

    QObject::connect(ui->In_FirstParent, &QComboBox::currentTextChanged, this, &EditPanel::toggleSecondParent);
}

EditPanel::~EditPanel()
{
    delete ui;
    delete m_pLogic;
    delete m_displayedFamily;
    delete m_editedMember;
    for(Member* member : m_possibleRelationships) {
        delete member;
    }
}

int getIndex(QString value) {
    if(value == "Male") {
        return 0;
    }
    if(value == "Female") {
        return 1;
    }
    if(value == "Diverse") {
        return 2;
    }
    if(value == "Unknown") {
        return 3;
    }
    qDebug() << "Error in editpanel::getIndex";
    return -1;
}

QVector<Member*> sortMembersByID(QVector<Member*> members) {
    int n = members.length();
    int i, j;
    for (i = 1; i < n-1; i++)  {
        for (j = 1; j < n-i-1; j++) {
            if (members.at(j)->getID() > members.at(j+1)->getID()) {
                Member* helper = members.at(j);
                members.replace(j, members.at(j+1));
                members.replace(j+1, helper);
            }
        }
    }
    return members;
}

void EditPanel::showPotentionRelationships() {
    // show all potential partners and parents
    QVector<Member*> membersFromFam = m_pLogic->getMembersByFamily(m_displayedFamily->getId());
    if(membersFromFam.isEmpty()) {
        return;
    }
    membersFromFam = sortMembersByID(membersFromFam);
    m_possibleRelationships.push_front(new Member()); // for first default value: no relationship
    if(!membersFromFam.isEmpty()) {
        for(Member* p : membersFromFam) {
            if(p->getID() != m_editedMember->getID()) {
                ui->ChoosePartner->addItem(p->getName());
                ui->In_FirstParent->addItem(p->getName());
                ui->In_SecondParent->addItem(p->getName());
                m_possibleRelationships.push_back(p);
            }
        }
    }
}

int EditPanel::getRelationshipIndex(int id) const {
    for(int i=0; i<m_possibleRelationships.length(); i++) {
        if(m_possibleRelationships.at(i)->getID() == id) {
            return i;
        }
    }
}

void EditPanel::setupEditPanel(int memberID) {
    // reset
    resetUI();
    qDebug() << "Member Choosen: " << memberID;
    m_displayedFamily = m_pLogic->getFamilyTreeByID(m_pLogic->getCurrentFamilyID());

    if(memberID != -1) { // update Member
        ui->ButtonSave->setText("Update");
        m_editedMember = m_pLogic->getMemberByID(memberID);

        showPotentionRelationships();

        // fill-in exsisting data
        ui->In_Name->setText(m_editedMember->getName());
        ui->ChooseGender->setCurrentIndex(getIndex(m_editedMember->getGender()));
        QString birth = m_editedMember->getBirth();
        QDate date(QDateTime::currentDateTime().date());
        if(birth != "Unknown") {
            QStringList pieces = birth.split(".");
            int d = pieces.value(0).toInt();
            int m = pieces.value(1).toInt();
            int y = pieces.value(2).toInt();
            date.setDate(y, m, d);
        } else {
            ui->BirthCheckBox->setChecked(false);
            ui->ChoosenBirth->setEnabled(false);
        }
        ui->ChoosenBirth->setDate(date);
        QString death = m_editedMember->getDeath();
        if(death != "Unknown") {
            QStringList pieces = death.split(".");
            int d = pieces.value(0).toInt();
            int m = pieces.value(1).toInt();
            int y = pieces.value(2).toInt();
            date.setDate(y, m, d);
        } else {
            date = QDateTime::currentDateTime().date();
            ui->DeathCheckBox->setChecked(false);
            ui->ChoosenDeath->setEnabled(false);
        }
        ui->ChoosenDeath->setDate(date);

        if(m_editedMember->getPartner()) {
            ui->ChoosePartner->setCurrentIndex(getRelationshipIndex(m_editedMember->getPartner()->getID()));
        }
        QVector<Member*> parents = m_editedMember->getParents();
        if(parents.length() > 0) {
            ui->In_FirstParent->setCurrentIndex(getRelationshipIndex(parents.at(0)->getID()));
            ui->In_SecondParent->setEnabled(true);
        }
        if(parents.length() > 1) {
            ui->In_SecondParent->setCurrentIndex(getRelationshipIndex(parents.at(1)->getID()));
        }
        if(m_editedMember->getImage() != DEFAULTIMG) {
            ui->showImagePath->setText(m_editedMember->getImage());
            ui->ButtonRemovePicture->show();
            ui->ButtonAddPicture->setText("Update Picture");
        }
    } else {
        ui->ButtonSave->setText("Save");
        ui->ButtonDelete->hide();
        m_editedMember = new Member(); // save default member in m_editedMember so that compairisons work
        showPotentionRelationships();
    }
}

void EditPanel::selectPicture() {
    std::filesystem::path imagePath;
    std::string imageAddressString;
    std::string imageName;
    QFileDialog *dialog = new QFileDialog();
    dialog->setAcceptMode(QFileDialog::AcceptOpen);
    dialog->setFileMode(QFileDialog::ExistingFile);
    dialog->setDefaultSuffix("jpg");
    dialog->selectMimeTypeFilter("image/jpeg");
    int result = dialog->exec();
    if(result == QDialog::Accepted) {
        // save image address
        QString address = dialog->selectedFiles()[0];
        imageAddressString = address.toStdString();
        imagePath = imageAddressString;
    } else if(result == QDialog::Rejected) {
        dialog->close();
    }
    try {
        const std::filesystem::path constImagePath = imagePath;
        imageName = imageAddressString.substr(imageAddressString.find_last_of("/") + 1, 100);

        std::filesystem::copy(constImagePath, IMAGES_DIR);                      //copy image
        EditPanel::currentImageSymlink = "../src/images/symlink" + imageName;   //set symulink up
        std::filesystem::path copiedImagePath = "../src/images/" + imageName;
        create_symlink(copiedImagePath, EditPanel::currentImageSymlink);        //create symlink to copied image
        QMessageBox messageBox;
        messageBox.setText("Image successfully added!");
        messageBox.setFixedSize(500,200);
        messageBox.exec();
        ui->showImagePath->setText(QString::fromStdString(imageName));
        ui->ButtonRemovePicture->show();
        ui->ButtonAddPicture->setText("Update Picture");
    } catch (std::filesystem::filesystem_error& e) {
        //show error dialog
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Image has already been added!");
        messageBox.setFixedSize(500,200);
    }
}

void EditPanel::removePicture() {
    try {
        const std::filesystem::path constSymlink = EditPanel::currentImageSymlink;
        const std::filesystem::path constImagePath = std::filesystem::read_symlink(constSymlink);
        qDebug() << "file to delete: " << constImagePath.c_str();
        qDebug() << "target directory: " << IMAGES_DIR.c_str();
        qDebug() << "file deleted: " << std::filesystem::remove(constImagePath);
        qDebug() << "symlink deleted: " << std::filesystem::remove(EditPanel::currentImageSymlink);
        QMessageBox messageBox;
        messageBox.setText("Image successfully removed!");
        messageBox.setFixedSize(500,200);
        messageBox.exec();
        ui->showImagePath->setText("");
        ui->ButtonRemovePicture->hide();
        ui->ButtonAddPicture->setText("Add Picture");
    } catch (std::filesystem::filesystem_error& e) {
        qDebug() << e.code().message().c_str();
        //show error dialog
        QMessageBox messageBox;
        messageBox.critical(0,"Error","No image has been added yet!");
        messageBox.setFixedSize(500,200);
    }
}

void EditPanel::showError(const QString& message) const {
    ui->ErrorMessage->setText("<html><head/><body><p><span style='color:#ef2929;'>" + message + "</span></p></body></html>");
    ui->ErrorMessage->show();
}

bool EditPanel::relationshipValid(int& partnerID, int& parent1ID, int& parent2ID) {
    if(partnerID != 0 && (partnerID == parent1ID || partnerID == parent2ID)) {
        showError("A parent can not also be a partner.");
        return false;
    }
    if(parent1ID != 0 && parent2ID != 0 && parent1ID == parent2ID) {
        showError("A member needs different parents.");
        return false;
    }
    QVector<Member*> siblings = m_pLogic->getSiblingsFromMember(m_editedMember);
    //bool noError = true;
    for(Member* sibling : siblings) {
        if(sibling->getID() == m_possibleRelationships.at(partnerID)->getID()) {
            showError("A sibling can not also be a partner.");
            return false;
        }
        if(sibling->getID() == m_possibleRelationships.at(parent1ID)->getID() || sibling->getID() == m_possibleRelationships.at(parent2ID)->getID()) {
            showError("A sibling can not also be a parent.");
            return false;
        }
    }
    return true;
}

void EditPanel::saveMember() {
    ui->ErrorMessage->hide();
    // data from userinput
    QString name = ui->In_Name->text();
    QString birth = ui->ChoosenBirth->text();
    QString death = ui->ChoosenDeath->text();
    QString gender = ui->ChooseGender->currentText();
    QString imagePath = ui->showImagePath->text();

    int partnerID = ui->ChoosePartner->currentIndex();
    int parent1ID = ui->In_FirstParent->currentIndex();
    int parent2ID = ui->In_SecondParent->currentIndex();

    qDebug() << name << " | " << birth << " | " << death << " | " << gender << " | " << partnerID << " | " << parent1ID << " | " << parent2ID;

    // verify name
    if(name.length() == 0) { // name is not filled in
        showError("<html><head/><body><p><span style='color:#ef2929;'>Every member requires a name.</span></p></body></html>");
        return;
    }
    if(!relationshipValid(partnerID, parent1ID, parent2ID)) {
        return;
    }
    // add defaults
    if(!ui->BirthCheckBox->isChecked()) {
        birth = "Unknown";
    }
    if(!ui->DeathCheckBox->isChecked()) {
        death = "Unknown";
    }
    if(imagePath == "") {
        imagePath = "defaultMember.png";
    }

    if(m_editedMember->getName() != "") { // member already exsists
        qDebug() << "Update member: " << m_editedMember->getName();
        m_editedMember = m_pLogic->updateMemberData(m_editedMember, name, birth, death, gender, imagePath);
        // relationships
        if(partnerID != 0) {
            Member* partner = m_possibleRelationships.at(partnerID);
            qDebug() << "UPDATE partner: "<< partner->getName();
            if(!m_editedMember->getPartner() || partnerID != m_editedMember->getPartner()->getID())
                m_editedMember = m_pLogic->savePartnerFromMember(m_editedMember, partner);
        } else if(m_editedMember->getPartner()) {
            m_pLogic->deletePartnerFromMember(m_editedMember, m_editedMember->getPartner());
        }
        QVector<Member*> parents = m_editedMember->getParents();
        if(parent1ID != 0) {
            Member* parent1 = m_possibleRelationships.at(parent1ID);
            qDebug() << "UPDATE PARENT1: "<< parent1->getName();
            if(parents.length() == 0 || parent1ID != parents.at(0)->getID()) {
                if(parents.length() == 1)
                    m_pLogic->deleteParentChildRelationship(parents.at(0), m_editedMember);
                m_pLogic->saveParentChildRelationship(parent1, m_editedMember);
            }
        } else if(parents.length() > 0) {
            m_pLogic->deleteParentChildRelationship(parents.at(0), m_editedMember);
        }
        if(parent2ID != 0) {
            Member* parent2 = m_possibleRelationships.at(parent2ID);
            qDebug() << "UPDATE PARENT2: "<< parent2->getName();
            if(parents.length() < 2 || parent2ID != parents.at(1)->getID()) {
                if(parents.length() == 2)
                    m_pLogic->deleteParentChildRelationship(parents.at(1), m_editedMember);
                m_pLogic->saveParentChildRelationship(parent2, m_editedMember);
            }
        } else if(parents.length() > 1) {
            m_pLogic->deleteParentChildRelationship(parents.at(1), m_editedMember);
        }
    } else { // new Member
        qDebug() << "create new member";
        qDebug() << name << " | " << birth << " | " << death << " | " << gender;
        m_editedMember = m_pLogic->createMember(m_displayedFamily, name, birth, death, gender, imagePath);

        // save relationships
        if(partnerID != 0) {
            m_pLogic->savePartnerFromMember(m_editedMember, m_possibleRelationships.at(partnerID));
        }
        if(parent1ID != 0) {
            m_pLogic->saveParentChildRelationship(m_possibleRelationships.at(parent1ID), m_editedMember);
        }
        if(parent2ID != 0) {
            m_pLogic->saveParentChildRelationship(m_possibleRelationships.at(parent2ID), m_editedMember);
        }
    }
    emit closePanel();
    emit updateDisplay(m_editedMember->getID());
}

void EditPanel::resetUI(){
    ui->ButtonDelete->show();
    ui->In_Name->clear();
    QDate defaultDate(QDateTime::currentDateTime().date());
    ui->ChoosenBirth->setDateRange(ui->ChoosenBirth->minimumDate(), QDateTime::currentDateTime().date());
    ui->ChoosenBirth->setDate(defaultDate);
    ui->ChoosenBirth->setEnabled(true);
    ui->ChoosenDeath->setDateRange(ui->ChoosenDeath->minimumDate(), QDateTime::currentDateTime().date());
    ui->ChoosenDeath->setDate(defaultDate);
    ui->ChoosenDeath->setEnabled(true);
    ui->BirthCheckBox->setChecked(true);
    ui->DeathCheckBox->setChecked(true);
    ui->ChooseGender->setCurrentIndex(0);

    ui->ChoosePartner->clear();
    ui->In_FirstParent->clear();
    ui->In_SecondParent->clear();
    ui->ChoosePartner->addItem("no partner");
    ui->In_FirstParent->addItem("no parents");
    ui->In_SecondParent->addItem("no second parent");
    ui->In_SecondParent->setEnabled(false);
    ui->ChoosePartner->setCurrentIndex(0);
    ui->In_FirstParent->setCurrentIndex(0);
    ui->In_SecondParent->setCurrentIndex(0);

    ui->showImagePath->setText("");
    ui->ButtonRemovePicture->hide();
    ui->ButtonAddPicture->setText("Add Picture");

    m_editedMember = nullptr;
    m_possibleRelationships.clear();
}

void EditPanel::deleteMember() {
    const QString title = "Delete family member";
    const QString text = "Are you sure that you want to delete " + m_editedMember->getName() + "?";
    auto buttonPressed = QMessageBox::question(this, "Delete family member", "Are you sure that you want to delete " + m_editedMember->getName() + "?", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
    if(buttonPressed == QMessageBox::Yes){
        m_pLogic->deleteMember(m_editedMember);
        emit closePanel();
        emit updateDisplay(0);
    }
}

void EditPanel::toggleBirthDate() {
    if(ui->BirthCheckBox->isChecked()) {
        ui->ChoosenBirth->setEnabled(true);
        return;
    }
    ui->ChoosenBirth->setEnabled(false);
}

void EditPanel::toggleDeathDate() {
    if(ui->DeathCheckBox->isChecked()) {
        ui->ChoosenDeath->setEnabled(true);
        return;
    }
    ui->ChoosenDeath->setEnabled(false);
}

void EditPanel::toggleSecondParent()
{
    if(ui->In_FirstParent->currentIndex() != 0) {
        ui->In_SecondParent->setEnabled(true);
    } else {
        ui->In_SecondParent->setEnabled(false);
    }
}

