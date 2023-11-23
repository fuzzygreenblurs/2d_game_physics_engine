#include "Application.h"
#include "./Physics/Constants.h"

bool Application::IsRunning() {
    return running;
}

void Application::Setup() {
    running = Graphics::OpenWindow();
    particle = new Particle(50, 100, 1.0);
    particle->radius = 20;
    
    // TODO: setup objects in the scene

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
                break;
        }   
    }
}

// update is called several times per second to update objects
void Application::Update() {
    
    // ensure that program runs at 60FPS across platforms
    static int timePreviousFrame;
    int timeToWait = MILLISECONDS_PER_FRAME - (SDL_GetTicks() - timePreviousFrame);

    if(timeToWait > 0)
        SDL_Delay(timeToWait);

    float deltaTime = (SDL_GetTicks() - timePreviousFrame) / 1000.0f; 
    if (deltaTime > (MILLISECONDS_PER_FRAME / 1000.0f))
        deltaTime = (MILLISECONDS_PER_FRAME / 1000.f);

    timePreviousFrame = SDL_GetTicks();
    
    // integrating acceleration and velocity to find the new position
    particle->acceleration = Vec2(200, 10 * PIXELS_PER_METER);
    // particle->acceleration = Vec2(100, 9.8 * PIXELS_PER_METER);
    particle->velocity += particle->acceleration * deltaTime;
    particle->position += particle->velocity * deltaTime;

    // TODO: limit the particles position to stay within the boundaries of the window
    if(particle->position.x - particle-> radius < 0) {
        particle->position.x = particle->radius;
        particle->velocity.x *= -0.9;
    } else if(particle->position.x + particle-> radius >= Graphics::Width()) {
        particle->position.x = Graphics::Width() - particle->radius;
        particle->velocity.x *= -0.9;
    }
    
    if(particle->position.y - particle->radius < 0) {
        particle->position.y = particle->radius;
        particle->velocity.y *= -0.9;
    } else if(particle->position.y + particle->radius >= Graphics::Height()) {
        particle->position.y = Graphics::Height() - particle->radius;
        particle->velocity.y *= -0.9;
    }
}

// render called several times per second to draw objects
void Application::Render() {
    Graphics::ClearScreen(0xFF056263);
    Graphics::DrawFillCircle(particle->position.x, particle->position.y, particle->radius, 0xFFFFFFFF);
    Graphics::RenderFrame();
}

void Application::Destroy() {
    delete particle;
    // TODO: destroy all objects in the scene

    Graphics::CloseWindow();
}