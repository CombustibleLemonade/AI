#ifndef BLOCKS
#define BLOCKS
//#include <vector>

class SquareLayoutElement{
public:
    Model2d* Square;
    SquareLayoutElement(char* Texture);
    void CollisionCheck(Vector2 Location);
};

class Block {
    std::vector<Block*> Previous;
    std::vector<Block*> Next;
public:
    SquareLayoutElement* Square;
    Block(char* Texture);

    void CollisionCheck(Vector2 Location);

    void AddDependency(Block* PreviousBlock);
};

void CollisionCheck(Vector2 Location);

Block* ReturnFirstBlock ();

#endif
