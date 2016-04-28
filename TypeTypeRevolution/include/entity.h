#ifndef ENTITY_H
#define ENTITY_H
#include <Box2D/Box2D.h>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;

class Entity
{
public:
   //   sf::Vector2f velocity;
    Entity(b2World *world);
    void LoadCrate( int x, int y,int width, int height);
    void LoadWalls(int x, int y,int width, int height);
    b2Body *body;
    bool crateTyped=true;
   // void destroy();
    ~Entity();
protected:
    b2World *world=NULL;
    b2BodyDef *bodyDef=NULL;
    b2PolygonShape *polygon=NULL;
    b2FixtureDef *fixtureDef=NULL;
private:
    sf::Texture *texture=NULL;

};

#endif // ENTITY_H
