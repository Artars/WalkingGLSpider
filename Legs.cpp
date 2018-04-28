#include "Legs.h"

int Round(float a) {		//any x i.e 1>=x>=0.5 is rounded to 1

    if(a-int(a)>=0.5){
      return int(a)+1;
    }

    else {
      return int(a);
    }
}

Legs::Legs(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3) {
    position[0] = x1;
    position[1] = y1;

}

void Legs::drawLine(GLint x1, GLint y1, GLint x2, GLint y2, GLint x, GLint y) {
      int xinc, yinc;
      GLint ydif = y2-y1;
      GLint xdif = x2-x1;
      GLint passo;

      if (abs(xdif) > abs(ydif)){
        passo = abs(xdif);
      }

      else{
        passo = abs(ydif);
      }

      xinc = xdif/passo;
      yinc = ydif/passo;

      x = x1;
      y = y1;

      for(int k = 0; k < passo; k++){
          x = x + xinc;
          y = y + yinc;

      	  glColor3f(1,1,0);
      		glPointSize(3);

      	  glBegin(GL_POINTS);
              glVertex2i(Round(x),Round(y));
          glEnd();
      }

      glutPostRedisplay();


}

void Legs::setPosition(GLfloat x, GLfloat y) {

}

void Legs::setRotation(GLfloat angle) {

}

void Legs::setScale(GLfloat x, GLfloat y) {

}

void Legs::drawLeg(GLint x, GLint y) {
  drawLine(100, 200, 300, 400, x, y);
  drawLine(300, 400, 600, 400, x, y);
}
