/********************************************************************************
** Form generated from reading UI file 'homepage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEPAGE_H
#define UI_HOMEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Homepage
{
public:
    QFormLayout *formLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *ownFamiliesGrid;
    QLabel *welcomeText;
    QPushButton *newFamilyButton;

    void setupUi(QWidget *Homepage)
    {
        if (Homepage->objectName().isEmpty())
            Homepage->setObjectName(QString::fromUtf8("Homepage"));
        Homepage->resize(400, 300);
        formLayout = new QFormLayout(Homepage);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        ownFamiliesGrid = new QHBoxLayout();
        ownFamiliesGrid->setObjectName(QString::fromUtf8("ownFamiliesGrid"));

        verticalLayout->addLayout(ownFamiliesGrid);

        welcomeText = new QLabel(Homepage);
        welcomeText->setObjectName(QString::fromUtf8("welcomeText"));

        verticalLayout->addWidget(welcomeText);

        newFamilyButton = new QPushButton(Homepage);
        newFamilyButton->setObjectName(QString::fromUtf8("newFamilyButton"));

        verticalLayout->addWidget(newFamilyButton);


        formLayout->setLayout(0, QFormLayout::LabelRole, verticalLayout);


        retranslateUi(Homepage);

        QMetaObject::connectSlotsByName(Homepage);
    } // setupUi

    void retranslateUi(QWidget *Homepage)
    {
        Homepage->setWindowTitle(QApplication::translate("Homepage", "Form", nullptr));
        welcomeText->setText(QApplication::translate("Homepage", "Welcome user!", nullptr));
        newFamilyButton->setText(QApplication::translate("Homepage", "add Family", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Homepage: public Ui_Homepage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEPAGE_H
