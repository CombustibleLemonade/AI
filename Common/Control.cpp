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
float Zoom = 0.5;

void Keyboard (unsigned char key, int x, int y) {
    if (key == 27) {
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

void Mouse (int button, int state, int x, int y){
    if (button == 3 && Zoom > 0.02){
        Zoom *= 0.95;
        GLint ZoomID = glGetUniformLocation(ProgramReturn(), "zoom");
        glUniform1f(ZoomID, Zoom);
        cout << Zoom << endl;
        glutPostRedisplay();
    }

    if (button == 4 && Zoom < 0.5){
        Zoom *= 1/0.95;
        GLint ZoomID = glGetUniformLocation(ProgramReturn(), "zoom");
        glUniform1f(ZoomID, Zoom);
        cout << Zoom << endl;
        glutPostRedisplay();
    }
}
