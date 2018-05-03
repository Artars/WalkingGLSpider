#ifndef LEGS
#define LEGS

#include <GL/glut.h>
#include <cmath>
#include "Legs.h"

class Legs{
    Legs* child;

    public:
        GLfloat position[2], scale[2], angle;
        Legs(GLfloat x, GLfloat y, GLfloat sizeX, GLfloat sizeY, GLfloat rotation);
        void setPosition(GLfloat x, GLfloat y);
        void setRotation(GLfloat angle);
        void setScale(GLfloat x, GLfloat y);
        void createChild(GLfloat x, GLfloat y, GLfloat sizeX, GLfloat sizeY, GLfloat rotation);
        Legs* getChild();
        void draw();
    private:
        void drawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat width);
};


#endif
