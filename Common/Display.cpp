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
vector<GLuint> Attributes;
vector<GLuint> UvAttributes;

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

void ProgramManager::ExtendUVs (float AddUVs[]){
    int i = 0;
    while (i <= (sizeof(AddUVs)-1)){
        UVs.push_back(AddUVs[i]);
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

string HaloVertexShader () {
    return FileToString("VertexShader.vs");
}

string HaloFragmentShader () {
    return FileToString("FragmentShader.fs");
}

string DisplayVertexShader () {
    return FileToString("Display.vs");
}

string DisplayFragmentShader () {
    return FileToString("Display.fs");
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

    Halo.Init();
    Display.Init();

    float Location[] = {0.0, 0.0};
    CreateBlock(Location);
    Location[0] += 3.0;
    CreateBlock(Location);

    Halo.AddShader(GL_VERTEX_SHADER, HaloVertexShader);
    Halo.AddShader(GL_FRAGMENT_SHADER, HaloFragmentShader);

    Display.AddShader(GL_VERTEX_SHADER, DisplayVertexShader);
    Display.AddShader(GL_FRAGMENT_SHADER, DisplayFragmentShader);

    glLinkProgram(Halo.Program);
    glLinkProgram(Display.Program);
    int i = 0;
    while (i < ProgramCountReturn()) {
        GLint TempAttribute = glGetAttribLocation(ProgramReturn(i)->Program, "coord2d");
        Attributes.push_back(TempAttribute);
        GLint SecondTempAttribute = glGetAttribLocation(ProgramReturn(1)->Program, "UVcoord");
        UvAttributes.push_back(SecondTempAttribute);
        i++;
    }
    return 1;
}

void onDisplay () {
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    int i = 0;
    while (i < ProgramCount) {
        glUseProgram(ProgramReturn(i)->Program);

        WindowResXID = glGetUniformLocation(ProgramReturn(i)->Program, "xRes");
        WindowResYID = glGetUniformLocation(ProgramReturn(i)->Program, "yRes");

        glUniform1i(WindowResXID, glutGet(GLUT_WINDOW_WIDTH));
        glUniform1i(WindowResYID, glutGet(GLUT_WINDOW_HEIGHT));

        glEnableVertexAttribArray(Attributes[i]);
        glEnableVertexAttribArray(UvAttributes[i]);

        glVertexAttribPointer(
                    0,
                    2,
                    GL_FLOAT,
                    GL_FALSE,
                    0,
                    ProgramReturn(i)->Verts.data()    );

        glVertexAttribPointer(
                    UvAttributes[i],
                    2,
                    GL_FLOAT,
                    GL_FALSE,
                    0,
                    ProgramReturn(1)->UVs.data()    );
        glDrawArrays(GL_QUADS, 0, ProgramReturn(i)->Verts.size()/2);
        glDisableVertexAttribArray(Attributes[i]);
        glDisableVertexAttribArray(UvAttributes[i]);

        i++;
    }



    glutSwapBuffers();
}
