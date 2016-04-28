/**
 * Filename: qsfmlcanvas.h
 * Author: //TO DO: Teamname
 * Date: 12 April 2016
 * Description: This is a generic widget which wraps SFML functionality into QT.
 */

#ifndef QSFMLCanvas_H
#define QSFMLCanvas_H

#include <SFML/Graphics.hpp>
#include <QWidget>
#include <QTimer>

class QSFMLCanvas : public QWidget, public sf::RenderWindow {

public :

    QSFMLCanvas(QWidget* Parent, const QPoint& Position,
                const QSize& Size, unsigned int FrameTime = 0);

    virtual ~QSFMLCanvas();

protected:
    virtual void resizeEvent(QResizeEvent *);

private :

    virtual void OnInit()=0;

    virtual void OnUpdate()=0;

    virtual QPaintEngine* paintEngine() const;


    virtual void showEvent(QShowEvent*);

    virtual void paintEvent(QPaintEvent*);

    QTimer myTimer;
    bool   myInitialized;
    sf::View View2;
};

#endif // MAINWINDOW_H
