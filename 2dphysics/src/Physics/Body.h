#ifndef BODY_H
#define BODY_H
#include "Vec2.h"
#include "Shape.h"

struct Body {
    bool isColliding = false;

    // linear motion
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

    // angular motion
    float rotation;
    float angularVelocity;
    float angularAcceleration;

    // forces and torque
    Vec2 sumForces;
    float sumTorque;

    // moment of inertia: most calculations use 1/I, we can just calculate this directly
    float I;
    float invI;

    // mass: most calculations use 1/mass, we can just calculate this directly
    float mass;
    float invMass;

    // impulse
    float restitution;

    Shape* shape = nullptr;

    Body(const Shape& shape, float x, float y, float mass);
    void IntegrateLinear(float dt);
    void IntegrateAngular(float dt);
    void AddForce(const Vec2& force);
    void ClearForces();
    void AddTorque(float torque);
    void ClearTorque();
    void Update(float const deltaTime);
    bool IsStatic() const;
    void ApplyImpulse(const Vec2& j);

    ~Body(); 
};

#endif