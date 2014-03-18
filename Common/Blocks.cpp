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
vector<Block*> AllBlocks;

void Block::OnColision() {
    cout << "win: ";
}

void Block::Translate(Vector2 Offset) {
    Square->Translate(Offset);
}

void Block::BlockCollisionCheck(/*Vector2 CollisionLocation*/) {
    bool DoesCollide;
    //DoesCollide = Location.x<CollisionLocation.x;
    cout << Test.x << endl;
    if (DoesCollide) {
        OnColision();
    }
}

Block::Block(char *TextureName) {
    AllBlocks.push_back(this);
    //create block 2d model
    Square = AddModel2d(0);

    float Vertices[] = {
        1.0, 1.0,
        1.0, -1.0,
        -1.0, -1.0,
        -1.0, 1.0,
    };
    float UVs[] = {
        1.0, 1.0,
        1.0, 0.0,
        0.0, 0.0,
        0.0, 1.0,
    };

    Square->SetVertices(&Vertices[0], &Vertices[8]);
    Square->SetUVs(&UVs[0], &UVs[8]);
    Square->AddShader(GL_VERTEX_SHADER, "Display.vs");
    Square->AddShader(GL_FRAGMENT_SHADER, "Display.fs");
    Square->ChangeTexture(TextureName);
    Square->LinkProgram();
    Square->DisplayMode = GL_QUADS;
}

void CollisionCheck (Vector2 CursorLocation) {
    int i = 0;
    int BlockCount = AllBlocks.size();
    while (i<BlockCount) {
        AllBlocks[i]->BlockCollisionCheck();
        i++;
    }
}
