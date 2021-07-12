#include "editpanel.h"
#include "ui_editpanel.h"
#include <QDebug>
#include <qfiledialog.h>

const QString DEFAULT_DATE = "31.12.9999";
const QString IMAGES_DIR = "./images";

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
}

EditPanel::~EditPanel()
{
    delete ui;
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

void EditPanel::setupEditPanel(int memberID) {
    // reset
    resetUI();
    qDebug() << "Member Choosen: " << memberID;
    m_displayedFamily = m_pLogic->getFamilyTreeByID(m_pLogic->getCurrentFamilyID());

    if(memberID != -1) { // update Member
        ui->ButtonSave->setText("Update");
        m_editedMember = m_pLogic->getMemberByID(memberID);

        // fill-in exsisting data
        ui->In_Name->setText(m_editedMember->getName());
        ui->ChooseGender->setCurrentIndex(getIndex(m_editedMember->getGender()));
        QString birth = m_editedMember->getBirth();
        QDate date(9999, 12, 31);
        if(birth != "Unknown") {
            QStringList pieces = birth.split(".");
            int d = pieces.value(0).toInt();
            int m = pieces.value(1).toInt();
            int y = pieces.value(2).toInt();
            date.setDate(y, m, d);
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
        }
        ui->ChoosenDeath->setDate(date);

    } else {
        ui->ButtonDelete->hide();
        m_editedMember = new Member(); // save default member in m_editedMember so that compairisons work
    }

    // show all potential partners and parents
    m_membersFromFam = m_pLogic->getMembersByFamily(m_displayedFamily->getId());
    if(m_membersFromFam != nullptr) {
        int index = 0;
        for(Member* p : *m_membersFromFam) {
            qDebug() << p->getName();
            if(p->getName() != m_editedMember->getName()) {
                ui->ChoosePartner->addItem(p->getName());
                ui->ChoosePartner->setItemData(index, p->getID());
                ui->In_FirstParent->addItem(p->getName());
                //ui->In_FirstParent->setItemData(index, p->getID());
                ui->In_SecondParent->addItem(p->getName());
                //ui->In_SecondParent->setItemData(index, p->getID());
                index++;
            } else {
                m_membersFromFam->remove(index);
            }
        }
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
        m_editedMember = m_pLogic->createMember(m_displayedFamily, name, birth, death, gender, biografie);

        // save relationships
        if(partnerID != 0) {
            m_pLogic->savePartnerFromMember(m_editedMember, m_membersFromFam->at(partnerID));
        }
        if(parent1ID != 0) {
            Member* parent1 = m_membersFromFam->at(parent1ID);
            m_pLogic->saveParentChildRelationship(parent1, m_editedMember);
        }
        if(parent2ID != 0) {
            Member* parent2 = m_membersFromFam->at(parent2ID);
            m_pLogic->saveParentChildRelationship(parent2, m_editedMember);
        }
    }
    emit closePanel();
}

void EditPanel::resetUI(){
    ui->ButtonDelete->show();
    ui->In_Name->clear();
    QDate defaultDate(9999, 12, 31);
    ui->ChoosenBirth->setDate(defaultDate);
    ui->ChoosenDeath->setDate(defaultDate);
    ui->ChooseGender->setCurrentIndex(3);
    ui->TextBiography->clear();

    ui->ChoosePartner->setCurrentIndex(0);
    ui->In_FirstParent->setCurrentIndex(0);
    ui->In_SecondParent->setCurrentIndex(0);
    for(int i=1; i < ui->ChoosePartner->count(); i++) {
        ui->ChoosePartner->removeItem(i);
        ui->In_FirstParent->removeItem(i);
        ui->In_SecondParent->removeItem(i);
    }
    m_editedMember = nullptr;
}

void EditPanel::deleteMember() {
    qDebug() << "delete " << m_editedMember->getName() << ":";
    m_pLogic->deleteMember(m_editedMember);
    emit closePanel();
}
