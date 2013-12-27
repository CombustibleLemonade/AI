#ifdef __APPLE__
#include <GLEW/glew.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif
#include <iostream>

#include "Display.hpp"
#include "Control.hpp"

using namespace std;

int Fullscreen = 0;
float Zoom = 500;

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
    if (Button == 3 && Zoom > 10.0 && State == GLUT_DOWN){
        Zoom *= 0.95;
        GLint ZoomID = glGetUniformLocation(ProgramReturn(), "zoom");
        glUniform1f(ZoomID, Zoom);
        glutPostRedisplay();
    }

    if (Button == 4 && Zoom < 500.0 && State == GLUT_DOWN){
        Zoom *= 1/0.95;
        GLint ZoomID = glGetUniformLocation(ProgramReturn(), "zoom");
        glUniform1f(ZoomID, Zoom);
        glutPostRedisplay();
    }
}
