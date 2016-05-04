#include "crate.h"
#include <QDir>
#include <QResource>
#include <QtGui>

Crate::Crate(std::string text) {
    QResource crateTexture(":crate-texture");
    texture.loadFromMemory(crateTexture.data(), crateTexture.size());
    setTexture(texture);

    renderedName = "#black " + text;
    plaintextName = text;
}

Crate::Crate(bool ship){
    this->ship = ship;
    QResource crateTexture(":ship-texture");
    texture.loadFromMemory(crateTexture.data(), crateTexture.size());
    setTexture(texture);
}

void Crate::setCratePos(int x, int y){
    sf::Sprite::setPosition(x,y);
}

void Crate::setCrateRotation(float angle){
    sf::Sprite::setRotation(angle);
}

void Crate::toggleTexture(bool shouldHighlight){
    QString textureResource;
    if(shouldHighlight) {
        textureResource = ":crate-texture-highlighted";
    } else {
        textureResource = ":crate-texture";
    }

    QResource crateTexture(textureResource);
    texture.loadFromMemory(crateTexture.data(), crateTexture.size());
    setTexture(texture);
}

void Crate::highlightText(int index) {
    renderedName = "";
    renderedName.append("#green ");
    renderedName.append(plaintextName.substr(0, index));
    renderedName.append("#black ");
    renderedName.append(plaintextName.substr(index));
}

