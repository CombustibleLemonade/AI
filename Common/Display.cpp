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
vector<GLuint> Attributes;
vector<GLuint> UvAttributes;

vector<ProgramManager*> Programs;
int ProgramCount;
ProgramManager Knob;

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

ProgramManager* AddProgram() {
    Programs.push_back(new ProgramManager);
    ProgramCount++;
    return Programs.back();
}

ProgramManager* ProgramReturn (int OffSet) {
    return Programs[OffSet];
}

ProgramManager* KnobReturn (int OffSet) {
    return &Knob;
}

int ProgramCountReturn () {
    return ProgramCount;
}

int init () {
    // This bit is Super important!
    glewExperimental = GL_TRUE;
    glewInit();


    Knob.Texture = ilutGLLoadImage("Knob.png");
    float Location[] = {0.0, 0.0};

    glAlphaFunc(GL_GREATER, 0.1);
    glEnable(GL_ALPHA_TEST);
    int j = 0;
    int k = 0;

    CreateBlock(Location, "Plus.png");
    Location[0] += 3.0;
    CreateBlock(Location, "Minus.png");


    glActiveTexture(GL_TEXTURE0);

    int i = 0;
    while (i < ProgramCountReturn()) {
        GLint TempAttribute = glGetAttribLocation(ProgramReturn(i)->Program, "coord2d");
        Attributes.push_back(TempAttribute);
        GLint SecondTempAttribute = glGetAttribLocation(ProgramReturn(i)->Program, "UVcoord");
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

        glBindTexture(GL_TEXTURE_2D, ProgramReturn(i)->Texture);

        GLuint TextureID = glGetUniformLocation(ProgramReturn(i)->Program, "textureSampler");
        glUniform1i(TextureID, 0);

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
                    ProgramReturn(i)->UVs.data()    );
        glDrawArrays(GL_QUADS, 0, ProgramReturn(i)->Verts.size()/2);
        glDisableVertexAttribArray(Attributes[i]);
        glDisableVertexAttribArray(UvAttributes[i]);

        i++;
    }


    glutSwapBuffers();
}
