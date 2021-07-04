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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Homepage
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *welcomeText;
    QHBoxLayout *ownFamiliesGrid;
    QLabel *noFamiliesText;
    QPushButton *newFamilyButton;

    void setupUi(QWidget *Homepage)
    {
        if (Homepage->objectName().isEmpty())
            Homepage->setObjectName(QString::fromUtf8("Homepage"));
        Homepage->resize(800, 600);
        QFont font;
        font.setFamily(QString::fromUtf8("Sawasdee"));
        Homepage->setFont(font);
        gridLayout = new QGridLayout(Homepage);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(100, 100, 100, 100);
        welcomeText = new QLabel(Homepage);
        welcomeText->setObjectName(QString::fromUtf8("welcomeText"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Sawasdee"));
        font1.setPointSize(26);
        font1.setBold(true);
        font1.setWeight(75);
        welcomeText->setFont(font1);
        welcomeText->setAlignment(Qt::AlignCenter);
        welcomeText->setMargin(50);

        verticalLayout->addWidget(welcomeText);

        ownFamiliesGrid = new QHBoxLayout();
        ownFamiliesGrid->setObjectName(QString::fromUtf8("ownFamiliesGrid"));
        noFamiliesText = new QLabel(Homepage);
        noFamiliesText->setObjectName(QString::fromUtf8("noFamiliesText"));
        QFont font2;
        font2.setPointSize(15);
        font2.setItalic(true);
        noFamiliesText->setFont(font2);
        noFamiliesText->setAlignment(Qt::AlignCenter);
        noFamiliesText->setWordWrap(false);

        ownFamiliesGrid->addWidget(noFamiliesText);


        verticalLayout->addLayout(ownFamiliesGrid);

        newFamilyButton = new QPushButton(Homepage);
        newFamilyButton->setObjectName(QString::fromUtf8("newFamilyButton"));

        verticalLayout->addWidget(newFamilyButton);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(Homepage);

        QMetaObject::connectSlotsByName(Homepage);
    } // setupUi

    void retranslateUi(QWidget *Homepage)
    {
        Homepage->setWindowTitle(QApplication::translate("Homepage", "Form", nullptr));
        welcomeText->setText(QApplication::translate("Homepage", "Welcome user!", nullptr));
        noFamiliesText->setText(QApplication::translate("Homepage", "You haven't saved any familytrees yet.", nullptr));
        newFamilyButton->setText(QApplication::translate("Homepage", "+ add Family", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Homepage: public Ui_Homepage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEPAGE_H
