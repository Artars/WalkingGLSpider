#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include "Spider.h"

using namespace std;

GLint WINDOW_WIDTH  = 800,
      WINDOW_HEIGHT = 800;

void init();
void render();

void mouse_click(GLint button, GLint action, GLint x, GLint y);
void updateGame(int value);

void drawEllipse(float posX, float posY, float radiusX, float radiusY, float r, float g, float b);

int dt = 1000/60;

//Legs perna = Legs(100, 200, 300, 400, 600, 400);

Spider* muffet = new Spider(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 100, 1,100);

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

  muffet->draw();

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
        muffet->target(x,y);
        //tri.setPos(x,y);
    }

}

void updateGame(int value) {
    muffet->update(dt);

    glutTimerFunc(dt, updateGame, 0);
    glutPostRedisplay();

}
