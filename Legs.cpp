#include "Legs.h"

#lalala

int x, y;


int Round(float a) {		//any x i.e 1>=x>=0.5 is rounded to 1

    if(a-int(a)>=0.5){
      return int(a)+1;
    }

    else {
      return int(a);
    }
}


Legs::Legs(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3) {
    pontos[0].x = x1;
    pontos[0].y = y1;
    pontos[1].x = x2;
    pontos[1].y = y2;
    pontos[2].x = x3;
    pontos[2].y = y3;
}

void Legs::drawLine(GLint x1, GLint y1, GLint x2, GLint y2) {
    glColor3f(0,0,0);
    glLineWidth(5);

    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
}

void Legs::setPosition(GLfloat x, GLfloat y) {

}

void Legs::setRotation(GLfloat angle) {

}

void Legs::setScale(GLfloat x, GLfloat y) {

}

Point Legs::getPonto0() {
    return pontos[0];
}

Point Legs::getPonto1() {
    return pontos[1];
}

Point Legs::getPonto2() {
    return pontos[2];
}

void Legs::drawLeg() {
    drawLine(pontos[0].x, pontos[0].y, pontos[1].x, pontos[1].y);
    drawLine(pontos[1].x, pontos[1].y, pontos[2].x, pontos[2].y);
}
