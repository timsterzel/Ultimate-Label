#-------------------------------------------------
#
# Project created by QtCreator 2016-11-29T12:05:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UltimateLabel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    profilesdialog.cpp \
    jsonhelper.cpp \
    profile.cpp \
    printshowdialog.cpp

HEADERS  += mainwindow.h \
    profilesdialog.h \
    jsonhelper.h \
    profile.h \
    printshowdialog.h

FORMS    += mainwindow.ui \
    profilesdialog.ui \
    printshowdialog.ui
# Add Console for debugging purposes
CONFIG += console
