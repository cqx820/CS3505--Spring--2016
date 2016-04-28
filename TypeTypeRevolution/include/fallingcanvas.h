/**
 * Filename: fallingcanvas.h
 * Author: //TO DO: Teamname
 * Date: 12 April 2016
 * Description: This widget is used to draw the words as they fall from the
 * word box.
 */

#ifndef FALLINGCANVAS_H
#define FALLINGCANVAS_H
#include "qsfmlcanvas.h"
#include "crate.h"
#include "entity.h"
#include <Box2D/Box2D.h>
#include <map>

class FallingCanvas : public QSFMLCanvas {

public :
    /**
     * @brief FallingCanvas
     * @param Parent
     * @param Position Ignored
     * @param Size Ignored
     * @param frameMiliseconds Framerate ~= 1000/frameMiliseonds. 0 is unlimited
     */
    FallingCanvas(QWidget* Parent, const QPoint& Position,
                  const QSize& Size, const int frameMiliseconds = 30);
    ~FallingCanvas();

    void DisplayWorld();

public slots:
    void updateWorld(b2World*);
    void addEntity(Entity* entity,std::string name);
    void updateScore(int score);
    void toggleCrateColor(Entity*,bool);

private :

    void OnInit();

    void OnUpdate();

    b2World *world=NULL;

    std::map <b2Body*,Crate*> crateList;
    sf::Sprite *sea=NULL;
    sf::Texture *seaTexture=NULL;
    int score;
    sf::Texture *ship_texture;
};

#endif // FALLINGCANVAS_H
