#include <iostream>
#include <vector>

#ifdef __APPLE__
#include <GLEW/glew.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

#define ILUT_USE_OPENGL
#include <IL/il.h>
#include <IL/ilut.h>

#include "Display.hpp"
#include "Blocks.hpp"
#include "LoadText.hpp"

using namespace std;

ProgramManager* ThisProgram;

GLuint TextureID;
vector<Block*> AllBlocks;
vector<GLuint> Textures;

string VertexShader () {
    return FileToString("Display.vs");
}

string FragmentShader () {
    return FileToString("Display.fs");
}

Block::Block (float LocationArg[1], char* ImageFileName) {
    AllBlocks.push_back(this);

    this->Location[0] = LocationArg[0];
    this->Location[1] = LocationArg[1];
    ThisProgram = AddProgram();

    ThisProgram->Init();
    ThisProgram->AddShader(GL_VERTEX_SHADER, VertexShader);
    ThisProgram->AddShader(GL_FRAGMENT_SHADER, FragmentShader);
    ThisProgram->LinkProgram();


    Location[0] = LocationArg[0];
    Location[1] = LocationArg[1];

    float CubeContents[] = {
        -1.0f + Location[0], -1.0f + Location[1],
        1.0f + Location[0], -1.0f + Location[1],
        1.0f + Location[0],  1.0f + Location[1],
        -1.0f + Location[0],  1.0f + Location[1]
    };
    ThisProgram->ExtendVerts(CubeContents);

    float CubeUVs[] = {
        0.0f,  0.0f,
        1.0f,  0.0f,
        1.0f,  1.0f,
        0.0f,  1.0f
    };
    ThisProgram->ExtendUVs(CubeUVs);
    KnobReturn()->ExtendUVs(CubeUVs);
    ThisProgram->Texture = ilutGLLoadImage(ImageFileName);
}

void Block::AddNextBlock (Block* NextBlock) {
    float Location[2] = {1.0 + this->Location[0], 0.0 + this->Location[1]};
    BlockPointer Knob(Location, true);
}

void Block::AddPreviousBlock (Block* PreviousBlock) {
    float Location[2] = {-1.0 + this->Location[0], 0.0 + this->Location[1]};
    BlockPointer Knob(Location, false);
}

void CreateBlock(float Location[1], char* ImageFileName) {
    AllBlocks.push_back(new Block (Location, ImageFileName));
}

BlockPointer::BlockPointer(float LocationArg[1], bool Next) {
    Location[0] = LocationArg[0];
    Location[1] = LocationArg[1];
    FirstVertex = sizeof(KnobReturn()->Verts) + 1;
    IsNext = Next;
    if (Next) {
        float Knob[] = {
            -0.1f + Location[0], -0.1f + Location[1],
            0.1f + Location[0], -0.1f + Location[1],
            0.1f + Location[0],  0.1f + Location[1],
            -0.1f + Location[0],  0.1f + Location[1]
        };
        KnobReturn()->ExtendVerts(Knob);
    } else {
        float Knob[] = {
            0.1f + Location[0], -0.1f + Location[1],
            -0.1f + Location[0], -0.1f + Location[1],
            -0.1f + Location[0],  0.1f + Location[1],
            0.1f + Location[0],  0.1f + Location[1]
        };
        KnobReturn()->ExtendVerts(Knob);
    }
    int i = 0;
}

Block* BlockReturn (int i) {
    return AllBlocks[i];
}

GLuint ReturnTexture(int OffSet) {
    return Textures[OffSet];
}

Connector::Connector(BlockPointer* PreviousArg, BlockPointer* NextArg) {
}

void ConnectBlocks(Block* Previous, Block* Next){
    Previous->AddNextBlock(BlockReturn(1));
    Next->AddPreviousBlock(BlockReturn(0));

}
