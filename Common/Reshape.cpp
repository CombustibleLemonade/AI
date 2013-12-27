#ifdef __APPLE__
#include <GLEW/glew.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

#include "Display.hpp"

GLint WindowResXID;
GLint WindowResYID;


void Reshape(int Width, int Height){
    WindowResXID = glGetUniformLocation(ProgramReturn(), "xRes");
    WindowResYID = glGetUniformLocation(ProgramReturn(), "yRes");

    glUniform1i(WindowResXID, Width);
    glUniform1i(WindowResYID, Height);
}
