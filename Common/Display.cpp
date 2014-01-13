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

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

#include "Display.hpp"
#include "LoadText.hpp"
#include "Blocks.hpp"

using namespace std;

GLint WindowResXID;
GLint WindowResYID;

GLuint VertexBuffer;


vector<ProgramManager*> Programs;
int ProgramCount;
ProgramManager Knob;
ProgramManager Curve;

void ProgramManager::Init() {
    Program = glCreateProgram();
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

void ProgramManager::AddShader(GLenum ShaderType, char* FileName) {
    GLuint ShaderID = glCreateShader(ShaderType);
    string ShaderCodeString = FileToString(FileName);
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

void ProgramManager::LinkProgram() {
    glLinkProgram(Program);
    GLint TempAttribute = glGetAttribLocation(Program, "coord2d");
    Attribute = TempAttribute;
    GLint UVTempAttribute = glGetAttribLocation(Program, "UVcoord");
    UVAttribute = UVTempAttribute;
}

ProgramManager* AddProgram() {
    Programs.push_back(new ProgramManager);
    ProgramCount++;
    return Programs.back();
}

ProgramManager* ProgramReturn (int OffSet) {
    return Programs[OffSet];
}

ProgramManager* KnobReturn () {
    return &Knob;
}


int ProgramCountReturn () {
    return ProgramCount;
}

void DisplayFunc (ProgramManager* ActiveProgram, int i) {
    glUseProgram(ActiveProgram->Program);

    glBindTexture(GL_TEXTURE_2D, ActiveProgram->Texture);
    GLuint TextureID = glGetUniformLocation(ActiveProgram->Program, "textureSampler");
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUniform1i(TextureID, 0);

    WindowResXID = glGetUniformLocation(ActiveProgram->Program, "xRes");
    WindowResYID = glGetUniformLocation(ActiveProgram->Program, "yRes");
    glUniform1i(WindowResXID, glutGet(GLUT_WINDOW_WIDTH));
    glUniform1i(WindowResYID, glutGet(GLUT_WINDOW_HEIGHT));

    glEnableVertexAttribArray(ActiveProgram->Attribute);
    glEnableVertexAttribArray(ActiveProgram->UVAttribute);

    glVertexAttribPointer(
                0,
                2,
                GL_FLOAT,
                GL_FALSE,
                0,
                ActiveProgram->Verts.data()    );

    glVertexAttribPointer(
                ActiveProgram->UVAttribute,
                2,
                GL_FLOAT,
                GL_FALSE,
                0,
                ActiveProgram->UVs.data()    );
    glDrawArrays(GL_QUADS, 0, ActiveProgram->Verts.size()/2);
    glDisableVertexAttribArray(ActiveProgram->Attribute);
    glDisableVertexAttribArray(ActiveProgram->UVAttribute);
}

int init () {
    // This bit is Super important!
    glewExperimental = GL_TRUE;
    glewInit();

    Curve.Init();
    Curve.Texture = ilutGLLoadImage("Curve.png");
    Curve.AddShader(GL_VERTEX_SHADER, "Display.vs");
    Curve.AddShader(GL_FRAGMENT_SHADER, "Display.fs");
    Curve.LinkProgram();
    float Test[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        1.0f,  1.0f,
        -1.0f,  1.0f
    };
    Curve.ExtendVerts(Test);
    Curve.ExtendUVs(Test);

    Knob.Init();
    Knob.Texture = ilutGLLoadImage("Knob.png");
    Knob.AddShader(GL_VERTEX_SHADER, "Display.vs");
    Knob.AddShader(GL_FRAGMENT_SHADER, "Display.fs");
    Knob.LinkProgram();

    float Location[] = {0.0, 0.0};

    CreateBlock(Location, "Plus.png");
    Location[0] += 3.0;
    CreateBlock(Location, "Minus.png");
    ConnectBlocks(BlockReturn(1), BlockReturn(2));

    glActiveTexture(GL_TEXTURE0);

    return 1;
}

void onDisplay () {
    glClearColor(0.2, 0.2, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    int i = 0;
    while (i < ProgramCount) {
        DisplayFunc(ProgramReturn(i), i);
        i++;
    }
    //glBindTexture(GL_TEXTURE_2D, Knob.Texture);
    DisplayFunc(&Knob, 0);
    //DisplayFunc(&Curve, 1);

    glutSwapBuffers();
}
