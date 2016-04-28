#include "qsfmlcanvas.h"
#include "canvas.h"
#include <QApplication>
#include <QFrame>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Create the main frame
      QFrame* MainFrame = new QFrame;
      MainFrame->setWindowTitle("Qt SFML");
      MainFrame->resize(400, 400);
      MainFrame->show();

      // Create a SFML view inside the main frame
      Canvas* SFMLView = new Canvas(MainFrame, QPoint(20, 20), QSize(360, 360));
      SFMLView->show();

    return a.exec();
}
