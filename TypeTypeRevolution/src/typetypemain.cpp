/**
 * Filename: typetypemain.cpp
 * Author: //TO DO: Teamname
 * Date: 12 April 2016
 * Description: This small function loads up everything necessary for the Cargo
 * Typer application then launches it.
 */

#include "typetypegui.h"
#include <QApplication>
#include <QTranslator>
#include "typetypecontroller.h"
#include "typetypecallbackserver.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QTranslator myappTranslator;
    /*
    QString translationPath = QApplication::applicationDirPath();
    translationPath = translationPath + "/spritet_"
                      + QLocale::system().name();
    QString translationPath = "translations/spritet_"
            + QLocale::system().name();*/
    QString languageCode = QLocale::system().name();
    languageCode.truncate(languageCode.lastIndexOf('_'));
    if (myappTranslator.load("translation_" + languageCode,
                        ":/translations")) {
        qApp->installTranslator(&myappTranslator);
    } else {
        qWarning() << "[ERR]  Unable to load translation: "
        << languageCode;
    }

    TypeTypeGUI *gui = new TypeTypeGUI;
    TypeTypeController controller(gui);
    gui->show();


    //TypeTypeCallbackServer server;

    return a.exec();
}
