#include "homepage.h"
#include "ui_homepage.h"
#include "mainwindow.h"

#include <QDebug>
#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QTextLine>


Homepage::Homepage(domain::ILogic* pLogic, QWidget *parent) :
    QWidget(parent),
    m_pLogic(pLogic),
    ui(new Ui::Homepage)
{
    ui->setupUi(this);
    m_currentUser = pLogic->getCurrentUser();
    ui->welcomeText->setText("Welcome " + m_currentUser->getName() + "!");
    displayFamilies();
}

Homepage::~Homepage()
{
    delete ui;
}

void Homepage::displayFamilies() {
    // display Families
    ui->noFamiliesText->hide();
    while (auto item = ui->ownFamiliesGrid->layout()->takeAt(0)) {

      //      delete item;


     }

    QVector<FamilyTree*>* familyTrees = m_pLogic->getFamilyTreesByUserID(m_currentUser->getId());
    if(familyTrees) {
        qDebug() << "families available";
        qDebug() << familyTrees;
        for(FamilyTree* family : *familyTrees) {
            qDebug() << family->getFamilyName();
            QPushButton* famButton = new QPushButton();
            famButton->setText(family->getFamilyName());
            QObject::connect(famButton, &QPushButton::clicked,std::bind(&Homepage::showFamily, this, family->getId()));

            ui->ownFamiliesGrid->layout()->addWidget(famButton);
        }
    } else {
        ui->noFamiliesText->show();
        qDebug() << "NO families available";
    }
    QObject::connect(ui->newFamilyButton, &QPushButton::clicked, this, &Homepage::addFamily);
}

void Homepage::addFamily() {
    QDialog* d = new QDialog();
    QVBoxLayout* vbox = new QVBoxLayout();
    QLineEdit* nameLineEdit = new QLineEdit();
    nameLineEdit->setPlaceholderText("Enter family name");

    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    vbox->addWidget(nameLineEdit);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);

    int result = d->exec();
    if(result == QDialog::Accepted) {
       // create new user
       QString name = nameLineEdit->text();
       if(m_pLogic->createFamily(name, m_currentUser)) {
           // update family display
           // remove buttons
           QLayoutItem *child;
           while ((child = ui->ownFamiliesGrid->layout()->takeAt(0)) != 0) {
               delete child;
           }
           displayFamilies();
           d->close();
       } else {
           addFamily();
       }
    } else if(result == QDialog::Rejected) {
        d->close();
    }
}

void Homepage::showFamily(int familyID) {
    qDebug() << "Open Family with ID = " << familyID;
    m_pLogic->setCurrentFamilyID(familyID);
    //m_appWindow->openViewPage();
    emit switchToView();
}
