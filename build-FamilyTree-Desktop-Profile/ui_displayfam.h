/********************************************************************************
** Form generated from reading UI file 'displayfam.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYFAM_H
#define UI_DISPLAYFAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DisplayFam
{
public:
    QFormLayout *formLayout;
    QGridLayout *gridLayout;
    QLabel *label;

    void setupUi(QWidget *DisplayFam)
    {
        if (DisplayFam->objectName().isEmpty())
            DisplayFam->setObjectName(QString::fromUtf8("DisplayFam"));
        DisplayFam->resize(400, 300);
        formLayout = new QFormLayout(DisplayFam);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(DisplayFam);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        formLayout->setLayout(0, QFormLayout::LabelRole, gridLayout);


        retranslateUi(DisplayFam);

        QMetaObject::connectSlotsByName(DisplayFam);
    } // setupUi

    void retranslateUi(QWidget *DisplayFam)
    {
        DisplayFam->setWindowTitle(QApplication::translate("DisplayFam", "Form", nullptr));
        label->setText(QApplication::translate("DisplayFam", "trolololo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DisplayFam: public Ui_DisplayFam {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYFAM_H
