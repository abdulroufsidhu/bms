QT       += core gui \
            printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

LIBS += \
    -lpq \
    -lpqxx \
    -lqrencode

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#auth, jobs, items, inventory, deals, expensis, report, api needs to be defined in headers and sources

SOURCES += \
    libs/api.cpp \
    libs/auth.cpp \
    libs/barcodegenerator.cpp \
    libs/branch.cpp \
    libs/cnic.cpp \
    libs/contact.cpp \
    libs/deal.cpp \
    libs/disablemousescroll.cpp \
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
	widgets/OrganizationTab/hire.cpp \
    widgets/StoreTab/attributesclass.cpp \
	widgets/StoreTab/available/addproduct.cpp \
	widgets/StoreTab/available/available.cpp \
	widgets/StoreTab/available/listavailable.cpp \
	widgets/StoreTab/available/updateproduct.cpp \
  widgets/StoreTab/deal/dealtab.cpp \
    widgets/StoreTab/deal/itemdetails.cpp \
	widgets/StoreTab/deal/sell.cpp \
	widgets/attrvalwdgt.cpp \
    widgets/auth/login.cpp \
    widgets/auth/signup.cpp \
    widgets/authscreen.cpp \
    widgets/home.cpp \
    widgets/org.cpp \
    widgets/personal.cpp \
	widgets/store.cpp

HEADERS += \
    libs/api.h \
    libs/auth.h \
    libs/barcodegenerator.h \
    libs/branch.h \
    libs/cnic.h \
    libs/contact.h \
    libs/deal.h \
    libs/disablemousescroll.h \
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
  widgets/OrganizationTab/hire.h \
    widgets/StoreTab/attributesclass.h \
	widgets/StoreTab/available/addproduct.h \
	widgets/StoreTab/available/available.h \
	widgets/StoreTab/available/listavailable.h \
	widgets/StoreTab/available/updateproduct.h \
  widgets/StoreTab/deal/dealtab.h \
    widgets/StoreTab/deal/itemdetails.h \
	widgets/StoreTab/deal/sell.h \
	widgets/attrvalwdgt.h \
    widgets/auth/login.h \
    widgets/auth/signup.h \
    widgets/authscreen.h \
    widgets/home.h \
    widgets/org.h \
    widgets/personal.h \
	widgets/store.h

FORMS += \
    mainwindow.ui \
  widgets/OrganizationTab/hire.ui \
    widgets/StoreTab/attributesclass.ui \
	widgets/StoreTab/available/addproduct.ui \
	widgets/StoreTab/available/available.ui \
	widgets/StoreTab/available/listavailable.ui \
	widgets/StoreTab/available/updateproduct.ui \
  widgets/StoreTab/deal/dealtab.ui \
    widgets/StoreTab/deal/itemdetails.ui \
	widgets/StoreTab/deal/sell.ui \
	widgets/attrvalwdgt.ui \
    widgets/auth/login.ui \
    widgets/auth/signup.ui \
    widgets/authscreen.ui \
    widgets/home.ui \
    widgets/org.ui \
    widgets/personal.ui \
	widgets/store.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/icons.qrc
