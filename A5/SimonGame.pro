#-------------------------------------------------
#
# Project created by QtCreator 2016-02-27T10:01:23
#
#-------------------------------------------------
CONFIG += c++11

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimonGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    simonlogic.cpp

HEADERS  += mainwindow.h \
    simonlogic.h

FORMS    += mainwindow.ui

DISTFILES += \
    AudioClip

RESOURCES += \
    resource.qrc
