#ifdef __APPLE__
#include <GLEW/glew.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

#include <fstream>
#include <iostream>

#include "LoadText.hpp"

const char* ReturnShaderCode;

using namespace std;

string FileToString (const char* Shader) {
    string ShaderCode = "";

    ifstream ShaderStream(Shader, std::ios::in);

    if(ShaderStream.is_open()){
        string Line = "";
        while(getline(ShaderStream, Line)){
            ShaderCode += "\n" + Line;
        }
        ShaderStream.close();
        return ShaderCode;
    }else{
        printf("Impossible to open. Are you in the right directory?\n");
    }
}
