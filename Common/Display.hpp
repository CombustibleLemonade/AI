#ifndef DISPLAY
#define DISPLAY

class ProgramManager {
    int CompileOk;
public:
    int QuadRenderingAmount;
    std::vector<float> Verts;
    void Init();
    GLuint VertexBuffer;
    GLint Program;
    void AddShader(GLenum ShaderType, std::string (*ShaderStringFunc)());
    void ExtendVerts (float AddVerts[]);
};

int init ();

void onDisplay ();

GLuint ProgramReturn ();

#endif
