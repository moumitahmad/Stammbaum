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

    ui->ErrorMessage->hide();

    QObject::connect(ui->ButtonAddPicture, &QPushButton::clicked, this, &EditPanel::uploadPicture);
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
    delete m_membersFromFam;
    delete m_editedMember;
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

void EditPanel::showPotentionRelationships() {
    // show all potential partners and parents
    m_membersFromFam = m_pLogic->getMembersByFamily(m_displayedFamily->getId());
    if(m_membersFromFam != nullptr) {
        for(Member* p : *m_membersFromFam) {
            if(p->getID() != m_editedMember->getID()) {
                ui->ChoosePartner->insertItem(p->getID(), p->getName());
                ui->In_FirstParent->insertItem(p->getID(), p->getName());
                ui->In_SecondParent->insertItem(p->getID(), p->getName());
            }
        }
    }
}

Member* EditPanel::findMember(int id) {
    for(Member* member : *m_membersFromFam) {
        if(member->getID() == id)
            return member;
    }
    return nullptr;
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
        ui->TextBiography->setText(m_editedMember->getBiografie());
        ui->ChooseGender->setCurrentIndex(getIndex(m_editedMember->getGender()));
        QString birth = m_editedMember->getBirth();
        QDate date(9999, 12, 31);
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
            date.setDate(9999, 12, 31);
            ui->DeathCheckBox->setChecked(false);
            ui->ChoosenDeath->setEnabled(false);
        }
        ui->ChoosenDeath->setDate(date);
        int id;
        for(int i=0; i<m_membersFromFam->length(); i++) {
            id = m_membersFromFam->at(i)->getID();
            if(m_editedMember->getPartner() && id == m_editedMember->getPartner()->getID()) {
                ui->ChoosePartner->setCurrentIndex(i);
            }
            if(m_editedMember->getParents().length() > 0 && id == m_editedMember->getParents().at(0)->getID()) {
                ui->In_FirstParent->setCurrentIndex(i);
                ui->In_SecondParent->setEnabled(true);
                if(m_editedMember->getParents().length() == 2 && id == m_editedMember->getParents().at(1)->getID()) {
                    ui->In_SecondParent->setCurrentIndex(i);
                }
            }
        }

    } else {
        ui->ButtonDelete->hide();
        m_editedMember = new Member(); // save default member in m_editedMember so that compairisons work
        showPotentionRelationships();
    }
}

