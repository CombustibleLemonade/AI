#ifndef DISPLAY
#define DISPLAY

class ProgramManager {
    int CompileOk;
    float FullscreenScaler;
public:
    float TargetFullscreen;
    void Init();
    GLuint Texture;
    std::vector<float> UVs;
    std::vector<float> Verts;
    GLuint Attribute;
    GLuint UVAttribute;
    GLuint FullscreenAttribute;
    GLuint VertexBuffer;
    GLint Program;
    void AddShader(GLenum ShaderType, std::string (*ShaderStringFunc)());
    void AddShader(GLenum ShaderType, char* FileName);
    void ExtendVerts (float AddVerts[]);
    void ExtendUVs (float AddUVs[]);
    void LinkProgram();
    void DisplayFunc();
};

int init ();
void onDisplay ();
void Idle();
ProgramManager* AddProgram();
ProgramManager* AddProgram(int Layer);
ProgramManager* ProgramReturn (int OffSet);
ProgramManager* KnobReturn();
int ProgramCountReturn ();

void SetCameraPosition(float X, float Y);
void SetCameraZoom(float ZoomValue);

#endif
