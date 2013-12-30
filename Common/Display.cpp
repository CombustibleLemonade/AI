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
#include "Blocks.hpp"

using namespace std;

GLint Coord2d;

GLint WindowResXID;
GLint WindowResYID;

GLuint VertexBuffer;

vector<ProgramManager*> Programs;
int ProgramCount;

void ProgramManager::Init() {
    Program = glCreateProgram();
    Programs.push_back(this);
    ProgramCount++;
}

void ProgramManager::ExtendVerts (float AddVerts[]){
    int i = 0;
    while (i <= (sizeof(AddVerts)-1)){
        Verts.push_back(AddVerts[i]);
        i++;
    }
}

void ProgramManager::AddShader(GLenum ShaderType, string (*ShaderStringFunc)()){
    GLuint ShaderID = glCreateShader(ShaderType);
    string ShaderCodeString = (*ShaderStringFunc)();
    const char* ShaderCode = ShaderCodeString.c_str();
    glShaderSource(ShaderID, 1, &ShaderCode, NULL);
    glCompileShader(ShaderID);
    glAttachShader(Program, ShaderID);
    glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &CompileOk);
    if (!CompileOk) {
        cout << "Shader Error: " << ShaderType << endl;
        return;
    }
}

string VertexShaderFunc () {
    return FileToString("VertexShader.vs");
}

string FragmentShaderFunc () {
    return FileToString("FragmentShader.fs");
}

string FragmentShaderDisplayFunc () {
    return FileToString("FragmentShaderDisplay.fs");
}

ProgramManager Display;
ProgramManager Halo;

ProgramManager* ProgramReturn (int OffSet) {
    return Programs[OffSet];
}

int ProgramCountReturn () {
    return ProgramCount;
}

int init () {
    // This bit is Super important!
    glewExperimental = GL_TRUE;
    glewInit();

    Display.Init();
    Halo.Init();
    float Location[] = {0.0, 0.0};
    Block TestTwo(Location);

    Halo.AddShader(GL_VERTEX_SHADER, VertexShaderFunc);
    Halo.AddShader(GL_FRAGMENT_SHADER, FragmentShaderFunc);

    Display.AddShader(GL_VERTEX_SHADER, VertexShaderFunc);
    Display.AddShader(GL_FRAGMENT_SHADER, FragmentShaderDisplayFunc);

    glLinkProgram(Display.Program);
    glLinkProgram(Halo.Program);
    return 1;
}

void onDisplay () {
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    int i = 0;

    while (i < ProgramCount) {
        WindowResXID = glGetUniformLocation(ProgramReturn(i)->Program, "xRes");
        WindowResYID = glGetUniformLocation(ProgramReturn(i)->Program, "yRes");

        glUniform1i(WindowResXID, glutGet(GLUT_WINDOW_WIDTH));
        glUniform1i(WindowResYID, glutGet(GLUT_WINDOW_HEIGHT));

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, ProgramReturn(i)->VertexBuffer);
        glUseProgram(ProgramReturn(i)->Program);
        glVertexAttribPointer(
                    0,
                    2,
                    GL_FLOAT,
                    GL_FALSE,
                    0,
                    ProgramReturn(i)->Verts.data()    );
        glDrawArrays(GL_QUADS, 0, ProgramReturn(i)->Verts.size()/2);
        glDisableVertexAttribArray(0);
        i++;
    }
    glutSwapBuffers();
}
