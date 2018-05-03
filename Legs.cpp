#include "Legs.h"

int x, y;


int Round(float a) {		//any x i.e 1>=x>=0.5 is rounded to 1

    if(a-int(a)>=0.5){
      return int(a)+1;
    }

    else {
      return int(a);
    }
}


Legs::Legs(GLfloat x, GLfloat y, GLfloat sizeX, GLfloat sizeY, GLfloat rotation) {
    position[0] = x;
    position[1] = y;
    scale[0] = sizeX;
    scale[1] = sizeY;
    angle = rotation;
}

void Legs::createChild(GLfloat x, GLfloat y, GLfloat sizeX, GLfloat sizeY, GLfloat rotation) {
    child = new Legs(scale[0] + x,y, sizeX, sizeY, rotation);
}

Legs* Legs::getChild() {
    return child;
}

void Legs::drawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat width) {
    glColor3f(0,0,0);
    glLineWidth(width);

    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
}

void Legs::setPosition(GLfloat x, GLfloat y) {
    position[0] = x;
    position[1] = y;
}

void Legs::setRotation(GLfloat angle) {
    this->angle = angle;
}

void Legs::setScale(GLfloat x, GLfloat y) {
    scale[0] = x;
    scale[1] = y;
}


void Legs::draw() {
    //drawLine(pontos[0].x, pontos[0].y, pontos[1].x, pontos[1].y);
    //drawLine(pontos[1].x, pontos[1].y, pontos[2].x, pontos[2].y);

    //Aplicar matriz de rotação e translação
    glPushMatrix();
    glTranslatef(position[0], position[1], 0);
    glRotatef(-angle,0,0,1);

    drawLine(0,0, scale[0], 0, scale[1]);

    //Desenha o segmento filho
    if(child != NULL)
        child->draw();

    glPopMatrix();
}
