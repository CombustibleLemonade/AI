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
#include "Blocks.hpp"

using namespace std;

int Fullscreen = 0;
float Zoom = 200;

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
            glutReshapeWindow(1280, 720);
            Fullscreen = 0;
        }
    }
}

void Mouse (int Button, int State, int X, int Y){
    int i;
    if (Button == 4 && Zoom > 5.0 && State == GLUT_DOWN){
        Zoom *= 0.9;
        GLint ZoomID = glGetUniformLocation(KnobReturn()->Program, "zoom");
        glUniform1f(ZoomID, Zoom);
        i = 0;
        while (i < ProgramCountReturn()) {
            glUseProgram(ProgramReturn(i)->Program);
            GLint ZoomID = glGetUniformLocation(ProgramReturn(i)->Program, "zoom");
            glUniform1f(ZoomID, Zoom);
            i++;
        }
        glutPostRedisplay();
    }
    if (Button == 3 && Zoom < 500.0 && State == GLUT_DOWN){
        Zoom *= 1/0.9;
        GLint ZoomID = glGetUniformLocation(KnobReturn()->Program, "zoom");
        glUniform1f(ZoomID, Zoom);
        i = 0;
        while (i < ProgramCountReturn()) {
            glUseProgram(ProgramReturn(i)->Program);
            GLint ZoomID = glGetUniformLocation(ProgramReturn(i)->Program, "zoom");
            glUniform1f(ZoomID, Zoom);
            i++;
        }
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
        int i = 0;
        NewLocationX += (X - OldLocationX)/Zoom*2;
        NewLocationY -= (Y - OldLocationY)/Zoom*2;
        while (i < ProgramCountReturn()) {
            glUseProgram(ProgramReturn(i)->Program);
            LocationID = glGetUniformLocation(ProgramReturn(i)->Program, "Position");
            glUniform2f(LocationID, NewLocationX, NewLocationY);
            i++;
        }
        glUseProgram(KnobReturn()->Program);
        LocationID = glGetUniformLocation(KnobReturn()->Program, "Position");
        glUniform2f(LocationID, NewLocationX, NewLocationY);
        glutPostRedisplay();
        OldLocationX = X;
        OldLocationY = Y;
    }

}
