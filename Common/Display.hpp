#ifndef DISPLAY
#define DISPLAY

class ProgramManager {
    int CompileOk;
public:
    std::vector<float> Verts;
    void Init();
    GLuint VertexBuffer;
    GLint Program;
    void AddShader(GLenum ShaderType, std::string (*ShaderStringFunc)());
    void ExtendVerts (float AddVerts[]);
};

int init ();

void onDisplay ();

ProgramManager* ProgramReturn (int OffSet);

int ProgramCountReturn ();

#endif
