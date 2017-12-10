#-------------------------------------------------
#
# Project created by Rafał Mazurkiewicz 2016-11-09T09:34:11
#
#-------------------------------------------------

QT       += core gui
QT       += core
QT           += sql widgets
RC_FILE = myapp.rc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = baza
TEMPLATE = app

TRANSLATIONS = baza_pl.ts \
               baza_en.ts \
               baza_fr.ts \

SOURCES += main.cpp\
    connectDB.cpp \
    setlanguage.cpp \
    adding.cpp \
    collecting.cpp \
    newproduct.cpp \
    warehouse.cpp

HEADERS  += \
    connectDB.h \
    version.h \
    setlanguage.h \
    adding.h \
    collecting.h \
    newproduct.h \
    warehouse.h

FORMS    +=  \
    setlanguage.ui \
    adding.ui \
    collecting.ui \
    newproduct.ui

DISTFILES += \
    myapp.rc
