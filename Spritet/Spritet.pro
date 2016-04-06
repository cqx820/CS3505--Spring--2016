#-------------------------------------------------
#
# Project created by QtCreator 2016-03-06T19:18:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Spritet
TEMPLATE = app

CONFIG += c++11
QMAKE_CXXFLAGS+= -std=c++11
QMAKE_LFLAGS +=  -std=c++11

INCLUDEPATH += include tool/include

#INCLUDEPATH += $(MAGICK) $(MAGICK)/Magick++/lib/
#LIBS += -L$(MAGICK)/Magick++/lib/.libs

QMAKE_CXXFLAGS += $(shell Magick++-config --cppflags --cxxflags)

#QMAKE_CXXFLAGS += -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -I/usr/local/include/ImageMagick-7 -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -I/usr/local/include/ImageMagick-7 -L/usr/local/lib -lMagick++-7.Q16HDRI -lMagickWand-7.Q16HDRI -lMagickCore-7.Q16HDRI -L/usr/local/lib -lMagick++-7.Q16HDRI -lMagickWand-7.Q16HDRI -lMagickCore-7.Q16HDRI

LIBS += $(shell Magick++-config --ldflags --libs)

LANGUAGES = de es fr zh

CLASS = spritetgui modtroller drawingcanvas toolbox framepanel tool toolbutton menu colorswitcher hotkeypanel preview thumbnail drawingframe framecontainer

#SRC =
INC = define

RESOURCES = resources/icons.qrc

TOOLS = pencil eraser line selection colourreplacer box mirror fill lightendarken

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

for(i, TOOLS) {
	SOURCES += tool/src/$${i}.cpp
	HEADERS += tool/include/$${i}.h
}

for (i, LANGUAGES) {
    TRANSLATIONS += translations/spritet_$${i}.ts
}

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
