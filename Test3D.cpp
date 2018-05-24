#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include "Transform.h"
#include "Vector3.h"
#include "Objector.h"

using namespace std;

GLint WINDOW_WIDTH  = 800,
      WINDOW_HEIGHT = 800;

void init();
void render();

void mouse_click(GLint button, GLint action, GLint x, GLint y);
void updateGame(int value);

void drawEllipse(float posX, float posY, float radiusX, float radiusY, float r, float g, float b);

int dt = 1000/60;

GLfloat pos[3] = {10,0,10};
GLfloat angle = 0;
GLfloat speed = 0.1;
void keyboard_special_keys(GLint key, GLint x, GLint y);

void drawGrid(){
    int i, j;
    glColor3f(0,0,0);
    for(i = -100; i < 99; i++){
        glBegin(GL_LINES);
        glVertex3f(-100,i,0);
        glVertex3f(100,i,0);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(i,-100,0);
        glVertex3f(i,100,0);
        glEnd();
    }
}

//Legs perna = Legs(100, 200, 300, 400, 600, 400);

Transform *test = new Transform(Vector3(0,0,0),Vector3(1,1,1),Vector3(90,0,0));

char path[] = "Spider.obj";

void reshapeCallback(int w, int h)
{
  /** Atualiza os valores da janela */
  WINDOW_WIDTH = w;
  WINDOW_HEIGHT = h;
  /** Define o volume de vista */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  GLint screen_width  = glutGet(GLUT_SCREEN_WIDTH),
        screen_height = glutGet(GLUT_SCREEN_HEIGHT);

  glutInitWindowPosition((screen_width - WINDOW_WIDTH) / 2, (screen_height - WINDOW_WIDTH) / 2);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_WIDTH);
  glutCreateWindow("2D Spider");

  test->loadModel(path);
  test->setColor(0.2,0.2,0.2);

  init();

  glutDisplayFunc(render);
  glutReshapeFunc(reshapeCallback);  
  glutSpecialFunc(keyboard_special_keys);
  

  glutMouseFunc(mouse_click);

  glutPostRedisplay();

  glutMainLoop();


  return EXIT_SUCCESS;
}

void init()
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  //glMatrixMode(GL_PROJECTION);

  //gluOrtho2D(0, WINDOW_WIDTH,WINDOW_HEIGHT, 0);

}

void render()
{
  glClear(GL_COLOR_BUFFER_BIT);

  //std::cout<<"Desenho\n";

    glLoadIdentity();
    gluLookAt(pos[0],pos[1],pos[2],0,0,0,0,0,1);

    drawGrid();
    test->draw();
    


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
        }
        //tri.setPos(x,y);
    }

}

void keyboard_special_keys(GLint key, GLint x, GLint y) {
    if(key == GLUT_KEY_RIGHT){
        angle += speed;
        pos[0] = cos(angle)*10;
        pos[1] = sin(angle)*10;
        pos[2] = 10;
    }
    else if(key == GLUT_KEY_LEFT){
        angle -= speed;
        pos[0] = cos(angle)*10;
        pos[1] = sin(angle)*10;
        pos[2] = 10;
    }
    glutPostRedisplay();
}