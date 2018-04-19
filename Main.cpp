#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <cmath>

GLint WINDOW_WIDTH  = 500,
      WINDOW_HEIGHT = 500;
      
void init();      
void render();

void mouse_click(GLint button, GLint action, GLint x, GLint y);
void updateGame(int value);

int dt = 1000/60;

double rad2Deg = (180.0/3.141592653589793238463);

class TestTriangle {
    GLfloat posX, posY, size, angSpeed, frontSpeed;
    GLfloat angleDir, angDegDir, direction[2];
    GLfloat angThreshold = 0.1, posThreshold = 0.5;
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
    if(!reachedAngle){
        angleDir += currAngleSpeed * delta/1000;
        float delta = angleDir - targetAngle;
        if(std::abs(delta) <= angThreshold){
            reachedAngle = 1;
            shouldMove = 1;
            angleDir = targetAngle;
            direction[0] = cos(angleDir - angleOffset);
            direction[1] = sin(angleDir - angleOffset);
        }

        angDegDir = angleDir * rad2Deg;       
    }
    if(shouldMove){
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
    glTranslatef(posX,posY, 0);    
    glRotatef(angDegDir,0,0,1);
    glTranslatef(-posX,-posY,0);
    
    
    

    glBegin(GL_TRIANGLES);
    glColor3f(0,0,0);
    glVertex2f(posX - size/2, posY + size/2);
    glVertex2f(posX, posY - size/2);
    glVertex2f(posX + size/2, posY + size/2);
    glEnd();
    
    glPopMatrix();    
     
    /* glBegin(GL_POINTS);
        glVertex2f(posX, posY);
    glEnd(); */
}

TestTriangle tri = TestTriangle(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 100, 1,100);

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
  
  std::cout<<"Desenho\n";

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
            std::cout << "Clicou em X= " << x << " , Y= " << y << ".\n";
            
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




