#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H


#include <Box2D/Box2D.h>
#include <buoyancylogic.h>
#include <QDebug>

class MyContactListner : public b2ContactListener
{
public:
   // MyContactListner();
    void BeginContact(b2Contact *contact){
        b2Fixture *fixtureA = contact->GetFixtureA();
        b2Fixture *fixtureB = contact->GetFixtureB();
        if(fixtureA->IsSensor() && (fixtureB->GetBody()->GetType() == b2_dynamicBody)){
            m_fixturePairs.insert(std::pair<b2Fixture*, b2Fixture*>(fixtureA, fixtureB));
        }
        else if(fixtureB->IsSensor() && (fixtureA->GetBody()->GetType() == b2_dynamicBody)){
            m_fixturePairs.insert(std::pair<b2Fixture*, b2Fixture*>(fixtureB, fixtureA));
        }
    }

    void EndContact(b2Contact *contact){
        b2Fixture *fixtureA = contact->GetFixtureA();
        b2Fixture *fixtureB = contact->GetFixtureB();
        if(fixtureA->IsSensor() && (fixtureB->GetBody()->GetType() == b2_dynamicBody)){
            m_fixturePairs.erase(std::pair<b2Fixture*, b2Fixture*>(fixtureA, fixtureB));
        }
        else if(fixtureB->IsSensor() && (fixtureA->GetBody()->GetType() == b2_dynamicBody)){
            m_fixturePairs.erase(std::pair<b2Fixture*, b2Fixture*>(fixtureB, fixtureA));
        }
    }

    std::set<fixturePair> m_fixturePairs;
};

#endif // MYCONTACTLISTENER_H
