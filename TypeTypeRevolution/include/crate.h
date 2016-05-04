#ifndef CRATE_H
#define CRATE_H
#include <SFML/Graphics.hpp>
#include <string>

class Crate :public sf::Sprite, public sf::Text
{
public:
    Crate(std::string text);
    Crate(bool ship);
    void setCratePos(int x, int y);
    std::string renderedName;
    void setCrateRotation(float angle);
    void toggleTexture(bool shouldHighlight);
    void highlightText(int index);

private:
    std::string plaintextName;
    sf::Texture  texture;
    bool ship = false;
};

#endif // CRATE_H
