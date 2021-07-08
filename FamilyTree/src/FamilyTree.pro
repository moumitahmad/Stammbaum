QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    domain/ILogic.cpp \
    gui/adminpanel.cpp \
    gui/displayfam.cpp \
    gui/editpage.cpp \
    gui/editpanel.cpp \
    gui/homepage.cpp \
    gui/mainwindow.cpp \
    gui/userwindow.cpp \
    gui/viewpage.cpp \
    main.cpp \
    persistence/databaseservice.cpp \
    value-objects/familytree.cpp \
    value-objects/member.cpp \
    value-objects/user.cpp

HEADERS += \
    domain/ILogic.h \
    gui/adminpanel.h \
    gui/displayfam.h \
    gui/editpage.h \
    gui/editpanel.h \
    gui/homepage.h \
    gui/mainwindow.h \
    gui/userwindow.h \
    gui/viewpage.h \
    persistence/databaseservice.h \
    value-objects/familytree.h \
    value-objects/member.h \
    value-objects/user.h

FORMS += \
    gui/adminpanel.ui \
    gui/displayfam.ui \
    gui/editpage.ui \
    gui/editpanel.ui \
    gui/homepage.ui \
    gui/mainwindow.ui \
    gui/userwindow.ui \
    gui/viewpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
