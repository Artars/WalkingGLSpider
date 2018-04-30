#include "Legs.h"

int x, y;

GLint WINDOW_WIDTH  = 500,
      WINDOW_HEIGHT = 500;

void init();
void render();

void mouse_click(GLint button, GLint action, GLint x, GLint y);
void updateGame(int value);

void drawEllipse(float posX, float posY, float radiusX, float radiusY, float r, float g, float b);

int dt = 1000/60;

//Legs perna = Legs(100, 200, 300, 400, 600, 400);


class TestTriangle {
    GLfloat posX, posY, size, angSpeed, frontSpeed;
    GLfloat angleDir, angDegDir, direction[2];
    //Legs pernas[8];
    GLfloat angThreshold = 0.1, posThreshold = 2;	//Originalmente era 0.5, mas as vezes a figura simplesmente escapava do ponto
    int reachedAngle = 1, shouldMove = 0;
    GLfloat currAngleSpeed, targetAngle, targetX, targetY;
    GLfloat angleOffset = 3.14/2;
    public:
        TestTriangle (GLfloat x,GLfloat y,GLfloat s,GLfloat angS,GLfloat froS);
        void target(GLfloat x, GLfloat y);
        void update(double delta);
        void draw();
        void setPos(GLfloat x, GLfloat y) {posX = x; posY = y;};
};

TestTriangle::TestTriangle(GLfloat x,GLfloat y,GLfloat s,GLfloat angS,GLfloat froS){
    posX = x;
    posY = y;
    size = s;
    angSpeed = angS;
    frontSpeed = froS;
    angleDir = angleOffset;
    angDegDir = angleDir * rad2Deg;
    direction[0] = cos(angleDir - angleOffset);
    direction[1] = sin(angleDir - angleOffset);
    //pernas[0] = Legs(100, 200, 300, 400, 600, 400);
}

void TestTriangle::target(GLfloat x, GLfloat y){
    GLfloat deltaX, deltaY;
    targetX = x;
    targetY = y;

    deltaX = targetX - posX;
    deltaY = targetY - posY;

    targetAngle = atan2(deltaY, deltaX);

    targetAngle += angleOffset;
>>>>>>> amnesia


int arredonda(float a) {		//any x i.e 1>=x>=0.5 is rounded to 1

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

    scale[0] = 4;
    scale[1] = 1;
    position[0] = 0;
    position[1] = 0;
}

<<<<<<< HEAD
void Legs::drawLine(GLint x1, GLint y1, GLint x2, GLint y2) {
      int xinc, yinc;
      GLint ydif = y2-y1;
      GLint xdif = x2-x1;
      GLint passo;

      if (abs(xdif) > abs(ydif)){
        passo = abs(xdif);
      }
=======
void drawEllipse(float posX, float posY, float radiusX, float radiusY, float r, float g, float b) {
	glBegin(GL_TRIANGLE_FAN);	//Inicia o processo de desenhar uma elipse
	glColor3f(r, g, b);			//Cria um conjunto de tri�ngulos com um ponto no centro da elipse
	glVertex2f(posX , posY);

	for (int d = 0; d <= 360; d++) {	//E os outros dois pontos nas bordas, completando um c�rculo de 360 graus
		float rad = d / rad2Deg;
		glVertex2f(posX + cos(rad)*radiusX, posY + sin(rad)*radiusY);
	}
	glEnd();
}

//Legs leg = Legs(100, 200, 300, 400, 500);

//TestTriangle tri = TestTriangle(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 100, 1,100);
//Peti��o: batizar nossa aranha de Muffet OU Peter Parker

Spider* muffet = new Spider(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 100, 1,100);

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
>>>>>>> amnesia

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

      	  glColor3f(0,0,0);
      		glPointSize(3);

      	  glBegin(GL_POINTS);
              glVertex2i(arredonda(x),arredonda(y));
          glEnd();
      }

      glutPostRedisplay();


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

Point Legs::getPonto0() {
    return pontos[0];
}

<<<<<<< HEAD
Point Legs::getPonto1() {
    return pontos[1];
}
=======
  muffet->draw();
>>>>>>> amnesia

Point Legs::getPonto2() {
    return pontos[2];
}

<<<<<<< HEAD
void Legs::draw() {
    //drawLine(pontos[0].x, pontos[0].y, pontos[1].x, pontos[1].y);
    //drawLine(pontos[1].x, pontos[1].y, pontos[2].x, pontos[2].y);
=======
void mouse_click(GLint button, GLint action, GLint x, GLint y)
{
/*   switch(button)
  {
    case GLUT_LEFT_BUTTON:
    {
      std::cout<<"Esquerda";
      break;
    }
    case GLUT_MIDDLE_BUTTON:
    {
      std::cout<<"Meio";
      break;
    }
    case GLUT_RIGHT_BUTTON:
    {
      std::cout<<"Direita";
      break;
    }
    default: break;
  } */

    if(button == GLUT_LEFT_BUTTON){
        if(action == GLUT_DOWN) {
            cout << "Clicou em X= " << x << " , Y= " << y << ".\n";
        }
        muffet->target(x,y);
        //tri.setPos(x,y);
    }
>>>>>>> amnesia

    glPushMatrix();
    glTranslatef(position[0], position[1], 0);
    glRotatef(angle,0,0,1);

<<<<<<< HEAD
=======
void updateGame(int value) {
    muffet->update(dt);
>>>>>>> amnesia


    glBegin(GL_QUADS);
        glVertex2f(0,scale[1]/2);
        glVertex2f(scale[0],scale[1]/2);
        glVertex2f(scale[0],-scale[1]/2);
        glVertex2f(0,-scale[1]/2);
    glEnd();

    glPopMatrix();
}
