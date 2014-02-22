#ifndef BLOCKS
#define BLOCKS

class Block {
    Block* Next;
    Block* Previous;
    Model2d* Square;
public:
    Block(char* TextureName);
};

#endif
