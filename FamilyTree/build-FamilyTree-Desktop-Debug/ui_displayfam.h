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
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DisplayFam
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *DisplayFam)
    {
        if (DisplayFam->objectName().isEmpty())
            DisplayFam->setObjectName(QString::fromUtf8("DisplayFam"));
        DisplayFam->resize(795, 648);
        gridLayout_2 = new QGridLayout(DisplayFam);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new QGraphicsView(DisplayFam);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(DisplayFam);

        QMetaObject::connectSlotsByName(DisplayFam);
    } // setupUi

    void retranslateUi(QWidget *DisplayFam)
    {
        DisplayFam->setWindowTitle(QApplication::translate("DisplayFam", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DisplayFam: public Ui_DisplayFam {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYFAM_H
