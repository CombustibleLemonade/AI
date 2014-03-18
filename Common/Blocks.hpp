#ifndef BLOCKS
#define BLOCKS
#include <vector>

class BackgroundElement {
};

class TextElement {
};

class PageLayoutElement {
    BackgroundElement Background;
    std::vector<int> TextElements;
    TextElement Text;
};

class SquareLayoutElement {
    Vector2 Location;
    Model2d* Square;
public:
    void CollisionCheck();
};

class Block {
    std::vector<int> TestVector;
    Block* Next;
    Block* Previous;
    Model2d* Square;
    void OnColision();
public:
    Vector2 Test;

    Block(char* TextureName);
    PageLayoutElement Page;

    void Translate(Vector2 Offset);
    void BlockCollisionCheck(/*Vector2 CollisionLocation*/);
};

void CollisionCheck (Vector2 CursorLocation);

#endif
