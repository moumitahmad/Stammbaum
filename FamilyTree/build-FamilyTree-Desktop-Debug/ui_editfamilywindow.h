/********************************************************************************
** Form generated from reading UI file 'editfamilywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITFAMILYWINDOW_H
#define UI_EDITFAMILYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_editFamilyWindow
{
public:
    QGraphicsView *graphicsView;

    void setupUi(QWidget *editFamilyWindow)
    {
        if (editFamilyWindow->objectName().isEmpty())
            editFamilyWindow->setObjectName(QString::fromUtf8("editFamilyWindow"));
        editFamilyWindow->resize(1024, 619);
        graphicsView = new QGraphicsView(editFamilyWindow);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(30, 20, 941, 571));

        retranslateUi(editFamilyWindow);

        QMetaObject::connectSlotsByName(editFamilyWindow);
    } // setupUi

    void retranslateUi(QWidget *editFamilyWindow)
    {
        editFamilyWindow->setWindowTitle(QApplication::translate("editFamilyWindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class editFamilyWindow: public Ui_editFamilyWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITFAMILYWINDOW_H
