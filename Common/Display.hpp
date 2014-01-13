#ifndef DISPLAY
#define DISPLAY

class ProgramManager {
    int CompileOk;
public:
    void Init();
    GLuint Texture;
    std::vector<float> UVs;
    std::vector<float> Verts;
    GLuint Attribute;
    GLuint UVAttribute;
    GLuint VertexBuffer;
    GLint Program;
    void AddShader(GLenum ShaderType, std::string (*ShaderStringFunc)());
    void AddShader(GLenum ShaderType, char* FileName);
    void ExtendVerts (float AddVerts[]);
    void ExtendUVs (float AddUVs[]);
    void LinkProgram();
    void DisplayFunc();
};

class KnobManager {
};

int init ();
void onDisplay ();
ProgramManager* AddProgram();
ProgramManager* ProgramReturn (int OffSet);
ProgramManager* KnobReturn();
int ProgramCountReturn ();

#endif
