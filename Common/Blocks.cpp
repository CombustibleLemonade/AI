#include <iostream>
#include <vector>

#ifdef __APPLE__
#include <GLEW/glew.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

#include "Display.hpp"
#include "Blocks.hpp"

using namespace std;

vector<Block*> AllBlocks;

Block::Block (float LocationArg[1]) {
    AllBlocks.push_back(this);

    Location[0] = LocationArg[0];
    Location[1] = LocationArg[1];
    float HaloCubeContents[] = {
        -1.1f + Location[0], -1.1f + Location[1],
        1.1f + Location[0], -1.1f + Location[1],
        1.1f + Location[0],  1.1f + Location[1],
        -1.1f + Location[0],  1.1f + Location[1]
     };
    ProgramReturn(0)->ExtendVerts(HaloCubeContents);
    float CubeContents[] = {
        -1.0f + Location[0], -1.0f + Location[1],
        1.0f + Location[0], -1.0f + Location[1],
        1.0f + Location[0],  1.0f + Location[1],
        -1.0f + Location[0],  1.0f + Location[1]
         };
    ProgramReturn(1)->ExtendVerts(CubeContents);
}

void CreateBlock(float Location[1]) {
    AllBlocks.push_back(new Block (Location));
}
