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
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

#include "LoadText.hpp"
#include "Blocks.hpp"
#include "Display.hpp"

using namespace std;

GLint WindowResXID;
GLint WindowResYID;

GLuint VertexBuffer;

float CameraPosition[2] = {0.0, 0.0};
float ZoomValue = 200;
int PreviousTime = 0;
float FrameTime;

vector< vector<ProgramManager*> > Layers;
vector<ProgramManager*> Programs;
int ProgramCount;

float FullScreenVerts[] = {
    -1.0f, -1.0f,
    1.0f, -1.0f,
    1.0f,  1.0f,
    -1.0f,  1.0f
};

ProgramManager* Knob;
ProgramManager* Curve;

void ProgramManager::Init() {
    Program = glCreateProgram();
    TargetFullscreen = 0.0;
    FullscreenScaler = 0.0;
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
    TempAttribute = glGetAttribLocation(Program, "UVcoord");
    UVAttribute = TempAttribute;
    TempAttribute = glGetAttribLocation(Program, "Fullscreencoord");
    FullscreenAttribute = TempAttribute;
}

void ProgramManager::DisplayFunc() {
    glUseProgram(Program);

    FullscreenScaler = TargetFullscreen - (TargetFullscreen - FullscreenScaler)*pow(0.02, FrameTime);

    GLint FullscreenID = glGetUniformLocation(Program, "FullscreenBlend");
    glUniform1f(FullscreenID, FullscreenScaler);

    GLint ZoomID = glGetUniformLocation(Program, "zoom");
    glUniform1f(ZoomID, ZoomValue);

    GLint LocationID = glGetUniformLocation(Program, "Position");
    glUniform2f(LocationID, CameraPosition[0], CameraPosition[1]);

    glBindTexture(GL_TEXTURE_2D, Texture);
    GLuint TextureID = glGetUniformLocation(Program, "textureSampler");
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUniform1i(TextureID, 0);

    WindowResXID = glGetUniformLocation(Program, "xRes");
    WindowResYID = glGetUniformLocation(Program, "yRes");
    glUniform1i(WindowResXID, glutGet(GLUT_WINDOW_WIDTH));
    glUniform1i(WindowResYID, glutGet(GLUT_WINDOW_HEIGHT));

    glEnableVertexAttribArray(Attribute);
    glEnableVertexAttribArray(UVAttribute);

    glVertexAttribPointer(
                Attribute,
                2,
                GL_FLOAT,
                GL_FALSE,
                0,
                Verts.data()    );

    glVertexAttribPointer(
                UVAttribute,
                2,
                GL_FLOAT,
                GL_FALSE,
                0,
                UVs.data()    );
    if (false) {
        glVertexAttribPointer(
                    FullscreenAttribute,
                    2,
                    GL_FLOAT,
                    GL_FALSE,
                    0,
                    UVs.data()    );
    }
    glDrawArrays(GL_QUADS, 0, Verts.size()/2);
    glDisableVertexAttribArray(Attribute);
    glDisableVertexAttribArray(UVAttribute);
}

ProgramManager* AddProgram() {
    Programs.push_back(new ProgramManager);
    ProgramCount++;
    return Programs.back();
}

ProgramManager* AddProgram(int Layer) {
    while (Layers.size() <= Layer) {
        vector<ProgramManager*> NewLayer;
        Layers.push_back(NewLayer);
    }
    Layers[Layer].push_back(new ProgramManager);
    return Layers[Layer].back();
}

ProgramManager* ProgramReturn (int OffSet) {
    return Programs[OffSet];
}

void SetCameraPosition(float X, float Y) {
    CameraPosition[0] = X;
    CameraPosition[1] = Y;
}

void SetCameraZoom(float ZoomArg){
    ZoomValue = ZoomArg;
}

int ProgramCountReturn () {
    return ProgramCount;
}

int init () {
    // This bit is Super important!
    cout << pow(2, 5) << endl;
    glewExperimental = GL_TRUE;
    glewInit();

    Curve = AddProgram(0);
    Curve->Init();
    Curve->Texture = ilutGLLoadImage("Curve.png");
    Curve->AddShader(GL_VERTEX_SHADER, "Display.vs");
    Curve->AddShader(GL_FRAGMENT_SHADER, "Display.fs");
    Curve->LinkProgram();
    float Test[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        1.0f,  1.0f,
        -1.0f,  1.0f
    };
    //Curve->ExtendVerts(Test);
    //Curve->ExtendUVs(Test);

    float Location[] = {0.0, 0.0};

    CreateBlock(Location, "Plus.png");
    Location[0] += 3.0;
    CreateBlock(Location, "Minus.png");
    ConnectBlocks(BlockReturn(1), BlockReturn(2));

    glActiveTexture(GL_TEXTURE0);

    return 1;
}

void Idle() {
    FrameTime = (glutGet(GLUT_ELAPSED_TIME)-PreviousTime)*0.001;
    cout << PreviousTime << " " << glutGet(GLUT_ELAPSED_TIME) << " " << FrameTime*1000 <<  endl;
    PreviousTime =  glutGet(GLUT_ELAPSED_TIME);
    glutPostRedisplay();
}

void onDisplay () {
    glClearColor(0.2, 0.2, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    int i = 0;
    while (i<10000)
        i++;
    i = 0;
    int LayerCount = Layers.size();
    while (i < LayerCount) {
        int j = 0;
        int ProgramCount = Layers[i].size();
        while (j < ProgramCount) {
            Layers[i][j]->DisplayFunc();
            j++;
        }
        i++;
    }
    glutSwapBuffers();
}
