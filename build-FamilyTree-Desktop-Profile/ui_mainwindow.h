/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *loginPage;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *welcomeLabel;
    QLabel *loginLabel;
    QLabel *errorLabelLogin;
    QLabel *accountCreatedLabel;
    QLabel *placeholder;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_4;
    QGridLayout *gridLayout;
    QPushButton *newUserButton;
    QSpacerItem *verticalSpacer_4;
    QLabel *username;
    QLabel *password;
    QPushButton *loginButton;
    QLineEdit *in_username;
    QLineEdit *in_password;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QWidget *createNewUserPage;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_9;
    QLabel *welcomeLabel_1;
    QLabel *signUpLabel;
    QLabel *errorLabelNameTaken;
    QLabel *errorLabelNameNotValid;
    QLabel *errorLabelPasswordNotValid;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_6;
    QGridLayout *gridLayout_4;
    QLabel *password_3;
    QSpacerItem *verticalSpacer_8;
    QPushButton *newUserButton_2;
    QLabel *username_3;
    QPushButton *backButton;
    QLineEdit *in_new_username;
    QLineEdit *in_new_password;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_9;
    QWidget *page_3;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(680, 445);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        loginPage = new QWidget();
        loginPage->setObjectName(QString::fromUtf8("loginPage"));
        layoutWidget = new QWidget(loginPage);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 661, 390));
        verticalLayout_5 = new QVBoxLayout(layoutWidget);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        welcomeLabel = new QLabel(layoutWidget);
        welcomeLabel->setObjectName(QString::fromUtf8("welcomeLabel"));
        welcomeLabel->setMaximumSize(QSize(16777215, 90));
        QFont font;
        font.setFamily(QString::fromUtf8("Sawasdee"));
        font.setPointSize(26);
        font.setBold(true);
        font.setWeight(75);
        welcomeLabel->setFont(font);

        horizontalLayout_7->addWidget(welcomeLabel);


        verticalLayout_5->addLayout(horizontalLayout_7);

        loginLabel = new QLabel(layoutWidget);
        loginLabel->setObjectName(QString::fromUtf8("loginLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(loginLabel->sizePolicy().hasHeightForWidth());
        loginLabel->setSizePolicy(sizePolicy);
        loginLabel->setMinimumSize(QSize(100, 50));
        loginLabel->setMaximumSize(QSize(400, 50));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Sawasdee"));
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        loginLabel->setFont(font1);

        verticalLayout_5->addWidget(loginLabel);

        errorLabelLogin = new QLabel(layoutWidget);
        errorLabelLogin->setObjectName(QString::fromUtf8("errorLabelLogin"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(errorLabelLogin->sizePolicy().hasHeightForWidth());
        errorLabelLogin->setSizePolicy(sizePolicy1);
        errorLabelLogin->setFont(font1);

        verticalLayout_5->addWidget(errorLabelLogin);

        accountCreatedLabel = new QLabel(layoutWidget);
        accountCreatedLabel->setObjectName(QString::fromUtf8("accountCreatedLabel"));
        sizePolicy1.setHeightForWidth(accountCreatedLabel->sizePolicy().hasHeightForWidth());
        accountCreatedLabel->setSizePolicy(sizePolicy1);
        accountCreatedLabel->setFont(font1);

        verticalLayout_5->addWidget(accountCreatedLabel);

        placeholder = new QLabel(layoutWidget);
        placeholder->setObjectName(QString::fromUtf8("placeholder"));
        sizePolicy1.setHeightForWidth(placeholder->sizePolicy().hasHeightForWidth());
        placeholder->setSizePolicy(sizePolicy1);
        placeholder->setFont(font1);

        verticalLayout_5->addWidget(placeholder);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        newUserButton = new QPushButton(layoutWidget);
        newUserButton->setObjectName(QString::fromUtf8("newUserButton"));

        gridLayout->addWidget(newUserButton, 4, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_4, 2, 1, 1, 1);

        username = new QLabel(layoutWidget);
        username->setObjectName(QString::fromUtf8("username"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(username->sizePolicy().hasHeightForWidth());
        username->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(username, 0, 0, 1, 1);

        password = new QLabel(layoutWidget);
        password->setObjectName(QString::fromUtf8("password"));

        gridLayout->addWidget(password, 1, 0, 1, 1);

        loginButton = new QPushButton(layoutWidget);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));

        gridLayout->addWidget(loginButton, 3, 1, 1, 1);

        in_username = new QLineEdit(layoutWidget);
        in_username->setObjectName(QString::fromUtf8("in_username"));

        gridLayout->addWidget(in_username, 0, 1, 1, 1);

        in_password = new QLineEdit(layoutWidget);
        in_password->setObjectName(QString::fromUtf8("in_password"));

        gridLayout->addWidget(in_password, 1, 1, 1, 1);


        horizontalLayout_5->addLayout(gridLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);


        verticalLayout_5->addLayout(horizontalLayout_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        stackedWidget->addWidget(loginPage);
        createNewUserPage = new QWidget();
        createNewUserPage->setObjectName(QString::fromUtf8("createNewUserPage"));
        layoutWidget1 = new QWidget(createNewUserPage);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 0, 661, 390));
        verticalLayout_7 = new QVBoxLayout(layoutWidget1);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        welcomeLabel_1 = new QLabel(layoutWidget1);
        welcomeLabel_1->setObjectName(QString::fromUtf8("welcomeLabel_1"));
        welcomeLabel_1->setMaximumSize(QSize(16777215, 90));
        welcomeLabel_1->setFont(font);

        horizontalLayout_9->addWidget(welcomeLabel_1);


        verticalLayout_7->addLayout(horizontalLayout_9);

        signUpLabel = new QLabel(layoutWidget1);
        signUpLabel->setObjectName(QString::fromUtf8("signUpLabel"));
        sizePolicy.setHeightForWidth(signUpLabel->sizePolicy().hasHeightForWidth());
        signUpLabel->setSizePolicy(sizePolicy);
        signUpLabel->setMinimumSize(QSize(100, 50));
        signUpLabel->setMaximumSize(QSize(400, 50));
        signUpLabel->setFont(font1);

        verticalLayout_7->addWidget(signUpLabel);

        errorLabelNameTaken = new QLabel(layoutWidget1);
        errorLabelNameTaken->setObjectName(QString::fromUtf8("errorLabelNameTaken"));
        sizePolicy1.setHeightForWidth(errorLabelNameTaken->sizePolicy().hasHeightForWidth());
        errorLabelNameTaken->setSizePolicy(sizePolicy1);
        errorLabelNameTaken->setFont(font1);

        verticalLayout_7->addWidget(errorLabelNameTaken);

        errorLabelNameNotValid = new QLabel(layoutWidget1);
        errorLabelNameNotValid->setObjectName(QString::fromUtf8("errorLabelNameNotValid"));
        sizePolicy1.setHeightForWidth(errorLabelNameNotValid->sizePolicy().hasHeightForWidth());
        errorLabelNameNotValid->setSizePolicy(sizePolicy1);
        errorLabelNameNotValid->setFont(font1);

        verticalLayout_7->addWidget(errorLabelNameNotValid);

        errorLabelPasswordNotValid = new QLabel(layoutWidget1);
        errorLabelPasswordNotValid->setObjectName(QString::fromUtf8("errorLabelPasswordNotValid"));
        sizePolicy1.setHeightForWidth(errorLabelPasswordNotValid->sizePolicy().hasHeightForWidth());
        errorLabelPasswordNotValid->setSizePolicy(sizePolicy1);
        errorLabelPasswordNotValid->setFont(font1);

        verticalLayout_7->addWidget(errorLabelPasswordNotValid);

        verticalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_7->addItem(verticalSpacer_7);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_6);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        password_3 = new QLabel(layoutWidget1);
        password_3->setObjectName(QString::fromUtf8("password_3"));

        gridLayout_4->addWidget(password_3, 1, 0, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_4->addItem(verticalSpacer_8, 2, 1, 1, 1);

        newUserButton_2 = new QPushButton(layoutWidget1);
        newUserButton_2->setObjectName(QString::fromUtf8("newUserButton_2"));

        gridLayout_4->addWidget(newUserButton_2, 3, 1, 1, 1);

        username_3 = new QLabel(layoutWidget1);
        username_3->setObjectName(QString::fromUtf8("username_3"));
        sizePolicy2.setHeightForWidth(username_3->sizePolicy().hasHeightForWidth());
        username_3->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(username_3, 0, 0, 1, 1);

        backButton = new QPushButton(layoutWidget1);
        backButton->setObjectName(QString::fromUtf8("backButton"));

        gridLayout_4->addWidget(backButton, 4, 1, 1, 1);

        in_new_username = new QLineEdit(layoutWidget1);
        in_new_username->setObjectName(QString::fromUtf8("in_new_username"));

        gridLayout_4->addWidget(in_new_username, 0, 1, 1, 1);

        in_new_password = new QLineEdit(layoutWidget1);
        in_new_password->setObjectName(QString::fromUtf8("in_new_password"));

        gridLayout_4->addWidget(in_new_password, 1, 1, 1, 1);


        horizontalLayout_10->addLayout(gridLayout_4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_3);


        verticalLayout_7->addLayout(horizontalLayout_10);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_9);

        stackedWidget->addWidget(createNewUserPage);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        stackedWidget->addWidget(page_3);

        gridLayout_2->addWidget(stackedWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 680, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", nullptr));
        welcomeLabel->setText(QApplication::translate("MainWindow", "Welcome to the Family Tree Project!", nullptr));
        loginLabel->setText(QApplication::translate("MainWindow", "Log in to access your family tree.", nullptr));
        errorLabelLogin->setText(QApplication::translate("MainWindow", "No user found with this data. Please try again.", nullptr));
        accountCreatedLabel->setText(QApplication::translate("MainWindow", "Account successfully created! Please log in.", nullptr));
        placeholder->setText(QApplication::translate("MainWindow", "Placeholder for symmetry", nullptr));
        newUserButton->setText(QApplication::translate("MainWindow", "Sign Up", nullptr));
        username->setText(QApplication::translate("MainWindow", "Username", nullptr));
        password->setText(QApplication::translate("MainWindow", "Password", nullptr));
        loginButton->setText(QApplication::translate("MainWindow", "Login", nullptr));
        welcomeLabel_1->setText(QApplication::translate("MainWindow", "Welcome to the Family Tree Project!", nullptr));
        signUpLabel->setText(QApplication::translate("MainWindow", "Here you can sign up.", nullptr));
        errorLabelNameTaken->setText(QApplication::translate("MainWindow", "Username already taken. Please choose a different one.", nullptr));
        errorLabelNameNotValid->setText(QApplication::translate("MainWindow", "Username must be at least 5 characters long.", nullptr));
        errorLabelPasswordNotValid->setText(QApplication::translate("MainWindow", "Password must be at least 7 characters long.", nullptr));
        password_3->setText(QApplication::translate("MainWindow", "Password", nullptr));
        newUserButton_2->setText(QApplication::translate("MainWindow", "Sign Up", nullptr));
        username_3->setText(QApplication::translate("MainWindow", "Username", nullptr));
        backButton->setText(QApplication::translate("MainWindow", "Back", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
