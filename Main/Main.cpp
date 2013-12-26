#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

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

int main (int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(1600, 900);
    glutCreateWindow("My First Triangle");

    if (init()) {
        glutDisplayFunc(onDisplay);
        glutKeyboardFunc(Keyboard);
        glutMouseFunc(Mouse);
        glutMainLoop();
    }
    else {
        return 0;
    }
}
