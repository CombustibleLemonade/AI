#ifdef __APPLE__
#include <GLEW/glew.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

#include <GLFW/glfw3.h>

#define ILUT_USE_OPENGL
#include <IL/il.h>
#include <IL/ilut.h>
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "LoadText.hpp"
#include "Display.hpp"
#include "Blocks.hpp"


using namespace std;

bool ExitMainLoopBool = false;
int WindowWidth = 1920, WindowHeight = 1080;

vector< vector<Model2d*> > Layers;
vector<Camera2d*> Cameras;

Camera2d* DefaultCamera2d;
GLFWwindow* Window;

Attribute::Attribute() {
    AttribIndex = 0;
}

Uniform1f::Uniform1f () {
}

Uniform1f::Uniform1f (GLuint UniformLocation) {
    UniformIndex = UniformLocation;
}

void Uniform1f::UniformFunc() {
    glUniform1f(UniformIndex, Value);
}

Uniform1i::Uniform1i () {
}

Uniform1i::Uniform1i (GLuint UniformLocation) {
    UniformIndex = UniformLocation;
}

Vector2::Vector2() {
    x = 0.0;
    y = 0.0;
    //Vector2 operator + (const Vector2);
};

Vector2::Vector2(float xArg, float yArg) : x(xArg), y(yArg) {}

Vector2 Vector2::operator + (const Vector2& Param) {
    Vector2 Temp;
    Temp.x = x + Param.x;
    Temp.y = y + Param.y;
    return Temp;
}

void Vector2::operator +=(const Vector2& Param) {
    Vector2 Temp;
    x += Param.x;
    y += Param.y;
    return;
}

Texture::Texture(char *FileName, const char *VariableName) {
    TextureIterator = ilutGLLoadImage(FileName);
}

void Texture::DisplayFunc () {
}

Camera2d::Camera2d () {
    Cameras.push_back(this);
    x = 0;
    y = 0;
    Zoom = 200;
}

Model2d::Model2d (int Layer) {
    VertexAttribute = new Attribute;
    UVAttribute = new Attribute;
    Camera = DefaultCamera2d;

    while (Layer >= Layers.size()) {
        vector<Model2d*> NewLayer;
        Layers.push_back(NewLayer);
    }

    Layers[0].push_back(this);
    Program = glCreateProgram();
    DisplayMode = GL_TRIANGLES;
    Rotation = 0;
    Scale.x = 1;
    Scale.y = 1;
}

Model2d::Model2d(GLenum RelativeSpace) {
    VertexAttribute = new Attribute;
    Program = glCreateProgram();
    SpaceType = RelativeSpace;
}

void Model2d::Translate(float x, float y) {
    Location.x += x;
    Location.y += y;
}

void Model2d::Translate(Vector2 Vector) {
    Location += Vector;
    cout << Location.x;
}

void Model2d::Rotate(float r) {
    Rotation += r;
}

void Model2d::SetVertices(vector<float> Vertices) {
    VertexAttribute->Contents = Vertices;
}


void Model2d::SetVertices(float* Begin, float* End) {
    vector<float> AttribVectorReference;
    while (Begin < End) {
        VertexAttribute->Contents.push_back(*Begin);
        Begin++;
    }
}

void Model2d::SetUVs(vector<float> Normals) {
    UVAttribute->Contents = Normals;
}

void Model2d::SetUVs(float* Begin, float* End) {
    vector<float> AttribVectorReference;
    while (Begin < End) {
        UVAttribute->Contents.push_back(*Begin);
        Begin++;
    }
}