void EditPanel::uploadPicture() {

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

void EditPanel::saveMember() {
    ui->ErrorMessage->hide();
    // data from userinput
    QString name = ui->In_Name->text();
    QString birth = ui->ChoosenBirth->text();
    QString death = ui->ChoosenDeath->text();
    QString gender = ui->ChooseGender->currentText();
    QString biografie = ui->TextBiography->toPlainText();

    int partnerID = ui->ChoosePartner->currentIndex();
    int parent1ID = ui->In_FirstParent->currentIndex();
    int parent2ID = ui->In_SecondParent->currentIndex();
    if(m_editedMember->getID() <= partnerID)
        partnerID++;
    if(m_editedMember->getID() <= parent1ID)
        parent1ID++;
    if(m_editedMember->getID() <= parent2ID)
        parent2ID++;

    qDebug() << name << " | " << birth << " | " << death << " | " << gender << " | " << biografie << " | " << partnerID << " | " << parent1ID << " | " << parent2ID;

    // verify name
    if(name.length() == 0) { // name is not filled in
        ui->ErrorMessage->setText("<html><head/><body><p><span style='color:#ef2929;'>A name is requiered for every member.</span></p></body></html>");
        ui->ErrorMessage->show();
        return;
    }
    // add defaults
    if(!ui->BirthCheckBox->isChecked()) {
        birth = "Unknown";
    }
    if(!ui->DeathCheckBox->isChecked()) {
        death = "Unknown";
    }
    if(biografie.length() == 0) {
        biografie = nullptr;
    }

    if(m_editedMember->getName() != "") { // member already exsists
        qDebug() << "Update member: " << m_editedMember->getName();
        m_editedMember = m_pLogic->updateMemberData(m_editedMember, name, birth, death, gender, biografie);
        // relationships
        Member* partner = findMember(partnerID);
        if(partnerID != 0) {
            if(!m_editedMember->getPartner() || partnerID != m_editedMember->getPartner()->getID())
                m_editedMember = m_pLogic->savePartnerFromMember(m_editedMember, partner);
        } else if(!m_editedMember->getPartner()) {
            m_pLogic->deletePartnerFromMember(m_editedMember, partner);
        }
        QVector<Member*> parents = m_editedMember->getParents();
        Member* parent1 = findMember(parent1ID);
        if(parent1ID != 0) {
            if(parents.length() == 0 || parent1ID != parents.at(0)->getID()) {
                if(parents.length() == 1)
                    m_pLogic->deleteParentChildRelationship(parents.at(0), m_editedMember);
                m_editedMember = m_pLogic->saveParentChildRelationship(parent1, m_editedMember);
            }
        } else if(parents.length() < 0) {
            m_editedMember = m_pLogic->deleteParentChildRelationship(parent1, m_editedMember);
        }
        Member* parent2 = findMember(parent2ID);
        if(parent2ID != 0) {
            if(parents.length() == 1 || parent2ID != parents.at(1)->getID()) {
                if(parents.length() == 2)
                    m_pLogic->deleteParentChildRelationship(parents.at(1), m_editedMember);
                m_editedMember = m_pLogic->saveParentChildRelationship(parent2, m_editedMember);
            }
        } else if(parents.length() > 1) {
            m_editedMember = m_pLogic->deleteParentChildRelationship(parent2, m_editedMember);
        }
    } else { // new Member
        qDebug() << "create new member";
        qDebug() << name << " | " << birth << " | " << death << " | " << gender << " | " << biografie;
        m_editedMember = m_pLogic->createMember(m_displayedFamily, name, birth, death, gender, biografie);

        // save relationships
        if(partnerID != 0) {
            m_editedMember = m_pLogic->savePartnerFromMember(m_editedMember, m_membersFromFam->at(partnerID));
        }
        if(parent1ID != 0) {
            Member* parent1 = m_membersFromFam->at(parent1ID);
            m_editedMember = m_pLogic->saveParentChildRelationship(parent1, m_editedMember);
        }
        if(parent2ID != 0) {
            Member* parent2 = m_membersFromFam->at(parent2ID);
            m_editedMember = m_pLogic->saveParentChildRelationship(parent2, m_editedMember);
        }
    }
    emit closePanel();
}

void EditPanel::resetUI(){
    ui->ButtonDelete->show();
    ui->In_Name->clear();
    ui->ChoosenBirth->setDateRange(ui->ChoosenBirth->minimumDate(), QDateTime::currentDateTime().date());
    ui->ChoosenBirth->setEnabled(true);
    ui->ChoosenDeath->setDateRange(ui->ChoosenDeath->minimumDate(), QDateTime::currentDateTime().date());
    ui->ChoosenDeath->setEnabled(true);
    ui->BirthCheckBox->setChecked(true);
    ui->DeathCheckBox->setChecked(true);
    ui->ChooseGender->setCurrentIndex(3);
    ui->TextBiography->clear();

    ui->ChoosePartner->setCurrentIndex(0);
    ui->In_FirstParent->setCurrentIndex(0);
    ui->In_SecondParent->setCurrentIndex(0);
    ui->ChoosePartner->clear();
    ui->ChoosePartner->addItem("no partner");
    ui->In_FirstParent->clear();
    ui->In_FirstParent->addItem("no parents");
    ui->In_SecondParent->clear();
    ui->In_SecondParent->addItem("no second parent");
    ui->In_SecondParent->setEnabled(false);

    m_editedMember = nullptr;
    m_membersFromFam = nullptr;
}

void EditPanel::deleteMember() {
    qDebug() << "delete " << m_editedMember->getName() << ":";
    m_pLogic->deleteMember(m_editedMember);
    emit closePanel();
}

void EditPanel::toggleBirthDate() {
    qDebug() << "toggle Birth:";
    if(ui->BirthCheckBox->isChecked()) {
        qDebug() << "true";
        ui->ChoosenBirth->setEnabled(true);
        return;
    }
    qDebug() << "false";
    ui->ChoosenBirth->setEnabled(false);
}

void EditPanel::toggleDeathDate() {
    qDebug() << "toggle Death:";
    if(ui->DeathCheckBox->isChecked()) {
        qDebug() << "true";
        ui->ChoosenDeath->setEnabled(true);
        return;
    }
    qDebug() << "false";
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

