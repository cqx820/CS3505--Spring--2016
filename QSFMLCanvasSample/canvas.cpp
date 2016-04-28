#include "canvas.h"



    Canvas::Canvas(QWidget* Parent, const QPoint& Position, const QSize& Size) :
    QSFMLCanvas(Parent, Position, Size)
    {

    }
    void Canvas::OnInit()
    {
        // Load the image
        //myImage.loadFromFile("datas/qt/sfml.png");

        // Setup the sprite
        //mySprite.setTexture(myImage);
        mySprite.setOrigin(mySprite.getGlobalBounds().width / 2.f,mySprite.getGlobalBounds().height / 2.f);
    }

    void Canvas::OnUpdate()
    {
        // Clear screen
        clear(sf::Color(0, 128, 0));

        // Rotate the sprite
        //mySprite.rotate(getFrameTime() * 100.f);

        // Draw it
        draw(mySprite);
    }
