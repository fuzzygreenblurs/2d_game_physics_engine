#include "Shape.h"
#include <iostream>

CircleShape::CircleShape(float radius) {
    this->radius = radius; 
    std::cout << "circle shape constructor called" << std::endl;
};

CircleShape::~CircleShape() {
    std::cout << "circle shape destructor called" << std::endl;
};

ShapeType CircleShape::GetType() const {
    return CIRCLE;
};

Shape* CircleShape::Clone() const
{
    return new CircleShape(radius);
};

float CircleShape::GetMomentOfInertia() const
{
    //this is simply the geometric component of the MoI of a solid circle. 
    // still need to multiply by mass
    return 0.5 * (radius * radius);
};

PolygonShape::PolygonShape(const std::vector<Vec2> vertices)
{
    // TODO
};

PolygonShape::~PolygonShape()
{
    // TODO
};

ShapeType PolygonShape::GetType() const
{
    return POLYGON;
};

Shape *PolygonShape::Clone() const
{
    return new PolygonShape(localVertices);
};

float PolygonShape::GetMomentOfInertia() const
{
    // this is simply the geometric component of the MoI of a solid circle.
    //  still need to multiply by mass
    // TODO:
    return 0.0;
};

void PolygonShape::UpdateVertices(float angle, const Vec2& position) {
    // rotate and translate each vertex
    for(int i = 0; i < localVertices.size(); i++) {
        worldVertices[i] = localVertices[i].Rotate(angle);
        worldVertices[i] += position;
    }
};

BoxShape::BoxShape(float width, float height)
{
    this->width = width;
    this->height = height;
    
    // load the local space vertices of the box in clockwise fashion
    localVertices.push_back(Vec2(-width / 2.0, -height / 2.0));
    localVertices.push_back(Vec2(+width / 2.0, -height / 2.0));
    localVertices.push_back(Vec2(+width / 2.0, +height / 2.0));
    localVertices.push_back(Vec2(-width / 2.0, +height / 2.0));
    
    worldVertices.push_back(Vec2(-width / 2.0, -height / 2.0));
    worldVertices.push_back(Vec2(+width / 2.0, -height / 2.0));
    worldVertices.push_back(Vec2(+width / 2.0, +height / 2.0));
    worldVertices.push_back(Vec2(-width / 2.0, +height / 2.0));
};

BoxShape::~BoxShape()
{
    // TODO
};

ShapeType BoxShape::GetType() const
{
    return BOX;
};

Shape *BoxShape::Clone() const
{
    return new BoxShape(width, height);
};

float BoxShape::GetMomentOfInertia() const
{
    // this is simply the geometric component of the MoI of a solid circle.
    //  still need to multiply by mass
    return 0.083333 * ((width * width) + (height * height));
};

