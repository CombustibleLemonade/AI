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
#include "Control.hpp"

using namespace std;

int Fullscreen = 0;
float Zoom = 500;

int OldLocationX = 0;
int OldLocationY = 0;
float NewLocationX = 0;
float NewLocationY = 0;
GLint LocationID;

int Scroll = false;

void Keyboard (unsigned char Key, int x, int y) {
    if (Key == 27) {
        if (!Fullscreen){
            glutFullScreen();
            Fullscreen = 1;
        }
        else{
            glutReshapeWindow(1600, 900);
            Fullscreen = 0;
        }
    }
}

void Mouse (int Button, int State, int X, int Y){
    if (Button == 4 && Zoom > 10.0 && State == GLUT_DOWN){
        Zoom *= 0.9;
        GLint ZoomID = glGetUniformLocation(ProgramReturn(), "zoom");
        glUniform1f(ZoomID, Zoom);
        glutPostRedisplay();
    }
    if (Button == 3 && Zoom < 500.0 && State == GLUT_DOWN){
        Zoom *= 1/0.9;
        GLint ZoomID = glGetUniformLocation(ProgramReturn(), "zoom");
        glUniform1f(ZoomID, Zoom);
        glutPostRedisplay();
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
}

void Motion (int X, int Y) {
    if (Scroll == true){
        NewLocationX += (X - OldLocationX)/Zoom*2;
        NewLocationY -= (Y - OldLocationY)/Zoom*2;
        LocationID = glGetUniformLocation(ProgramReturn(), "Position");
        //cout << "X:" << NewLocationX << "  Y: " << NewLocationY << endl;
        glUniform2f(LocationID, NewLocationX, NewLocationY);
        glutPostRedisplay();
        OldLocationX = X;
        OldLocationY = Y;
    }

}

