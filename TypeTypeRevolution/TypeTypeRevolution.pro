#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T17:10:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TypeTypeRevolution
TEMPLATE = app

CONFIG += c++11
QMAKE_CXXFLAGS+= -std=c++11
QMAKE_LFLAGS +=  -std=c++11

INCLUDEPATH += include

CLASS += typetypegui
CLASS += typetypecontroller
CLASS += wordbox
CLASS += qsfmlcanvas
CLASS += fallingcanvas
CLASS += crate
CLASS += entity
CLASS += buoyancy
CLASS += mycontactlistener
CLASS += buoyancylogic
CLASS += typetypemenu
# CLASS += timecanvas
CLASS += keyboardhandler
CLASS += chooselessondialog
CLASS += serverconnectdialog
CLASS += networkcontroller

SRC = typetypemain #ROSS DO NOT DO ANYTHING SILLY AND REMOVE THE MAIN AGAIN
#lol

for(i, CLASS) {
        SOURCES += src/$${i}.cpp
        HEADERS += include/$${i}.h
}

for(i, SRC) {
        SOURCES += src/$${i}.cpp
}

for(i, INC) {
        HEADERS += include/$${i}.h
}

#SFML linkage down here please

macx {
LIBS += -L"/usr/local/lib"
LIBS += -L"/usr/local/opt"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

INCLUDEPATH += "/usr/local/include"
DEPENDPATH += "/usr/local/include"

INCLUDEPATH += ../libs/Box2D
LIBS += -L"../libs/Box2D/Build/Box2D"
LIBS += -lBox2D
}

linux { #Note from Simon: I just copied the macx stuff and installed my directories to match. That seems pefectly sane.
LIBS += -L"/usr/local/lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

INCLUDEPATH += "/usr/local/include"
DEPENDPATH += "/usr/local/include"

INCLUDEPATH += ../libs/Box2D
LIBS += -L"../libs/Box2D/Build/Box2D"
LIBS += -lBox2D
}

RESOURCES += \
    resources.qrc

