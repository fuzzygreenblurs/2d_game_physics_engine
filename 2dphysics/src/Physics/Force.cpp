#include "Force.h"

/*
general C++ note: a reference is THE ACTUAL OBJECT, NOT a copy of the object (i.e. this is pass-by-reference not pass-by-value)
if you have a pointer to a body and you want to call this function, you need to do:
    `Force::GenerateDragForce(*body, k);`

- *body dereferences the body pointer and passes the body object itself
*/

Vec2 Force::GenerateDragForce(const Body& body, float k)
{
    Vec2 dragForce = Vec2(0.0, 0.0);

    if(body.velocity.MagnitudeSquared() > 0) {
        Vec2 dragDirection = body.velocity.UnitVector() * -1.0;
        float dragMagnitude = k * body.velocity.MagnitudeSquared();

        dragForce = dragDirection * dragMagnitude;
    }

    return dragForce;
}

Vec2 Force::GenerateFrictionForce(const Body& body, float k)
{
    Vec2 frictionForce = Vec2(0.0, 0.0);
    Vec2 frictionDirection = body.velocity.UnitVector() * -1.0;
    float frictionMagnitude = k;

    frictionForce = frictionDirection * frictionMagnitude;

    return frictionForce;
}

Vec2 Force::GenerateGravitationalForce(const Body& a, const Body& b, float g)
{
    Vec2 d = (b.position - a.position);
    float distanceSquared = d.MagnitudeSquared();
    Vec2 attractionDirection = d.UnitVector();

    float attractionMagnitude = g * (a.mass * b.mass) / distanceSquared;

    Vec2 attractionForce = attractionDirection * attractionMagnitude;
    return attractionForce;
}

Vec2 Force::GenerateSpringForce(const Body& body, Vec2 anchor, float restLength, float k) {
    Vec2 d = body.position - anchor;
    float displacement = d.Magnitude() - restLength;

    Vec2 springDirection = d.UnitVector();
    float springMagnitude = -k * displacement;

    Vec2 springForce = springDirection * springMagnitude;
    return springForce;
};