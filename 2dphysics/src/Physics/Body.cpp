#include "Body.h"
#include <iostream>
#include <math.h>

Body::Body(const Shape& shape, float x, float y, float mass) 
{
    this->shape = shape.Clone();
    
    this->position = Vec2(x, y);
    this->velocity = Vec2(0,0);
    this->acceleration = Vec2(0,0);
    this->mass = mass;
    this->sumForces = Vec2(0,0);

    this->rotation = 0.0;
    this->angularVelocity = 0.0;
    this->angularAcceleration = 0.0;
    this->sumTorque = 0.0;
    this->restitution = 1.0;

    I = shape.GetMomentOfInertia() * mass;
    if (I != 0.0) {
        this->invI = 1.0 / I;
    } else {
        this->invI = 0.0;
    }

    if(mass != 0.0) {
        this->invMass = 1.0 / mass;
    } else {
        // static object (object of infinite mass which never moves)
        this->invMass = 0.0;
    }
    std::cout << "body constructor called." << std::endl;
}

Body::~Body() 
{
    delete shape;
    std::cout << "body destructor called." << std::endl;
}

void Body::AddForce(const Vec2& force) 
{
    sumForces += force;
}
void Body::AddTorque(const float torque) 
{
    sumTorque += torque;
}

void Body::ClearForces() 
{
    sumForces = Vec2(0.0, 0.0);
}

void Body::ClearTorque() 
{
    sumTorque = 0.0;
}
    
void Body::IntegrateLinear(float dt) 
{
    if(IsStatic()) {
        return;
    }

    acceleration = sumForces * invMass;
    velocity += acceleration * dt;
    position += velocity * dt;

    ClearForces();
}

void Body::IntegrateAngular(float dt) 
{
    angularAcceleration = sumTorque * invI;
    angularVelocity += angularAcceleration * dt;
    rotation += angularVelocity * dt;

    ClearTorque();
}

void Body::Update(const float deltaTime) 
{
    IntegrateLinear(deltaTime);
    IntegrateAngular(deltaTime);

    bool isPolygon = shape->GetType() == POLYGON || shape->GetType() == BOX;
    if (isPolygon)
    {
        PolygonShape *polygonShape = dynamic_cast<PolygonShape *>(shape);
        polygonShape->UpdateVertices(rotation, position);
    }
}

void Body::ApplyImpulse(const Vec2& j)
{
    if(IsStatic()) {
        return;
    }

    velocity += j * invMass;
}

bool Body::IsStatic() const 
{
    const float epsilon = 0.005f;
    return fabs(invMass) < epsilon;
}
