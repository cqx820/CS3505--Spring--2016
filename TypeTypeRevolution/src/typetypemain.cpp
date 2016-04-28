/**
 * Filename: typetypemain.cpp
 * Author: //TO DO: Teamname
 * Date: 12 April 2016
 * Description: This small function loads up everything necessary for the Cargo
 * Typer application then launches it.
 */

#include "typetypegui.h"
#include <QApplication>
#include "typetypecontroller.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    TypeTypeGUI *gui = new TypeTypeGUI;
    TypeTypeController controller(gui);
    gui->show();

    return a.exec();
}
