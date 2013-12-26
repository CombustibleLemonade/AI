#ifndef DISPLAY
#define DISPLAY

int init ();

void onDisplay ();

GLuint ProgramReturn ();

class cube{
public:
    cube* previous[];
    cube* next[];
};

#endif
