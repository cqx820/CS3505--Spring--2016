#include "buoyancy.h"
#include "QDebug"

Buoyancy::Buoyancy(MyContactListner *listner)
{
    this->listener = listner;
    this->logic = new BuoyancyLogic;
    //Leave for initializing
}

Buoyancy::~Buoyancy(){
    delete listener;
    delete logic;
}

//Code from iforce2d
void Buoyancy::Step(){
   // qDebug()<<"Called!!!";
    std::set<fixturePair>::iterator it = listener->m_fixturePairs.begin();
    std::set<fixturePair>::iterator end = listener->m_fixturePairs.end();
    while(it != end){
        b2Fixture *fixtureA = it->first;
        b2Fixture *fixtureB = it->second;
       // float density = fixtureA->GetDensity();
        std::vector<b2Vec2> intersectionPoints;
        if(logic->findIntersection(fixtureA, fixtureB, intersectionPoints)){
            float area = 0;
            b2Vec2 centroid = logic->computeCentroid(intersectionPoints, area);
            float displaceMass = fixtureA->GetDensity() * area;
            b2Vec2 gravity(0, -10);
            b2Vec2 buoyancyForce = displaceMass/2 * (-gravity);
            fixtureB->GetBody()->ApplyForce(buoyancyForce, centroid, true);
        }
        //apply drag separately for each polygon edge
          for (int i = 0; i < intersectionPoints.size(); i++) {
              //the end points and mid-point of this edge
              b2Vec2 v0 = intersectionPoints[i];
              b2Vec2 v1 = intersectionPoints[(i+1)%intersectionPoints.size()];
              b2Vec2 midPoint = 0.5f * (v0+v1);

              //find relative velocity between object and fluid at edge midpoint
              b2Vec2 velDir = fixtureB->GetBody()->GetLinearVelocityFromWorldPoint( midPoint ) -
                              fixtureA->GetBody()->GetLinearVelocityFromWorldPoint( midPoint );
              float vel = velDir.Normalize();

              b2Vec2 edge = v1 - v0;
              float edgeLength = edge.Normalize();
              b2Vec2 normal = b2Cross(-1,edge); //gets perpendicular vector

              float dragDot = b2Dot(normal, velDir);
              if ( dragDot < 0 )
                  continue; //normal points backwards - this is not a leading edge

              float dragMag = dragDot * edgeLength * fixtureA->GetDensity() * vel * vel;
              b2Vec2 dragForce = dragMag * -velDir;
              fixtureB->GetBody()->ApplyForce( dragForce, midPoint,true );
          }
        ++it;
    }


}
