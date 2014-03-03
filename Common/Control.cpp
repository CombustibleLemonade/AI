#include <iostream>
#include <vector>

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

bool NewlyPressedDown = false;

float OldLocationX = 0;
float OldLocationY = 0;
float NewLocationX = 0;
float NewLocationY = 0;

void InitFunc() {
    int i = 0;
    while (i < 10) {
        NewBlock = new Block("Plus.png");
        i++;
    }
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
    }
}

void ScrollFunc (double XOffset, double YOffset) {
    if (YOffset == 1) {
        ReturnDefaultCamera2d()->Zoom *= 1.1;
    } else if (YOffset == -1) {
        ReturnDefaultCamera2d()->Zoom /= 1.1;
    }
}
