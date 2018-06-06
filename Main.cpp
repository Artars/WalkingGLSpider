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

int axisRotButton = 0;
int axisFowButton = 0;

GLfloat pos[3] = {2,0,2};
GLfloat angle = 0;
GLfloat speed = 0.1;
void keyboard_special_keys(GLint key, GLint x, GLint y);
void keyboard_special_keys_up(GLint key, GLint x, GLint y);

void drawGrid(){
    int i, j;
    GLfloat maxX = 10,maxY = 10, size = 0.3;
    glColor3f(0,0,0);
    for(i = -maxX; i < maxX; i++){
      for(j = -maxY; j < maxY; j++){
        if((i+j) % 2 == 0){
          glColor3f(1,0,1);
        }
        else
          glColor3f(0,0,0);
        glBegin(GL_QUADS);
        glVertex3f(maxX*i*size,maxY*j*size,0);
        glVertex3f(maxX*(i+1)*size,maxY*j*size,0);        
        glVertex3f(maxX*(i+1)*size,maxY*(j+1)*size,0);
        glVertex3f(maxX*i*size,maxY*(j+1)*size,0);
        glEnd();
      }
    }
}

//Legs perna = Legs(100, 200, 300, 400, 600, 400);

Spider3D *parker = new Spider3D(Vector3(0,0,0.2),Vector3(1,1,1),Vector3(0,0,0));

char path[] = "Spider.obj";

void reshapeCallback(int w, int h)
{
  /** Atualiza os valores da janela */
  WINDOW_WIDTH = w;
  WINDOW_HEIGHT = h;
  /** Define o volume de vista */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 0.01, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH | GLUT_RGB);

  GLint screen_width  = glutGet(GLUT_SCREEN_WIDTH),
        screen_height = glutGet(GLUT_SCREEN_HEIGHT);

  glutInitWindowPosition((screen_width - WINDOW_WIDTH) / 2, (screen_height - WINDOW_WIDTH) / 2);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_WIDTH);
  glutCreateWindow("3D Spider");

  glDepthMask(GL_TRUE);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);



  //parker->loadModel(path);
  parker->setColor(0.1,0.1,0.1);

  init();

  glutDisplayFunc(render);
  glutReshapeFunc(reshapeCallback);  
  glutSpecialFunc(keyboard_special_keys);
  glutSpecialUpFunc(keyboard_special_keys_up);
  

  glutTimerFunc(dt, updateGame, 0);

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

    glViewport(0, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    glLoadIdentity();
    gluLookAt(0.01, 3.0, 0.5, parker->position.x, parker->position.y, parker->position.z, 0.0, 0, 1.0);

    //glRotatef(-90.0, 1.0, 0.0, 0.0);
    drawGrid();
    
    parker->draw();
   
  /** Desenha a janela mais a direita */
    glViewport(0, WINDOW_HEIGHT/2, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    glLoadIdentity();
    gluLookAt(3.0, 0.01, 0.5, parker->position.x, parker->position.y, parker->position.z , 0, 0.0, 1.0);
    //glRotatef(-90.0, 1.0, 0.0, 0.0);

    drawGrid();      
    parker->draw();
    
    glViewport(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    glLoadIdentity();
    gluLookAt(0.01, 0.01, 3.0, parker->position.x, parker->position.y, parker->position.z, 0.0, 0.0, 1.0);
    //glRotatef(-90.0, 1.0, 0.0, 0.0);
  
    drawGrid();    
    parker->draw();

    glViewport(WINDOW_WIDTH/2, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    glLoadIdentity();
    gluLookAt(5, 5, 5.0, parker->position.x, parker->position.y, parker->position.z, 0.0, 0.0, 1.0);
    //glRotatef(-90.0, 1.0, 0.0, 0.0);
  
    drawGrid();    
    parker->draw();

  glFlush();
}

void keyboard_special_keys(GLint key, GLint x, GLint y) {
    if(key == GLUT_KEY_RIGHT){
        axisRotButton = -1;
        parker->turn(axisRotButton);        
    }
    else if(key == GLUT_KEY_LEFT){
        axisRotButton = 1;
        parker->turn(axisRotButton);        
    }
    if(key == GLUT_KEY_UP){
      axisFowButton = -1;
      parker->advance(axisFowButton);
    }
    else if(key == GLUT_KEY_DOWN){
      axisFowButton = 1;
      parker->advance(axisFowButton);
    }
}


void keyboard_special_keys_up(GLint key, GLint x, GLint y) {
  if(key == GLUT_KEY_RIGHT){
    if(axisRotButton == -1)
      axisRotButton = 0;
  }
  else if (key == GLUT_KEY_LEFT){
    if(axisRotButton == 1)
      axisRotButton = 0;
  }
  if(key == GLUT_KEY_UP){
    if(axisFowButton == -1)
      axisFowButton = 0;
  }
  else if(key == GLUT_KEY_DOWN){
    if(axisFowButton == 1)
      axisFowButton = 0;
  }
  parker->advance(axisFowButton);
  parker->turn(axisRotButton);
}

void updateGame(int value) {
  parker->update(dt);

  glutTimerFunc(dt, updateGame, 0);  
  glutPostRedisplay();
  

}
