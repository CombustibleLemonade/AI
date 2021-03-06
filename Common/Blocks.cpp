#include <iostream>
#include <vector>

#ifdef __APPLE__
#include <GLEW/glew.h>
#else
#include <GL/glew.h>
#endif

#define ILUT_USE_OPENGL
#include <IL/il.h>
#include <IL/ilut.h>

#include "LoadText.hpp"
#include "Display.hpp"
#include "Blocks.hpp"

using namespace std;

std::vector<Block*> AllBlocks;

SquareLayoutElement::SquareLayoutElement(char* Texture){
    Square = AddModel2d(0);
    Square->AddShader(GL_VERTEX_SHADER, "Display.vs");
    Square->AddShader(GL_FRAGMENT_SHADER, "Display.fs");
    float Vertices[] = {
        1.0, 1.0,
        1.0, -1.0,
        -1.0, -1.0,
        -1.0, 1.0
    };
    float UVs[] = {
        1.0, 1.0,
        1.0, 0.0,
        0.0, 0.0,
        0.0, 1.0,
    };
    Square->SetVertices(&Vertices[0], &Vertices[8]);
    Square->SetUVs(&UVs[0], &UVs[8]);
    Square->ChangeTexture(Texture);
    Square->DisplayMode = GL_QUADS;
    Square->LinkProgram();
}

bool SquareLayoutElement::CollisionCheck(Vector2 Location){
    if (Location.x<(Square->Location.x+1.0) && Location.x>(Square->Location.x-1.0) && Location.y<(Square->Location.y+1.0) && Location.y>(Square->Location.y-1.0)) {
        cout << "collide: ";
        return true;
    }
}

Block::Block(char* Texture) {
    AllBlocks.push_back(this);
    Square = new SquareLayoutElement(Texture);
}

void Block::CollisionCheck(Vector2 Location) {
    Square->CollisionCheck(Location);
}

void CollisionCheck(Vector2 Location) {
    int i = 0;
    int SizeOfAllBlocks = AllBlocks.size();
    while (i < SizeOfAllBlocks) {
        AllBlocks[i]->CollisionCheck(Location);
        i++;
    }
}

Block* ReturnFirstBlock () {
    return AllBlocks[0];
}
