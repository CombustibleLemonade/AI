#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#ifdef __APPLE__
#include <GLEW/glew.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

#define ILUT_USE_OPENGL
#include <IL/il.h>
#include <IL/ilut.h>

#include "Display.hpp"
#include "Control.hpp"

using namespace std;

int main (int argc, char* argv[]) {
    glutInit(&argc, argv);
    glewInit();
    ilInit();
    ilutInit();
    ilutRenderer(ILUT_OPENGL_CONV);

    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("AI");
    if (init()) {
        glutDisplayFunc(onDisplay);
        glutKeyboardFunc(Keyboard);
        glutMouseFunc(Mouse);
        glutMotionFunc(Motion);
        glutPassiveMotionFunc(PassiveMotion);
        glutIdleFunc(Idle);
        glutFullScreen();
        glutMainLoop();
    }
    else {
        return 0;
    }
}
