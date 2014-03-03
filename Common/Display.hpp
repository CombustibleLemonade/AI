#ifndef DISPLAY
#define DISPLAY
#define CAMERA_SPACE 0
#define SCREEN_CENTRE_SPACE 1
#define SCREEN_TOP_LEFT_SPACE 2
#define SCREEN_TOP_RIGHT_SPACE 3
#define SCREEN_BOTTOM_LEFT_SPACE 4
#define SCREEN_BOTTOM_RIGHT_SPACE 5

#include <vector>
#include <GLFW/glfw3.h>

void InitFunc();

class Attribute {
public:
    Attribute();
    std::vector<float> Contents;
    GLuint AttribIndex;
};

class Uniform1f {
public:
    float Value;
    Uniform1f();
    Uniform1f(GLuint Program);
    Uniform1f(const char* AttribName, GLuint Program);
    GLuint UniformIndex;
    void UniformFunc();
};

class Uniform1i {
public:
    int Value;
    Uniform1i();
    Uniform1i(GLuint Program);
    Uniform1i(const char* AttribName, GLuint Program);
    GLuint UniformIndex;
};

class Vector2 {
public:
    float x, y;
    Vector2();
    Vector2(float xArg, float yArg);
    Vector2 operator + (const Vector2& Param);
};

class Texture {
    void TextureRedisplayFunc();
    Uniform1f TextureID;
    GLuint TextureIterator;
public:
    void DisplayFunc();
    Texture(char* FileName, const char* VariableName);
};

class Camera2d {
public:
    Camera2d();
    void DisplayFunc();
    float x;
    float y;
    float Zoom;
};

class Material {
    Attribute* VertexAttribute;
    void DisplayFunc();
};

class Model2d {
    int CompileOk;
    std::vector<Attribute*> Attributes;
    std::vector<Uniform1f*> Uniforms;

    Attribute* VertexAttribute;
    Attribute* UVAttribute;

    Uniform1f LocationUniform;
    Uniform1f RotationUniform;
    Uniform1f ScaleUniform;

    Uniform1f ZoomUniform;
    Uniform1i XResUniform;
    Uniform1i YResUniform;

    GLuint Texture;
    GLuint Program;
    GLenum SpaceType;
public:
    GLenum DisplayMode;
    Camera2d* Camera;

    Model2d(int Layer);
    Model2d(GLenum RelativeSpace);
    void SetRelativeSpace(GLenum RelativeSpace);

    void SetUVs (std::vector<float> Normals);
    void SetUVs (float* Begin, float* end);

    void SetVertices (std::vector<float> Vertices);
    void SetVertices(float* Begin, float* End);

    Vector2 Location;
    float Rotation;
    Vector2 Scale;

    void Translate(float x, float y);
    void Translate(Vector2 Vector);
    void Rotate(float r);
    void Resize(int x, int y);
    void Resize(Vector2 Vector);

    void AddShader(GLenum ShaderType, char* FileName);
    void AddAttribute(const char* AttributeName);
    void AddUniform(const char* UniformName);

    void ChangeTexture (char* FileName);

    void LinkProgram();

    void DisplayFunc();
};

Model2d* AddModel2d (int Layer);
Model2d* ReturnModel2d(int Layer, int Index);
Camera2d* ReturnCamera2d(int Index);
Camera2d* ReturnDefaultCamera2d();
GLFWwindow* ReturnWindow();
void ExitMainLoop();
#endif
