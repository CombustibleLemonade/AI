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

#include "LoadText.hpp"
#include "Display.hpp"
#include "Blocks.hpp"


using namespace std;

Block::Block(char *TextureName) {
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
