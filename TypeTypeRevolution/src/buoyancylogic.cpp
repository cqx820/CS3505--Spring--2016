#include "buoyancylogic.h"
#include <vector>

BuoyancyLogic::BuoyancyLogic(){
}

b2Vec2 BuoyancyLogic::computeCentroid(vector<b2Vec2> vs, float &area){
    int count = (int)vs.size();
    b2Assert(count >= 3);
    b2Vec2 c;
    c.Set(0.0f, 0.0f);
    area = 0.0f;
    b2Vec2 pRef(0.0f, 0.0f);
    const float32 inv3 = 1.0f / 3.0f;
    for(int i = 0; i < count; ++i){
        b2Vec2 p1 = pRef;
        b2Vec2 p2 = vs[i];
        b2Vec2 p3 = i + 1 < count ? vs[i + 1]:vs[0];
        b2Vec2 e1 = p2 - p1;
        b2Vec2 e2 = p3 - p1;
        float32 D = b2Cross(e1, e2);
        float32 triangleArea = 0.5f * D;
        area += triangleArea;
        c += triangleArea * inv3 * (p1 + p2 + p3);
    }
    if(area > b2_epsilon){
        c *= 1.0f / area;
    }
    else{
        area = 0;
    }
    return c;
}

bool BuoyancyLogic::inside(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 p){
    return (cp2.x - cp1.x) * (p.y - cp1.y) > (cp2.y - cp1.y) * (p.x - cp1.x);
}

b2Vec2 BuoyancyLogic::intersection(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 s, b2Vec2 e){
    b2Vec2 dc(cp1.x - cp2.x, cp1.y - cp2.y);
    b2Vec2 dp(s.x - e.x, s.y - e.y);
    float n1 = cp1.x * cp2.y - cp1.y * cp2.x;
    float n2 = s.x * e.y - s.y * e.x;
    float n3 = 1.0 / (dc.x * dp.y - dc.y * dp.x);
    return b2Vec2((n1 * dp.x - n2 * dc.x) * n3, (n1 * dp.y - n2 * dc.y) * n3);
}

bool BuoyancyLogic::findIntersection(b2Fixture *fA, b2Fixture *fB, vector<b2Vec2> &vertices){
    if(!(fA->GetShape()->GetType() == b2Shape::e_polygon
         && fB->GetShape()->GetType() == b2Shape::e_polygon)){
        return false;
    }
    b2PolygonShape *polyA = dynamic_cast<b2PolygonShape*>(fA->GetShape());
    b2PolygonShape *polyB = dynamic_cast<b2PolygonShape*>(fB->GetShape());
    for(int32 i = 0; i < polyA->GetVertexCount(); i++){
        vertices.push_back(fA->GetBody()->GetWorldPoint(polyA->GetVertex(i)));
    }
    std::vector<b2Vec2> clipPolygon;
    for(int32 i = 0; i < polyB->GetVertexCount(); i++){
        clipPolygon.push_back(fB->GetBody()->GetWorldPoint(polyB->GetVertex(i)));
    }
    b2Vec2 cp1 = clipPolygon[clipPolygon.size() - 1];
    for(unsigned i = 0; i < clipPolygon.size(); i++){
        b2Vec2 cp2 = clipPolygon[i];
        if(vertices.empty()){
            return false;
        }
        std::vector<b2Vec2> inputs = vertices;
        vertices.clear();
        b2Vec2 s = inputs[inputs.size() - 1];
        for(unsigned j = 0; j < inputs.size(); j++){
            b2Vec2 e = inputs[j];
            if(inside(cp1, cp2, e)){
                if(!inside(cp1, cp2, s)){
                    vertices.push_back(intersection(cp1, cp2, s, e));
                }
                vertices.push_back(e);
            }
            else if(inside(cp1, cp2, s)){
                vertices.push_back(intersection(cp1, cp2, s, e));
            }
            s = e;
        }
        cp1 = cp2;
    }
    return !vertices.empty();
}






















