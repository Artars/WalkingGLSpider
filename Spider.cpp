#include "Spider.h"

Spider::Spider(GLfloat x,GLfloat y,GLfloat s,GLfloat angS,GLfloat froS){
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

void Spider::target(GLfloat x, GLfloat y){
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

void Spider::update(double delta){
	if (!reachedAngle) {		//Realiza c�lculo de �ngulo a ser encontrado
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
    if(shouldMove){			//Realiza c�lculo de movimenta��o do objeto
        posX += direction[0] * delta/1000 * frontSpeed;
        posY += direction[1] * delta/1000 * frontSpeed;

        float distance = sqrt(pow(targetX - posX,2) + pow(targetY - posY,2));

        if(distance <= posThreshold){
            shouldMove = 0;
        }
    }
}

void Spider::draw(){
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
	

    glPopMatrix();
     
    /* glBegin(GL_POINTS);
        glVertex2f(posX, posY);
    glEnd(); */
}

void Spider::drawEllipse(float posX, float posY, float radiusX, float radiusY, float r, float g, float b) {
	glBegin(GL_TRIANGLE_FAN);	//Inicia o processo de desenhar uma elipse
	glColor3f(r, g, b);			//Cria um conjunto de triângulos com um ponto no centro da elipse
	glVertex2f(posX, posY);

	for (int d = 0; d <= 360; d++) {	//E os outros dois pontos nas bordas, completando um círculo de 360 graus
		float rad = d / rad2Deg;
		glVertex2f(posX + cos(rad)*radiusX, posY + sin(rad)*radiusY);
	}
	glEnd();
}