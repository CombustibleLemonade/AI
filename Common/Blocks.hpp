#ifndef BLOCKS
#define BLOCKS

class ProgramManager;

class Block {
public:
    ProgramManager* ThisProgram;
    GLuint Texture;

    Block(float LocationArg[1], char* ImageFileName);
    std::vector<Block*> Next;
    void AddNextBlock(Block* NextBlock);
    std::vector<Block*> Previous;
    void AddPreviousBlock(Block* PreviousBlock);

    bool CheckCollision(float X, float Y);
    void ShowBlock(Block* BlockToShow);

    float Location[1];
    std::vector<float> HaloCube;
    std::vector<float> Cube;
    char* ImageName;
};

class Connector {
    int VertexVectorID;
    Connector(Block* PreviousArg, Block* NextArg, int VertID);
    Block* Previous;
    Block* Next;
};

void ConnectBlocks(Block* Previous, Block* Next);
void CreateBlock(float Location[1], char* ImageFileName);
void AddNextBlock ();
Block* CheckBlockCollision(float X, float Y);
Block* BlockReturn (int i);

GLuint ReturnTexture(int OffSet);
#endif
