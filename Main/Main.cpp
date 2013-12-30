#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

//#include <IL/devil_cpp_wrapper.hpp>

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
    glutInitWindowSize(1280, 720);
    glutCreateWindow("AI");
    if (init()) {
        glutDisplayFunc(onDisplay);
        glutKeyboardFunc(Keyboard);
        glutMouseFunc(Mouse);
        glutMotionFunc(Motion);
        glutMainLoop();
    }
    else {
        return 0;
    }
}
