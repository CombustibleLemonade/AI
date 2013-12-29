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

GLint Coord2d;

GLint WindowResXID;
GLint WindowResYID;

GLuint VertexBuffer;

void ProgramManager::Init() {
    Program = glCreateProgram();
}

void ProgramManager::ExtendVerts (float AddVerts[]){
    int i = 0;
    while (i <= sizeof(AddVerts)){
        Verts.push_back(AddVerts[i]);
        i++;
    }

    //glGenBuffers(1, &VertexBuffer);
    //glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    //glBufferData(GL_ARRAY_BUFFER, Verts.size(), Verts.data(), GL_STATIC_DRAW);
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

ProgramManager Test;

GLuint ProgramReturn () {
    return Test.Program;
}

int init () {
    // This bit is Super important!
    glewExperimental = GL_TRUE;
    glewInit();

    Test.Init();

    Test.AddShader(GL_VERTEX_SHADER, VertexShaderFunc);
    Test.AddShader(GL_FRAGMENT_SHADER, FragmentShaderFunc);

    float VertexBufferData[] = {
       -1.0f, -1.0f,
       1.0f, -1.0f,
       1.0f,  1.0f,
       -1.0f,  1.0f
    };
    Test.ExtendVerts(VertexBufferData);

    glLinkProgram (Test.Program);

    return 1;
}

void onDisplay () {
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    WindowResXID = glGetUniformLocation(ProgramReturn(), "xRes");
    WindowResYID = glGetUniformLocation(ProgramReturn(), "yRes");

    glUniform1i(WindowResXID, glutGet(GLUT_WINDOW_WIDTH));
    glUniform1i(WindowResYID, glutGet(GLUT_WINDOW_HEIGHT));

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, Test.VertexBuffer);
    glUseProgram(Test.Program);
    glVertexAttribPointer(
                0,
                2,
                GL_FLOAT,
                GL_FALSE,
                0,
                Test.Verts.data()    );
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableVertexAttribArray(0);
    glutSwapBuffers();
}
