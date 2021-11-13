QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    libs/branch.cpp \
    libs/cnic.cpp \
    libs/contact.cpp \
    libs/email.cpp \
    libs/location.cpp \
    libs/organization.cpp \
    libs/person.cpp \
    libs/user.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    libs/branch.h \
    libs/cnic.h \
    libs/contact.h \
    libs/email.h \
    libs/location.h \
    libs/organization.h \
    libs/person.h \
    libs/user.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
