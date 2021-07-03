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
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Homepage
{
public:
    QFormLayout *formLayout;
    QVBoxLayout *verticalLayout;
    QLabel *welcomeText;

    void setupUi(QWidget *Homepage)
    {
        if (Homepage->objectName().isEmpty())
            Homepage->setObjectName(QString::fromUtf8("Homepage"));
        Homepage->resize(400, 300);
        formLayout = new QFormLayout(Homepage);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        formLayout->setLayout(0, QFormLayout::LabelRole, verticalLayout);

        welcomeText = new QLabel(Homepage);
        welcomeText->setObjectName(QString::fromUtf8("welcomeText"));

        formLayout->setWidget(0, QFormLayout::FieldRole, welcomeText);


        retranslateUi(Homepage);

        QMetaObject::connectSlotsByName(Homepage);
    } // setupUi

    void retranslateUi(QWidget *Homepage)
    {
        Homepage->setWindowTitle(QApplication::translate("Homepage", "Form", nullptr));
        welcomeText->setText(QApplication::translate("Homepage", "Welcome user!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Homepage: public Ui_Homepage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEPAGE_H
