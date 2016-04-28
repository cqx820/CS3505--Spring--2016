#include "timecanvas.h"


TimeCanvas::TimeCanvas(QWidget* Parent, const QPoint& Position,
                       const QSize& Size, const int frameMilliseconds)
    : QSFMLCanvas(Parent, Position, Size, frameMilliseconds) {
}

void TimeCanvas::runTime(int min, int sec)
{


    timerText.setString(min +":"+sec );
    draw(timertext);

    do
    {
    timer.restart();

    while (timer.getElapsedTime.asMilliseconds()<frameMilliseconds);

    sec--;
    if(sec <0)
    {
        sec=59;
        min--;
    }
    timerText.setString(min +":"+sec );
    draw();
    }
    while(min!=0 ||sec!=0);

}
