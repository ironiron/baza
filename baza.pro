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



SOURCES += main.cpp\
        mainwindow.cpp \
    magazyn.cpp \
    connectDB.cpp \
    nowyprodukt.cpp \
    dodaje.cpp \
    odejmij.cpp

HEADERS  += mainwindow.h \
    magazyn.h \
    connectDB.h \
    nowyprodukt.h \
    dodaje.h \
    odejmij.h \
    version.h

FORMS    += mainwindow.ui \
    nowyprodukt.ui \
    dodaje.ui \
    odejmij.ui

DISTFILES += \
    myapp.rc
