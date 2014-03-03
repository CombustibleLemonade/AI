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
    void OnColision();
public:
    Block(char* TextureName);
    PageLayoutElement Page;

    void Translate(Vector2 Offset);
    void BlockCollisionCheck(Vector2 Location);
};

void CollisionCheck (Vector2 Location);

#endif
