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

int Fullscreen = 0;
float Zoom = 200;

int OldLocationX = 0;
int OldLocationY = 0;
float NewLocationX = 0;
float NewLocationY = 0;
GLint LocationID;
Block* CollidingBlock;
int Scroll = false;

void Keyboard (unsigned char Key, int x, int y) {
    /*if (Key == 27) {
        if (!Fullscreen){
            glutFullScreen();
            Fullscreen = 1;
        }
        else{
            glutReshapeWindow(1280, 720);
            Fullscreen = 0;
        }
    }*/
}

void Mouse (int Button, int State, int X, int Y){
    int i;
    if (Button == 4 && Zoom > 5.0 && State == GLUT_DOWN){
        Zoom *= 0.9;
        SetCameraZoom(Zoom);
    }
    if (Button == 3 && Zoom < 500.0 && State == GLUT_DOWN){
        Zoom *= 1/0.9;
        SetCameraZoom(Zoom);
    }
    if (Button ==1){
        OldLocationX = X;
        OldLocationY = Y;
        if (State == GLUT_DOWN) {
            Scroll = true;
            glutSetCursor(GLUT_CURSOR_CROSSHAIR);
        }else{
            Scroll = false;
            glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
        }
    }
    cout << Button << endl;
    if (Button == 0 && CollidingBlock){
        CollidingBlock->ThisProgram->TargetFullscreen = 1.0;
    }
}

void Motion (int X, int Y) {
    if (Scroll == true){
        int i = 0;
        NewLocationX += (X - OldLocationX)/Zoom*2;
        NewLocationY -= (Y - OldLocationY)/Zoom*2;

        SetCameraPosition(NewLocationX, NewLocationY);

        OldLocationX = X;
        OldLocationY = Y;
    }
}

void PassiveMotion(int X, int Y){
    int XBlockArrayPos;
    int YBlockArrayPos;

    int ScreenXRes = glutGet(GLUT_WINDOW_WIDTH);
    int ScreenYRes = glutGet(GLUT_WINDOW_HEIGHT);
    float RealXPosition = ((X-ScreenXRes/2)/Zoom*2)-NewLocationX;
    float RealYPosition = -((Y-ScreenYRes/2)/Zoom*2)-NewLocationY;

    CollidingBlock = CheckBlockCollision(RealXPosition, RealYPosition);
    if (CollidingBlock){
        glutSetCursor(GLUT_CURSOR_INFO);
    } else {
        glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
    }
}
