/********************************************************************************
** Form generated from reading UI file 'applicationwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPLICATIONWINDOW_H
#define UI_APPLICATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ApplicationWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *HomePage;
    QFormLayout *formLayout;
    QWidget *ViewFamily;
    QWidget *EditFamily;
    QMenuBar *menubar;
    QMenu *menuLogout;
    QMenu *menuQuit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ApplicationWindow)
    {
        if (ApplicationWindow->objectName().isEmpty())
            ApplicationWindow->setObjectName(QString::fromUtf8("ApplicationWindow"));
        ApplicationWindow->resize(800, 600);
        centralwidget = new QWidget(ApplicationWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        HomePage = new QWidget();
        HomePage->setObjectName(QString::fromUtf8("HomePage"));
        formLayout = new QFormLayout(HomePage);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        stackedWidget->addWidget(HomePage);
        ViewFamily = new QWidget();
        ViewFamily->setObjectName(QString::fromUtf8("ViewFamily"));
        stackedWidget->addWidget(ViewFamily);
        EditFamily = new QWidget();
        EditFamily->setObjectName(QString::fromUtf8("EditFamily"));
        stackedWidget->addWidget(EditFamily);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        ApplicationWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ApplicationWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuLogout = new QMenu(menubar);
        menuLogout->setObjectName(QString::fromUtf8("menuLogout"));
        menuQuit = new QMenu(menubar);
        menuQuit->setObjectName(QString::fromUtf8("menuQuit"));
        ApplicationWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ApplicationWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ApplicationWindow->setStatusBar(statusbar);

        menubar->addAction(menuLogout->menuAction());
        menubar->addAction(menuQuit->menuAction());

        retranslateUi(ApplicationWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ApplicationWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ApplicationWindow)
    {
        ApplicationWindow->setWindowTitle(QApplication::translate("ApplicationWindow", "MainWindow", nullptr));
        menuLogout->setTitle(QApplication::translate("ApplicationWindow", "Logout", nullptr));
        menuQuit->setTitle(QApplication::translate("ApplicationWindow", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ApplicationWindow: public Ui_ApplicationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPLICATIONWINDOW_H
