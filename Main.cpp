#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include "Spider.h"
#include "Legs.h"

using namespace std;

GLint WINDOW_WIDTH  = 500,
      WINDOW_HEIGHT = 500;

void init();
void render();

void mouse_click(GLint button, GLint action, GLint x, GLint y);
void updateGame(int value);

void drawEllipse(float posX, float posY, float radiusX, float radiusY, float r, float g, float b);

int dt = 1000/60;

Legs perna = Legs(100, 200, 300, 400, 600, 400);


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

    reachedAngle = 0;
    shouldMove = 0;

    currAngleSpeed = ( (targetAngle - angleDir) > 0)? angSpeed : -angSpeed;

    //Debug
    /* angleDir = targetAngle + angleOffset;
    angDegDir = angleDir * rad2Deg; */
}

void TestTriangle::update(double delta){
	if (!reachedAngle) {		//Realiza c�lculo de �ngulo a ser encontrado
        angleDir += currAngleSpeed * delta/1000;
        float delta = angleDir - targetAngle;
        if(abs(delta) <= angThreshold){
            reachedAngle = 1;
            shouldMove = 1;
            angleDir = targetAngle;
            direction[0] = cos(angleDir - angleOffset);
            direction[1] = sin(angleDir - angleOffset);
        }

        angDegDir = angleDir * rad2Deg;
    }
    if(shouldMove){			//Realiza c�lculo de movimenta��o do objeto
        posX += direction[0] * delta/1000 * frontSpeed;
        posY += direction[1] * delta/1000 * frontSpeed;

        float distance = sqrt(pow(targetX - posX,2) + pow(targetY - posY,2));

        if(distance <= posThreshold){
            shouldMove = 0;
        }
    }
}

void TestTriangle::draw(){
    glColor3f(0,0,0);
    glPointSize(size);

    glPushMatrix();
    glTranslatef(posX,posY, 0);    //Cria uma matriz de transforma��es: transla��o para origem, rota��o e transla��o de volta ao local incial
    glRotatef(angDegDir,0,0,1);
    glTranslatef(-posX,-posY,0);

						//Todos os par�metros est�o baseados na vari�vel "size", para que a aranha possa ser facilmente modificada
	float raioXC = 0.3 * size,
		raioYC = 0.4 * size,
		raioXA = 0.4 * size,
		raioYA = 0.5 * size,
		raioOlho = 0.03 * size,

		offset = size / 4;


	drawEllipse(posX, posY - offset, raioXC, raioYC, 0, 0, 0);//Elipse do cefalotorax
	drawEllipse(posX, posY + offset, raioXA, raioYA, 0, 0, 0);//Elipse do abdome

	drawEllipse(posX + raioXC / 5, posY - raioYC, raioOlho, raioOlho, 1, 0, 0);	//Desenhando os olhos
	drawEllipse(posX - raioXC / 5, posY - raioYC, raioOlho, raioOlho, 1, 0, 0);

  //pernas[0].drawLeg();


    glPopMatrix();

    /* glBegin(GL_POINTS);
        glVertex2f(posX, posY);
    glEnd(); */
}

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

TestTriangle tri = TestTriangle(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 100, 1,100);
//Peti��o: batizar nossa aranha de Muffet OU Peter Parker

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  GLint screen_width  = glutGet(GLUT_SCREEN_WIDTH),
        screen_height = glutGet(GLUT_SCREEN_HEIGHT);

  glutInitWindowPosition((screen_width - WINDOW_WIDTH) / 2, (screen_height - WINDOW_WIDTH) / 2);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_WIDTH);
  glutCreateWindow("2D Spider");

  init();
  glutDisplayFunc(render);

  glutMouseFunc(mouse_click);

  glutTimerFunc(dt, updateGame, 0);

  glutPostRedisplay();

  glutMainLoop();


  return EXIT_SUCCESS;
}

void init()
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glMatrixMode(GL_PROJECTION);

  gluOrtho2D(0, WINDOW_WIDTH,WINDOW_HEIGHT, 0);
}

void render()
{
  glClear(GL_COLOR_BUFFER_BIT);

  //std::cout<<"Desenho\n";

  tri.draw();

  glFlush();
}

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
            cout << perna.getPonto0().x << endl;
            cout << perna.getPonto0().y << endl;
            cout << perna.getPonto1().x << endl;
            cout << perna.getPonto1().y << endl;
            cout << perna.getPonto2().x << endl;
            cout << perna.getPonto2().y<< endl;
        }
        tri.target(x,y);
        //tri.setPos(x,y);
    }

}

void updateGame(int value) {
    tri.update(dt);

    glutTimerFunc(dt, updateGame, 0);
    glutPostRedisplay();

}
