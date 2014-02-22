#include <iostream>
#include <vector>

#ifdef __APPLE__
#include <GLEW/glew.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

#include "Display.hpp"
#include "Blocks.hpp"
#include "Control.hpp"

using namespace std;

Block* NewBlock;

bool MMBDown = false;
int OldLocationX = 0;
int OldLocationY = 0;
float NewLocationX = 0;
float NewLocationY = 0;

void InitFunc() {
    NewBlock = new Block("Plus.png");
}

void KeyboardFunc (unsigned char Key, int x, int y) {
    cout << Key << endl;
    if (Key == 27) {
        glutLeaveMainLoop();
    }
}

void MouseFunc(int Button, int State, int x, int y) {
    if (Button == 1) {
        if (State == GLUT_DOWN) {
            MMBDown = true;
        } else {
            MMBDown = false;
        }
    }
    OldLocationX = x;
    OldLocationY = y;
}

void MotionFunc (int x, int y) {
    if (MMBDown) {
        NewLocationX += (x - OldLocationX)/200.0*2;
        NewLocationY -= (y - OldLocationY)/200.0*2;

        ReturnDefaultCamera2d()->x = NewLocationX;
        ReturnDefaultCamera2d()->y = NewLocationY;
        cout << NewLocationX << " " << NewLocationY << endl;

        OldLocationX = x;
        OldLocationY = y;
    }
}
