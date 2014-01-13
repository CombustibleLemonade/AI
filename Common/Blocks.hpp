#ifndef BLOCKS
#define BLOCKS

class BlockPointer;

class Block {
public:
    GLuint Texture;
    Block(float LocationArg[1], char* ImageFileName);
    std::vector<BlockPointer*> Next;
    void AddNextBlock(Block* NextBlock);
    std::vector<BlockPointer*> Previous;
    void AddPreviousBlock(Block* PreviousBlock);

    float Location[1];
    std::vector<float> HaloCube;
    std::vector<float> Cube;
    char* ImageName;
};

class BlockPointer{
public:
    float FirstVertex;
    float Location[1];
    void Move(int YLocation);
    void Move(int YLocation, int XLoaction);
    bool IsNext;
    Block* NextBlock;
    BlockPointer(float LocationArg[1], bool Next);
};

class Connector {
    Connector(BlockPointer* PreviousArg, BlockPointer* NextArg);
    BlockPointer* Previous;
    BlockPointer* Next;
};

void ConnectBlocks(Block* Previous, Block* Next);
void CreateBlock(float Location[1], char* ImageFileName);
void AddNextBlock ();
Block* BlockReturn (int i);

GLuint ReturnTexture(int OffSet);
#endif
