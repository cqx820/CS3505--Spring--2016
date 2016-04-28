#ifndef CRATE_H
#define CRATE_H
#include <SFML/Graphics.hpp>
#include <string>

class Crate :public sf::Sprite, public sf::Text
{
public:
    Crate();
    Crate(bool ship);
    void setCratePos(int x, int y);
    std::string name;
    void setCrateRotation(float angle);
    void toggleTexture(bool shouldHighlight);

private:
    sf::Texture  texture;
    bool ship = false;

};

#endif // CRATE_H
