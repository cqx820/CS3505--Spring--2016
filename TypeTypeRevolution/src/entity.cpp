#include "entity.h"
#include <QDebug>

Entity::Entity(b2World *world){
    this->world = world;
}

void Entity::LoadCrate(int x,int y, int width, int height){
    this->bodyDef = new b2BodyDef;
    this->bodyDef->type = b2_dynamicBody;
    this->bodyDef->position= b2Vec2(x, y);
    this->body = this->world->CreateBody(this->bodyDef);
    this->polygon = new b2PolygonShape;
    this->polygon->SetAsBox(width,height);
    this->fixtureDef = new b2FixtureDef;
    this->fixtureDef->shape = this->polygon;
    this->fixtureDef->density = 0.4f;
    this->fixtureDef->friction = 5.f;
    this->fixtureDef->isSensor = false;
    this->body->CreateFixture(this->fixtureDef);

//    body->ApplyForce( b2Vec2(0,-50), body->GetWorldCenter(),true );
    b2Vec2 vel=body->GetLinearVelocity();
    vel.y=-30;
    body->SetLinearVelocity( vel );
     body->SetGravityScale(0);
}

void Entity::LoadWalls(int x, int y, int width, int height){
    bodyDef=new b2BodyDef;
    bodyDef->position = b2Vec2(x, y);
    bodyDef->type = b2_staticBody;
    body = world->CreateBody(bodyDef);
    polygon=new b2PolygonShape;
    polygon->SetAsBox((width), (height));
    fixtureDef=new b2FixtureDef;
    fixtureDef->density = 1.0f;
    fixtureDef->shape = polygon;
    fixtureDef->isSensor = true;
    body->CreateFixture(fixtureDef);
}


Entity::~Entity(){
    if(bodyDef!=NULL){
        delete this->bodyDef;
    }
    if(fixtureDef!=NULL){
        delete this->fixtureDef;
    }
    if(polygon!=NULL){
        delete this->polygon;
    }

}
