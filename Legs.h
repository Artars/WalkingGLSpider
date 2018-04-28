#ifndef LEGS
#define LEGS

#include <GL/glut.h>
#include <cmath>
#include "Legs.h"

class Legs{
    GLfloat position[2], scale[2], angle;
    public:
        void drawLine(GLint x1, GLint y1, GLint x2, GLint y2, GLint x, GLint y);
        void setPosition(GLfloat x, GLfloat y);
        void setRotation(GLfloat angle);
        void setScale(GLfloat x, GLfloat y);
        void drawLeg(GLint x, GLint y);

};


#endif
