#ifndef LEGS
#define LEGS

#include <GL/glut.h>
#include <cmath>
#include "Legs.h"

class Legs{
    GLfloat position[2], scale[2], angle;
    public:
        void setPosition(GLfloat x, GLfloat y);
        void setRotation(GLfloat angle);
        void setScale(GLfloat x, GLfloat y);
        void draw();

};


#endif