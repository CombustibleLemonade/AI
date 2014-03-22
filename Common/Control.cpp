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

bool Drag = false;
Vector2 LastClickLocation;
Vector2 CursorLocation;

Block* Test;

void InitFunc() {
    //Block NewBlock("Minus.png");
    Test = new Block("Minus.png");
}

void MouseFunc(int Button, int Action, int Mods) {
    if (Button == 2) {
        Drag = !Drag;
    }
}

void ScrollFunc(double XOffset, double YOffset){
    ReturnDefaultCamera2d()->Zoom *= pow(1.1,YOffset);
}

void MotionFunc(int x, int y){
    CursorLocation = Vector2(x, y);
    CursorLocation /= ReturnDefaultCamera2d()->Zoom / 2;
    Vector2 DeltaLocation = CursorLocation - LastClickLocation;
    if (Drag){
        ReturnDefaultCamera2d()->x += DeltaLocation.x;
        ReturnDefaultCamera2d()->y -= DeltaLocation.y;
    } else {
        CollisionCheck(CursorLocation);
    }
    LastClickLocation = CursorLocation;
}
