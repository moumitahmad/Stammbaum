/**
 * @author Moumita Ahmad
 */

#include "homepage.h"
#include "ui_homepage.h"
#include "mainwindow.h"

#include <QDebug>
#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QTextLine>
#include <QLabel>


Homepage::Homepage(domain::ILogic* pLogic, QWidget *parent) :
    QWidget(parent),
    m_pLogic(pLogic),
    ui(new Ui::Homepage)
{
    ui->setupUi(this);
    m_currentUser = pLogic->getCurrentUser();
    ui->welcomeText->setText("<html><head/><body><p><span style='color:#3465a4;'>Welcome " + m_currentUser->getName() + "!</span></p></body></html>");
    displayFamilies();

    QObject::connect(ui->newFamilyButton, &QPushButton::clicked, this, &Homepage::addFamily);
}

Homepage::~Homepage()
{
    delete ui;
    delete m_pLogic;
    delete m_currentUser;
}

void clearFamiliesLayout(QLayout *layout) {
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearFamiliesLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}

void Homepage::displayFamilies() {
    // display Families
    clearFamiliesLayout(ui->ownFamiliesGrid->layout());

    QVector<FamilyTree*> familyTrees = m_pLogic->getFamilyTreesByUserID(m_currentUser->getId());
    if(!familyTrees.isEmpty()) {
        ui->noFamiliesText->hide();
        for(FamilyTree* family : familyTrees) {
            QPushButton* famButton = new QPushButton();
            famButton->setText(family->getFamilyName());
            QObject::connect(famButton, &QPushButton::clicked, std::bind(&Homepage::showFamily, this, family->getId()));
            ui->ownFamiliesGrid->layout()->addWidget(famButton);
        }
    } else {
        ui->noFamiliesText->show();
    }
}

void Homepage::addFamily() {
    QDialog* d = new QDialog();
    QVBoxLayout* vbox = new QVBoxLayout();
    QLineEdit* nameLineEdit = new QLineEdit();
    nameLineEdit->setPlaceholderText("Enter family name");

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    vbox->addWidget(nameLineEdit);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);

    int result = d->exec();
    if(result == QDialog::Accepted) {
       // create new user
       QString name = nameLineEdit->text();
       FamilyTree* newFamily = m_pLogic->createFamily(name, m_currentUser);
       if(newFamily != nullptr) {
           // update family display
           displayFamilies();
       }
       d->close();
    } else if(result == QDialog::Rejected) {
        d->close();
    }
}

void Homepage::showFamily(int familyID) {
    qDebug() << "Open Family with ID = " << familyID;
    m_pLogic->setCurrentFamilyID(familyID);
    //m_appWindow->openViewPage();
    emit switchToView();
    emit drawFamily();
}
