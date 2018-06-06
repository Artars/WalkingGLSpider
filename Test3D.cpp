#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include "Transform.h"
#include "Vector3.h"
#include "Spider3D.h"

using namespace std;

GLint WINDOW_WIDTH  = 800,
      WINDOW_HEIGHT = 800;

void init();
void render();

void mouse_click(GLint button, GLint action, GLint x, GLint y);
void updateGame(int value);

void drawEllipse(float posX, float posY, float radiusX, float radiusY, float r, float g, float b);

int dt = 1000/60;

GLfloat pos[3] = {2,0,2};
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

Spider3D *test = new Spider3D(Vector3(0,0,0),Vector3(1,1,1),Vector3(0,0,0));

char path[] = "cone.obj";

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
  glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH | GLUT_RGB);

  GLint screen_WIDTH  = glutGet(GLUT_SCREEN_WIDTH),
        screen_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);

  glutInitWindowPosition((screen_WIDTH - WINDOW_WIDTH) / 2, (screen_HEIGHT - WINDOW_WIDTH) / 2);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_WIDTH);
  glutCreateWindow("3D Spider");

  glDepthMask(GL_TRUE);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  test->loadModel(path);
  test->setColor(1.0,0.0,0.0);


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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //std::cout<<"Desenho\n";

    glLoadIdentity();
    gluLookAt(pos[0],pos[1],pos[2],0,0,0,0,0,1);

    drawGrid();
    glViewport(0, WINDOW_HEIGHT/4, WINDOW_WIDTH/2, WINDOW_HEIGHT);
    glLoadIdentity();
    gluLookAt(6.0, 0.0, 0.0, test->position.x, test->position.y, test->position.z, 0.0, 1.0, 0.0);

    //glRotatef(-90.0, 1.0, 0.0, 0.0);

    test->draw();
   
  /** Desenha a janela mais a direita */
    glViewport(WINDOW_WIDTH/2, WINDOW_HEIGHT/4, WINDOW_WIDTH/2, WINDOW_HEIGHT);
    glLoadIdentity();
    gluLookAt(0.0, 6.0, 0.0, test->position.x, test->position.y, test->position.z , 1.0, 0.0, 0.0);
    //glRotatef(-90.0, 1.0, 0.0, 0.0);
  
    test->draw();
    
    glViewport(0, -WINDOW_HEIGHT/4, WINDOW_WIDTH/2, WINDOW_HEIGHT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 6.0, test->position.x, test->position.y, test->position.z, 0.0, 1.0, 0.0);
    //glRotatef(-90.0, 1.0, 0.0, 0.0);
  
    test->draw();

    glViewport(WINDOW_WIDTH/2, -WINDOW_HEIGHT/4, WINDOW_WIDTH/2, WINDOW_HEIGHT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0, test->position.x, test->position.y, test->position.z, 0.0, 1.0, 0.0);
    //glRotatef(-90.0, 1.0, 0.0, 0.0);
  
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
        pos[0] = cos(angle)*3;
        pos[1] = sin(angle)*3;
        pos[2] = 0;
    }
    else if(key == GLUT_KEY_LEFT){
        angle -= speed;
        pos[0] = cos(angle)*3;
        pos[1] = sin(angle)*3;
        pos[2] = 0;
    }
    glutPostRedisplay();
}