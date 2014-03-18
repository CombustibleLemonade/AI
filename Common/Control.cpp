#include <iostream>
#include <vector>
#include <thread>

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

Block* NewBlock;
float TimeAddedUp;
float AmountOfMeasurements;

bool NewlyPressedDown = false;

float OldLocationX = 0;
float OldLocationY = 0;
float NewLocationX = 0;
float NewLocationY = 0;

void LoadCubes(int i) {
    int j = 0;
    while (j<30) {
        NewBlock = new Block("Plus.png");
        NewBlock->Translate(Vector2(j*2.5, i*2.5));
        j++;
    }
}

void InitFunc() {
    Block NewBlock("Minus.png");
}

void DisplayFunc () {
    if(glfwGetKey(ReturnWindow(), GLFW_KEY_ESCAPE)) {
        ExitMainLoop();
    }
    if(glfwGetMouseButton(ReturnWindow(), GLFW_MOUSE_BUTTON_MIDDLE)) {
        double x, y;
        glfwGetCursorPos(ReturnWindow(), &x, &y);
        if (NewlyPressedDown) {
            OldLocationX = x;
            OldLocationY = y;
            NewlyPressedDown = false;
        }
        NewLocationX += (x - OldLocationX)/ReturnDefaultCamera2d()->Zoom*2;
        NewLocationY -= (y - OldLocationY)/ReturnDefaultCamera2d()->Zoom*2;

        ReturnDefaultCamera2d()->x = NewLocationX;
        ReturnDefaultCamera2d()->y = NewLocationY;

        OldLocationX = x;
        OldLocationY = y;
    }else{
        NewlyPressedDown = true;
        double x, y;
        int WindowXDimension, WindowYDimension;
        glfwGetWindowSize(ReturnWindow(), &WindowXDimension, &WindowYDimension);
        glfwGetCursorPos(ReturnWindow(), &x, &y);
        x -= 0.5 * WindowXDimension;
        y -= 0.5 * WindowYDimension;
        y *= -1;

        x /= ReturnDefaultCamera2d()->Zoom/2;
        y /= ReturnDefaultCamera2d()->Zoom/2;

        x -= ReturnDefaultCamera2d()->x;
        y -= ReturnDefaultCamera2d()->y;

        CollisionCheck(Vector2(x, y));
    }
    AmountOfMeasurements++;
    TimeAddedUp = TimeAddedUp + glfwGetTime();
    glfwSetTime(0);
    //cout << 1/(TimeAddedUp/AmountOfMeasurements) << endl;
}

void ScrollFunc (double XOffset, double YOffset) {
    if (YOffset == 1) {
        ReturnDefaultCamera2d()->Zoom *= 1.1;
    } else if (YOffset == -1) {
        ReturnDefaultCamera2d()->Zoom /= 1.1;
    }
}
