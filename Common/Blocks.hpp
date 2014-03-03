#ifndef BLOCKS
#define BLOCKS

class BackgroundElement {
};

class PageLayoutElement {
    BackgroundElement Background;
};

class Block {
    Block* Next;
    Block* Previous;
    Model2d* Square;
public:
    Block(char* TextureName);
    PageLayoutElement Page;
    bool BlockCollisionCheck();
};

#endif
