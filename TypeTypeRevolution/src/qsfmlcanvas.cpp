/**
 * Filename: qsfmlcanvas.cpp
 * Author: //TO DO: Teamname
 * Date: 12 April 2016
 */

#ifdef Q_WS_X11
    #include <Qt/qx11info_x11.h>
    #include <X11/Xlib.h>
#endif
#include "qsfmlcanvas.h"
#include <QDebug>
#include <QResizeEvent>
#include <cmath>

QSFMLCanvas::QSFMLCanvas(QWidget* Parent, const QPoint& Position,
                         const QSize& Size, unsigned int FrameTime)
    : QWidget(Parent), myInitialized(false) {

    // Setup some states to allow direct rendering into the widget
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    // Set strong focus to enable keyboard events to be received
    setFocusPolicy(Qt::StrongFocus);

    // Setup the widget geometry
    //move(Position);
    resize(Size);
    View2.reset(sf::FloatRect(0,0,1000,600));
    View2.setViewport(sf::FloatRect(0, 0.0,1.0,1.0));
    setView(View2);
    // Setup the timer
    myTimer.setInterval(FrameTime);
}

void QSFMLCanvas::resizeEvent(QResizeEvent *event) {
    if(!myInitialized){
        return;
    }
//    View2.setSize(rect().width(), rect().height());
//    //qDebug() << Q_FUNC_INFO << View2.getCenter().x << ", " << View2.getCenter().y ;
//    if (!(std::abs(event->size().width() - event->oldSize().width()) > 50)) {
//        //If the difference is > 50, it was probably not a real resize event
//        View2.move(event->size().width() - event->oldSize().width(),
//            event->size().height() - event->oldSize().height());
//        setView(View2);
//    }
    //qDebug() << Q_FUNC_INFO << View2.getCenter().x << ", " << View2.getCenter().y ;
    sf::RenderWindow::create((sf::WindowHandle) winId());
    setView(View2);
    OnUpdate();
    display();
}

void QSFMLCanvas::showEvent(QShowEvent*) {

    if (!myInitialized) {
        // Under X11, we need to flush the commands sent to the server to ensure that
        // SFML will get an updated view of the windows
        #ifdef Q_WS_X11
            XFlush(QX11Info::display());
        #endif

        // Create the SFML window with the widget handle
        sf::RenderWindow::create((sf::WindowHandle) winId());
        setView(View2);
        // Let the derived class do its specific stuff
        OnInit();

        // Setup the timer to trigger a refresh at specified framerate
        connect(&myTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        myTimer.start();

        myInitialized = true;
    }
}

QPaintEngine* QSFMLCanvas::paintEngine() const {
    return 0;
}

void QSFMLCanvas::paintEvent(QPaintEvent*) {
    // Let the derived class do its specific stuff
    OnUpdate();

    // Display on screen
    display();
}

QSFMLCanvas::~QSFMLCanvas(){ }
//virtual void QSFMLCanvas::OnInit();
//virtual void QSFMLCanvas::OnUpdate();
