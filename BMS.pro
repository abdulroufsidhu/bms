QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

LIBS += \
    -lpq \
    -lpqxx

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#auth, jobs, items, inventory, deals, expensis, report, api needs to be defined in headers and sources

SOURCES += \
    libs/api.cpp \
    libs/auth.cpp \
    libs/branch.cpp \
    libs/cnic.cpp \
    libs/contact.cpp \
    libs/deal.cpp \
    libs/email.cpp \
    libs/expense.cpp \
    libs/inventory.cpp \
    libs/item.cpp \
    libs/job.cpp \
    libs/location.cpp \
    libs/organization.cpp \
    libs/person.cpp \
    libs/report.cpp \
    libs/user.cpp \
    main.cpp \
    mainwindow.cpp \
    widgets/home.cpp \
    widgets/org.cpp \
    widgets/personal.cpp \
    widgets/store.cpp

HEADERS += \
    libs/api.h \
    libs/auth.h \
    libs/branch.h \
    libs/cnic.h \
    libs/contact.h \
    libs/deal.h \
    libs/email.h \
    libs/expense.h \
    libs/inventory.h \
    libs/item.h \
    libs/job.h \
    libs/location.h \
    libs/organization.h \
    libs/person.h \
    libs/report.h \
    libs/user.h \
    mainwindow.h \
    widgets/home.h \
    widgets/org.h \
    widgets/personal.h \
    widgets/store.h

FORMS += \
    mainwindow.ui \
    widgets/home.ui \
    widgets/org.ui \
    widgets/personal.ui \
    widgets/store.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/icons.qrc
