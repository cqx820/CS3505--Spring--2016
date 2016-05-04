/**
 * Filename: fallingcanvas.cpp
 * Author: //TO DO: Teamname
 * Date: 12 April 2016
 */

#include "fallingcanvas.h"
#include "richtext.h"
#include <QDebug>
#include <QResource>


FallingCanvas::FallingCanvas(QWidget* Parent, const QPoint& Position,
                             const QSize& Size, const int frameMiliseconds)
    : QSFMLCanvas(Parent, Position, Size, frameMiliseconds) {
    }
FallingCanvas::~FallingCanvas(){

    delete seaTexture;
    delete sea;
    for(auto entity:crateList){
        delete entity.second;
    }
}

void FallingCanvas::OnInit() {

}

void FallingCanvas::OnUpdate() {

    // Clear screen
    sf::RenderTarget::clear(sf::Color(10,230,255,0));
    if(world==NULL)
        return;
    sf::Font font;
    QResource wordFont(":font");
    if(!font.loadFromMemory(wordFont.data(),wordFont.size())){
        qDebug()<<"Failed to load font";
    }
    sf::RectangleShape line(sf::Vector2f(1000, 5));
    line.setPosition(0,300);
    line.setFillColor(sf::Color::Red);
    b2Body* body = world->GetBodyList();
    for (; body != 0; body = body->GetNext()) {
       if (body->GetType() == b2_dynamicBody)
       {

           Crate *crate=crateList.at(body);
           crate->setCratePos( body->GetPosition().x, -body->GetPosition().y);
           crate->setCrateRotation(body->GetAngle()*180/b2_pi);
//                       Sprite.SetRotation(BodyIterator->GetAngle() * 180/b2_pi);
           draw((sf::Sprite)*crate);

           sfe::RichText word;
           word.setString(crate->renderedName);
           word.setFont(font);
           word.setCharacterSize(50);
//           word.setStyle(sf::Text::Bold);
//           word.sf::Text::setColor(sf::Color::Black);
           word.setPosition(body->GetPosition().x, -body->GetPosition().y);
           word.setOrigin(word.getLocalBounds().width/2,word.getLocalBounds().height/2);
           word.setRotation(body->GetAngle()*180/b2_pi);
           word.setScale(0.5,0.5);
           draw (word);
//                       draw((sf::Text)*crate);
//                       ++BodyCount;
       }
       else
       {
            draw(*sea);
       }

    }
    sf::Text scoreDisplay;
    scoreDisplay.setFont(font);
    scoreDisplay.setString("Score: "+std::to_string(score));
    scoreDisplay.setCharacterSize(40);
    scoreDisplay.setStyle(sf::Text::Bold);
    scoreDisplay.sf::Text::setColor(sf::Color::Black);
    scoreDisplay.sf::Text::setPosition(10,10);
    draw(scoreDisplay);
    draw(line);

}

void FallingCanvas::updateWorld(b2World* world){
    this->world=world;
}

void FallingCanvas::addEntity(Entity *entity, std::string name){

    if(entity->body->GetType()==b2_dynamicBody){
        Crate* crate;

//            qDebug()<<"FallingCanvas sea"<<boxExtents.x<<","<<boxExtents.y;
        if(name==""){
            crate=new Crate(true);

        }else{
            crate=new Crate(name);

        }
        sf::Vector2u size = crate->getTexture()->getSize();
//            qDebug()<<"CRATE SIZE"<<size.x<<","<<size.x;
        b2AABB aabb;
        b2Fixture* fixture = entity->body->GetFixtureList();
        aabb=fixture->GetAABB(0);
        auto boxExtents =aabb.GetExtents();

        crate->sf::Sprite::setOrigin(size.x/2,size.y/2);
        if(name==""){

            crate->sf::Sprite::setScale(boxExtents.x/size.x*2,boxExtents.y/size.y*4);
        }
        else{
        crate->sf::Sprite::setScale(boxExtents.x/size.x*2,boxExtents.y/size.y*2);
        }
        crateList[entity->body]=crate;
    }
    else{
        sea=new sf::Sprite();
        QResource crateTexture(":ocean-texture");
        seaTexture=new sf::Texture();
        seaTexture->loadFromMemory(crateTexture.data(), crateTexture.size());
        sea->setTexture(*seaTexture);
        b2AABB aabb;
        b2Fixture* fixture = entity->body->GetFixtureList();
        aabb=fixture->GetAABB(0);
        auto boxExtents =aabb.GetExtents();
         auto size = sea->getTexture()->getSize();
        sea->setScale(boxExtents.x/size.x,boxExtents.y/size.y*2);
//             sea->setScale(.5,.1);
         sea->setPosition(entity->body->GetPosition().x,-entity->body->GetPosition().y-size.y/4);
           sf::Color color=sea->getColor();
           color.a=100;
           sea->setColor(color);
//         qDebug()<<"FallingCanvas sea"<<boxExtents.x<<","<<boxExtents.y;
//         qDebug()<<"FallingCanvas sea"<<size.x<<","<<size.y;

    }
}

void FallingCanvas::updateScore(int score){
    this->score=score;
}

void FallingCanvas::toggleCrateColor(Entity *entity, bool highlight){
    Crate *crate = crateList.at(entity->body);
    crate->toggleTexture(highlight);
}

void FallingCanvas::highlightText(Entity *entity, int index) {
    Crate *crate = crateList.at(entity->body);
    crate->highlightText(index);
}

