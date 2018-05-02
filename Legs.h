#ifndef LEGS
#define LEGS

#include <GL/glut.h>
#include <cmath>
#include "Legs.h"



typedef struct Point{
    GLint x;
    GLint y;
}Point;

class Legs{
    GLfloat position[2], scale[2], angle;
    Point pontos[3];
    Legs* child;

    public:
        Legs(GLfloat x, GLfloat y, GLfloat sizeX, GLfloat sizeY, GLfloat rotation);
        void setPosition(GLfloat x, GLfloat y);
        void setRotation(GLfloat angle);
        void setScale(GLfloat x, GLfloat y);
        Point getPonto0();
        Point getPonto1();
        Point getPonto2();
        void createChild(GLfloat x, GLfloat y, GLfloat sizeX, GLfloat sizeY, GLfloat rotation);
        Legs* getChild();
        void draw();
    private:
        void drawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat width);
};


#endif