void Model2d::AddShader(GLenum ShaderType, char *FileName) {
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

void Model2d::ChangeTexture (char *FileName) {
    Texture = ilutGLLoadImage(FileName);
}

void Model2d::LinkProgram() {
    glLinkProgram(Program);
    VertexAttribute->AttribIndex = glGetAttribLocation(Program, "coord2d");
    UVAttribute->AttribIndex = glGetAttribLocation(Program, "UVcoord");

    LocationUniform.UniformIndex = glGetUniformLocation(Program, "Position");
    RotationUniform.UniformIndex = glGetUniformLocation(Program, "Rotation");
    ScaleUniform.UniformIndex = glGetUniformLocation(Program, "Scale");
    ZoomUniform.UniformIndex = glGetUniformLocation(Program, "Zoom");
    XResUniform.UniformIndex = glGetUniformLocation(Program, "xRes");
    YResUniform.UniformIndex = glGetUniformLocation(Program, "yRes");
}

void Model2d::DisplayFunc() {
    glUseProgram(Program);

    glBindTexture(GL_TEXTURE_2D, Texture);
    GLuint TextureID = glGetUniformLocation(Program, "textureSampler");
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUniform1i(TextureID, 0);

    glUniform2f(LocationUniform.UniformIndex, Location.x + Camera->x, Location.y + Camera->y);
    glUniform1f(RotationUniform.UniformIndex, Rotation);
    glUniform2f(ScaleUniform.UniformIndex, Scale.x, Scale.y);
    glUniform1f(ZoomUniform.UniformIndex, Camera->Zoom);

    glUniform1i(XResUniform.UniformIndex, WindowWidth);
    glUniform1i(YResUniform.UniformIndex, WindowHeight);

    glEnableVertexAttribArray(VertexAttribute->AttribIndex);
    glVertexAttribPointer(
                VertexAttribute->AttribIndex,
                2,
                GL_FLOAT,
                GL_FALSE,
                0,
                VertexAttribute->Contents.data() );

    glEnableVertexAttribArray(UVAttribute->AttribIndex);
    glVertexAttribPointer(
                UVAttribute->AttribIndex,
                2,
                GL_FLOAT,
                GL_FALSE,
                0,
                UVAttribute->Contents.data() );

    glDrawArrays(DisplayMode, 0, VertexAttribute->Contents.size()/2);
    glDisableVertexAttribArray(VertexAttribute->AttribIndex);
    glDisableVertexAttribArray(UVAttribute->AttribIndex);
}


void DisplayFunc() __attribute__((weak));
void IdleFunc() __attribute__((weak));
void InitFunc() __attribute__((weak));
//void KeyboardFunc(unsigned char Key, int x, int y) __attribute__((weak));
void MouseFunc(int Button, int Action, int Mods) __attribute__((weak));
void ScrollFunc(double XOffset, double YOffset) __attribute__((weak));
void MotionFunc(int x, int y) __attribute__((weak));

void DisplayFuncRedirect() {
    glClearColor(0.2, 0.3, 0.6, 0.0);

    glClear(GL_COLOR_BUFFER_BIT);

    int i = 0;
    int j = 0;
    while (i < Layers.size()) {
        while (j < Layers[i].size()) {
            Layers[i][j]->DisplayFunc();
            j++;
        }
        i++;
    }

    i = 0;
    if (DisplayFunc) {
        DisplayFunc();
    }
}

void IdleFuncRedirect() {
    if (IdleFunc) {
        IdleFunc();
    }
    glutPostRedisplay();
}

void InitFuncRedirect() {
    DefaultCamera2d = new Camera2d;
    if (InitFunc) {
        InitFunc();
    }
}

/*void KeyboardFuncRedirect(unsigned char Key, int x, int y) {
    if (KeyboardFunc) {
        KeyboardFunc(Key, x, y);
    }
}*/

void MouseFuncRedirect(GLFWwindow* Window, int Button, int Action, int Mods){
    if (MouseFunc) {
        MouseFunc(Button, Action, Mods);
    }
}

void ScrollFuncRedirect(GLFWwindow* Window, double XOffset, double YOffset) {
    if (ScrollFunc) {
        ScrollFunc(XOffset, YOffset);
    }
}

void MotionFuncRedirect(GLFWwindow* Window, double x, double y) {
    if (MotionFunc) {
        MotionFunc(x, y);
    }
}

Model2d* AddModel2d (int Layer) {
    Model2d* ReturnModel = new Model2d(Layer);
    return ReturnModel;
}

Model2d* ReturnModel2d(int Layer, int Index) {
    return Layers[Layer][Index];
}

Camera2d* ReturnCamera2d (int Index) {
    return Cameras[Index];
}

Camera2d* ReturnDefaultCamera2d () {
    return DefaultCamera2d;
}

GLFWwindow* ReturnWindow() {
    return Window;
}

void ExitMainLoop() {
    ExitMainLoopBool = true;
}

int main (int argc, char* argv[]) {
    // This bit is Super important!

    glutInit(&argc, argv);
    glfwInit();

    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    WindowWidth = mode->width;
    WindowHeight = mode->height;
    Window = glfwCreateWindow(WindowWidth, WindowHeight, "test", NULL, NULL);
    glfwMakeContextCurrent(Window);

    ilInit();
    ilutInit();
    ilutRenderer(ILUT_OPENGL_CONV);

    glewExperimental = GL_TRUE;
    glewInit();

    glfwSetMouseButtonCallback(Window, MouseFuncRedirect);
    glfwSetScrollCallback(Window, ScrollFuncRedirect);
    glfwSetCursorPosCallback(Window, MotionFuncRedirect);

    InitFuncRedirect();
    while (!glfwWindowShouldClose(Window) && !ExitMainLoopBool) {
        glLoadIdentity();
        glfwGetWindowSize(Window, &WindowWidth, &WindowHeight);
        DisplayFuncRedirect();

        glfwSwapBuffers(Window);
        glfwPollEvents();
    }
    glfwDestroyWindow(Window);
    glfwTerminate();
    return 1;
}
