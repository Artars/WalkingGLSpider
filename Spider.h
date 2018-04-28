#ifndef SPIDER
#define SPIDER

#include <GL/glut.h>
#include <cmath>
#include "Legs.h"

#define rad2Deg (180.0/3.141592653589793238463);

class Spider {
    GLfloat posX, posY, size, angSpeed, frontSpeed;
    GLfloat angleDir, angDegDir, direction[2];
    GLfloat angThreshold = 0.1, posThreshold = 2;	//Originalmente era 0.5, mas as vezes a figura simplesmente escapava do ponto
    int reachedAngle = 1, shouldMove = 0;
    GLfloat currAngleSpeed, targetAngle, targetX, targetY;
    GLfloat angleOffset = 3.14/2;
    public:
        Spider (GLfloat x,GLfloat y,GLfloat s,GLfloat angS,GLfloat froS);
        void target(GLfloat x, GLfloat y);
        void update(double delta);
        void draw();
        void setPos(GLfloat x, GLfloat y) {posX = x; posY = y;};
    private:
        void drawEllipse(float posX, float posY, float radiusX, float radiusY, float r, float g, float b);

};

#endif
