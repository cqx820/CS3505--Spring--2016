#ifndef BUOYANCYLOGIC_H
#define BUOYANCYLOGIC_H
#include <set>
#include <vector>
#include <Box2D/Box2D.h>
using namespace std;
typedef pair<b2Fixture*, b2Fixture*> fixturePair;

class BuoyancyLogic
{
public:
    BuoyancyLogic();
    b2Vec2 computeCentroid(vector<b2Vec2> vs, float &area);
    bool inside(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 p);
    b2Vec2 intersection(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 s, b2Vec2 e);
    bool findIntersection(b2Fixture *fA, b2Fixture *fB, vector<b2Vec2> &vertices);


};

#endif // BUOYANCYLOGIC_H
