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

    public:
        Legs(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3);
        void drawLine(GLint x1, GLint y1, GLint x2, GLint y2);
        void setPosition(GLfloat x, GLfloat y);
        void setRotation(GLfloat angle);
        void setScale(GLfloat x, GLfloat y);
        Point getPonto0();
        Point getPonto1();
        Point getPonto2();
        void drawLeg();
};


#endif
