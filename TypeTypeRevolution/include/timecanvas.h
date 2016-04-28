#ifndef TIMECANVAS_H
#define TIMECANVAS_H

#include "qsfmlcanvas.h"

class TimeCanvas: public QSFMLCanvas {

public:
    TimeCanvas(QWidget *Parent, const QPoint &Position,
               const QSize &Size, const int frameMilliseconds = 1000);

private:
    sf::Clock timer;
    sf::Font timerFont;
    sf::Text timerText;

    void RunTime(int, int);

};



#endif // TIMECANVAS_H
