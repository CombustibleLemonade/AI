#include <iostream>
#include <vector>
#include <thread>
#include <math.h>

#ifdef __APPLE__
#include <GLEW/glew.h>
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

#include "Display.hpp"
#include "Blocks.hpp"
#include "Control.hpp"

using namespace std;

bool NewDrag = true;
bool Drag = false;
Vector2 LastClickLocation;
Vector2 CursorLocation;

Block* Test;

void InitFunc() {
    //Block NewBlock("Minus.png");
    Test = new Block("Minus.png");
}

void DisplayFunc () {
    if (glfwGetKey(ReturnWindow(), GLFW_KEY_ESCAPE)) {
        ExitMainLoop();
    }
}

void MouseFunc(int Button, int Action, int Mods) {
    if (Button == 2) {
        Drag = !Drag;
        NewDrag = true;
    }
}

void ScrollFunc(double XOffset, double YOffset){
    ReturnDefaultCamera2d()->Zoom *= pow(1.1,YOffset);
}

void MotionFunc(int x, int y){
    CursorLocation = Vector2(x, y);

    if (Drag){
        Vector2 DeltaLocation = CursorLocation - LastClickLocation; // This can be optimised later on
        if (NewDrag) {
            DeltaLocation = Vector2(0.0, 0.0);
            NewDrag = false;
        } else {
            DeltaLocation /= ReturnDefaultCamera2d()->Zoom / 2;
        }
        ReturnDefaultCamera2d()->x += DeltaLocation.x;
        ReturnDefaultCamera2d()->y -= DeltaLocation.y;
    } else {
        CursorLocation.y *= -1;
        int ScreenResX;
        int ScreenResY;
        glfwGetFramebufferSize(ReturnWindow(), &ScreenResX, &ScreenResY);
        CursorLocation += Vector2(-ScreenResX, ScreenResY)/2;
        CursorLocation /= ReturnDefaultCamera2d()->Zoom / 2;
        CursorLocation.x -= ReturnDefaultCamera2d()->x;
        CursorLocation.y -= ReturnDefaultCamera2d()->y;
        cout << CursorLocation.x << " " << CursorLocation.y << endl;

        CollisionCheck(CursorLocation);
    }
    LastClickLocation = CursorLocation;
}
