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
    ThisProgram = AddProgram(1);

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
    ThisProgram->Texture = ilutGLLoadImage(ImageFileName);
}

void Block::AddNextBlock (Block* NextBlock) {
    float Location[2] = {1.0 + this->Location[0], 0.0 + this->Location[1]};
}

void Block::AddPreviousBlock (Block* PreviousBlock) {
    float Location[2] = {-1.0 + this->Location[0], 0.0 + this->Location[1]};
}

bool Block::CheckCollision (float X, float Y) {
    if (X<(Location[0]+1.0) && X>(Location[0]-1.0) && Y<(Location[1]+1.0) && Y>(Location[1]-1.0)){
        return true;
    }
    return false;
}

void CreateBlock(float Location[1], char* ImageFileName) {
    AllBlocks.push_back(new Block (Location, ImageFileName));
}

Block* BlockReturn (int i) {
    return AllBlocks[i];
}

GLuint ReturnTexture(int OffSet) {
    return Textures[OffSet];
}

Connector::Connector(Block* PreviousArg, Block* NextArg, int VertID) {
    PreviousArg->AddNextBlock(NextArg);
    NextArg->AddPreviousBlock(PreviousArg);
    Previous = PreviousArg;
    Next = NextArg;
    VertexVectorID = VertID;
}

void ConnectBlocks(Block* Previous, Block* Next){
    Previous->AddNextBlock(BlockReturn(1));
    Next->AddPreviousBlock(BlockReturn(0));
}

Block* CheckBlockCollision(float X, float Y){
    int AmountOfBlocks = AllBlocks.size();
    int i = 0;
    while (i < AmountOfBlocks) {
        if(AllBlocks[i]->CheckCollision(X, Y))
            //AllBlocks[i]->ThisProgram->TargetFullscreen = 1.0;
            //cout << AllBlocks[i]->ThisProgram->TargetFullscreen << endl;
            return AllBlocks[i];
        i++;
    }
}


