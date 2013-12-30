#ifndef DISPLAY
#define DISPLAY

class ProgramManager {
    int CompileOk;
public:
    void Init();
    std::vector<float> UVs;
    std::vector<float> Verts;
    GLuint VertexBuffer;
    GLint Program;
    void AddShader(GLenum ShaderType, std::string (*ShaderStringFunc)());
    void ExtendVerts (float AddVerts[]);
    void ExtendUVs (float AddUVs[]);
};

int init ();

void onDisplay ();

ProgramManager* ProgramReturn (int OffSet);

int ProgramCountReturn ();

#endif
