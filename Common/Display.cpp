#ifdef __APPLE__
#include <GLEW/glew.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

#include "Display.hpp"
#include "LoadText.hpp"

using namespace std;

GLuint VertexBuffer;
GLuint Program;

GLint CompileOk;
GLint CompilevsOk;

GLuint VertexShaderID;
GLuint FragmentShaderID;

GLint Coord2d;

const char* fsCode;
const char* vsCode;

int InfoLogLength;

GLuint ProgramReturn () {
    return Program;
}

int init () {

    // This bit is Super important!
    glewExperimental = GL_TRUE;
    glewInit();

    static const GLfloat VertexBufferData[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        1.0f,  1.0f,
        -1.0f, 1.0f
    };

    glGenBuffers(1, &VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferData), VertexBufferData, GL_STATIC_DRAW);



    FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    string fsCodeString = FileToString("FragmentShader.fs");
    fsCode = fsCodeString.c_str();
    glShaderSource(FragmentShaderID, 1, &fsCode, NULL);

    glCompileShader(FragmentShaderID);

    VertexShaderID = glCreateShader(GL_VERTEX_SHADER);

    string vsCodeString = FileToString("VertexShader.vs");
    vsCode = vsCodeString.c_str();

    glShaderSource(VertexShaderID, 1, &vsCode, NULL);
    glCompileShader(VertexShaderID);
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &CompilevsOk);
    if (!CompilevsOk) {
        fprintf(stderr, "Error in vertex shader\n");
        return 0;
    }
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &CompileOk);
    if (!CompileOk) {
        fprintf(stderr, "Error in fragment shader\n");
        return 0;
    }


    Program = glCreateProgram();
    glAttachShader (Program, VertexShaderID);
    glAttachShader (Program, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    glLinkProgram (Program);


    const char* attribute_name = "coord2d";
    Coord2d = glGetAttribLocation(Program, attribute_name);



    return 1;
}

void onDisplay () {
    glClearColor(0.1, 0.1, 0.1, 0.1);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glUseProgram(Program);
    glVertexAttribPointer(
                0,
                2,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void*)0    );
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableVertexAttribArray(0);
    glutSwapBuffers();
}
