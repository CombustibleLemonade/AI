#ifndef BLOCKS
#define BLOCKS

class Block {
public:
    Block(float LocationArg[1]);
    std::vector<Block*> Next;
    std::vector<Block*> Previous;
    float Location[1];
    std::vector<float> HaloCube;
    std::vector<float> Cube;
};

#endif
