#include "Application.h"
#include "./Physics/Constants.h"
#include "./Physics/Force.h"
#include "./Physics/Shape.h"
#include "./Physics/CollisionDetection.h"
#include "./Physics/Contact.h"
#include <iostream>

bool Application::IsRunning()
{
    return running;
}

void Application::Setup()
{
    running = Graphics::OpenWindow();
    // anchor = Vec2(Graphics::Width() / 2.0, 30);
    
    Body* bigBall = new Body(CircleShape(100), 400, 400, 0.0);

    bodies.push_back(bigBall);
}

void Application::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            // triggered when the window is closed (using the mouse for example)
            case SDL_QUIT:
                running = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
                if (event.key.keysym.sym == SDLK_UP)
                    pushForce.y -= 5 * PIXELS_PER_METER;
                if (event.key.keysym.sym == SDLK_DOWN)
                    pushForce.y += 5 * PIXELS_PER_METER;
                if (event.key.keysym.sym == SDLK_RIGHT)
                    pushForce.x += 5 * PIXELS_PER_METER;
                if (event.key.keysym.sym == SDLK_LEFT)
                    pushForce.x -= 5 * PIXELS_PER_METER;
                break;

            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_UP)
                    pushForce.y = 0;
                if (event.key.keysym.sym == SDLK_DOWN)
                    pushForce.y = 0;
                if (event.key.keysym.sym == SDLK_RIGHT)
                    pushForce.x = 0;
                if (event.key.keysym.sym == SDLK_LEFT)
                    pushForce.x = 0;
                break;

            // case SDL_MOUSEMOTION:
            //     mouseCursor.x = event.motion.x;
            //     mouseCursor.y = event.motion.y;
            //     break;

            case SDL_MOUSEBUTTONDOWN:
                // if(!leftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT) {
                //     leftMouseButtonDown = true;
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    mouseCursor.x = x;
                    mouseCursor.y = y;

                    Body* smallBall = new Body(CircleShape(20), x, y, 1.0);
                    smallBall->restitution = 0.9;
                    bodies.push_back(smallBall);
                // }
                break;

            // case SDL_MOUSEMOTION:
            //     int x, y;
            //     SDL_GetMouseState(&x, &y);
            //     bodies[0]->position.x = x;
            //     bodies[0]->position.y = y;
            //     break;

            // case SDL_MOUSEBUTTONUP:
            //     if(leftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT) {
            //         leftMouseButtonDown = false;
            //         Vec2 impulseDirection = (bodies[0]->position - mouseCursor).UnitVector();
            //         float impulseMagnitude = (bodies[0]->position - mouseCursor).Magnitude() * 5.0;
            //         bodies[0]->velocity = impulseDirection * impulseMagnitude;
            //     }
            //     break;
        }
    }
}

// update is called several times per second to update objects
void Application::Update() {
    Graphics::ClearScreen(0xFF000000);
    // ensure that program runs at 60FPS across platforms
    static int timePreviousFrame;
    int timeToWait = MILLISECONDS_PER_FRAME - (SDL_GetTicks() - timePreviousFrame);

    if(timeToWait > 0)
        SDL_Delay(timeToWait);

    float deltaTime = (SDL_GetTicks() - timePreviousFrame) / 1000.0f; 
    if (deltaTime > (MILLISECONDS_PER_FRAME / 1000.0f))
        deltaTime = (MILLISECONDS_PER_FRAME / 1000.f);

    timePreviousFrame = SDL_GetTicks();
    
    for (auto body: bodies) {
        // body->AddForce(pushForce);

        // Vec2 drag = Force::GenerateDragForce(*body, 0.01);
        // body->AddForce(drag);

        Vec2 weight = Vec2(0.0, body->mass * 9.8 * PIXELS_PER_METER);
        body->AddForce(weight);
        
        // Vec2 wind = Vec2(2.0 * PIXELS_PER_METER, 0.0);
        // body->AddForce(wind);
        
        // float torque = 200;
        // body->AddTorque(torque);
    }

    // Vec2 springForce = Force::GenerateSpringForce(*bodies[0], anchor, restLength, k);
    // bodies[0]->AddForce(springForce);

    for (auto body: bodies)
        body->Update(deltaTime);

    for(int i = 0; i <= bodies.size() - 1; i++) {
        for(int j = i + 1; j < bodies.size(); j++) {
            Body* a = bodies[i];
            Body* b = bodies[j];
            Contact contact;
            if(CollisionDetection::isColliding(a, b, contact)) {
                Graphics::DrawFillCircle(
                    contact.start.x,
                    contact.start.y,
                    3,
                    0xFFFF00FF
                );

                Graphics::DrawFillCircle(
                    contact.end.x,
                    contact.end.y,
                    3,
                    0xFFFF00FF
                );

                Graphics::DrawLine(
                    contact.start.x,
                    contact.start.y,
                    contact.start.x + contact.normal.x * 15,
                    contact.start.y + contact.normal.y * 15,
                    0xFFFF00FF
                );

                a->isColliding = true;
                b->isColliding = true;

                // resolve collision using penetration and impulse methods together
                contact.ResolveCollision();
            } else {
                a->isColliding = false;
                b->isColliding = false;
            }
        }
    }

    for (auto body: bodies) {
        // TODO: limit the bodies position to stay within the boundaries of the window
        if(body->shape->GetType() == CIRCLE) {

            /*
            dynamic_cast is useful when you don't know what the dynamic type of the object is
            it returns a null pointer if the object referred to doesn't contain the type casted to as a base class
                - when you cast to a reference, a bad_cast exception is thrown in that case

            note: cannot use dynamic_cast for downcast (casting to a derived class) if the argument type is not polymorphic
            - For example, the following code is not valid, because Base doesn't contain any virtual function:

                struct Base {};
                struct Derived : Base {};
                
                int main() {
                    Derived d; Base *b = &d;
                    dynamic_cast<Derived*>(b); // Invalid
                }
            */

            CircleShape* circleShape = dynamic_cast<CircleShape*>(body->shape);
            if(body->position.x - circleShape->radius < 0) {
                body->position.x = circleShape->radius;
                body->velocity.x *= -0.9;
            } else if(body->position.x + circleShape->radius >= Graphics::Width()) {
                body->position.x = Graphics::Width() - circleShape->radius;
                body->velocity.x *= -0.9;
            }
            
            if(body->position.y - circleShape->radius < 0) {
                body->position.y = circleShape->radius;
                body->velocity.y *= -0.9;
            } else if(body->position.y + circleShape->radius >= Graphics::Height()) {
                body->position.y = Graphics::Height() - circleShape->radius;
                body->velocity.y *= -0.9;
            }
        }
    }
}

// render called several times per second to draw objects
void Application::Render() {
    // Graphics::ClearScreen(0xFF000000);

    for (auto body: bodies) {
        uint32_t color = body->isColliding ? 0xFF0000FF : 0xFFFFFFFF;

        if (body->shape->GetType() == CIRCLE) {
            CircleShape *circleShape = dynamic_cast<CircleShape*>(body->shape);
            Graphics::DrawCircle(
                body->position.x, 
                body->position.y, 
                circleShape->radius,
                body->rotation,         // angle 
                color
            );
        }

        if (body->shape->GetType() == BOX) {
            BoxShape* boxShape = dynamic_cast<BoxShape*>(body->shape);
            Graphics::DrawPolygon(body->position.x, body->position.y, boxShape->worldVertices, 0xFFFFFFFF);
        }
    }

    Graphics::RenderFrame();
}

void Application::Destroy() {
    for (auto body: bodies)
        delete body;

    Graphics::CloseWindow();
}