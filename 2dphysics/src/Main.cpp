#include "Application.h"

int main(int argc, char *args[]) {
    Application app;
    
    app.Setup();

    while (app.IsRunning()) {
        app.Input();    // polls for user input to close window (atm)
        app.Update();   // updates object properties (position, velocity, etc)
        app.Render();   // draws updated objects on the screen
    }

    app.Destroy();

    return 0;
}