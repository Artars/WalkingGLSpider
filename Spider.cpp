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

    int i = 0;
    GLfloat sizeX = size;
    GLfloat sizeY = size/16;

    //Perna dianteira direita
    legs[0] = new Legs(10,10,sizeX,sizeY,60);
    legs[0]->createChild(0,0,sizeX/2,sizeY, -30);    

    //Perna traseira direita
    legs[3] = new Legs(10,60,sizeX/2,sizeY, 30);
    legs[3]->createChild(0,0,sizeX,sizeY, -90);

    //Pernas intermediarias direitas
    legs[1] = new Legs(10,20,sizeX/2,sizeY,30);
    legs[1]->createChild(0,0,sizeX/2,sizeY, -90);        
    legs[2] = new Legs(10,40,sizeX/2,sizeY,30);
    legs[2]->createChild(0,0,sizeX/2,sizeY, -90);      

    //Perna dianteira esquerda
    legs[4] = new Legs(-10,10,sizeX,sizeY,120);
    legs[4]->createChild(0,0,sizeX/2,sizeY, 30);    

    //Perna traseira equerda
    legs[7] = new Legs(-10,60,sizeX/2,sizeY, 150);
    legs[7]->createChild(0,0,sizeX,sizeY, 90);

    //Pernas intermediarias direitas
    legs[5] = new Legs(-10,20,sizeX/2,sizeY,150);
    legs[5]->createChild(0,0,sizeX/2,sizeY, 90);        
    legs[6] = new Legs(-10,40,sizeX/2,sizeY,150);
    legs[6]->createChild(0,0,sizeX/2,sizeY, 90);     
    
    
    //legs[0]->setRotation(180);
    
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

    EstadoAranha = P2;

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
            EstadoAranha = P1;
        }
    }

    updateLegs(delta);

}

void Spider::draw(){
    glColor3f(0,0,0);
    glPointSize(size);

    glPushMatrix();
    glTranslatef(posX,posY, 0);    //Cria uma matriz de transforma��es: transla��o para origem, rota��o e transla��o de volta ao local incial
    glRotatef(angDegDir,0,0,1);
    glTranslatef(-posX,-posY,0);
    glTranslatef(posX,posY, 0);    

    //Desenha pernas
    int i;
    for(i = 0; i < 8; i++){
        if(legs[i] != NULL)
            legs[i]->draw();
    }

						//Todos os par�metros est�o baseados na vari�vel "size", para que a aranha possa ser facilmente modificada
	float raioXC = 0.3 * size,
		raioYC = 0.4 * size,
		raioXA = 0.4 * size,
		raioYA = 0.5 * size,
		raioOlho = 0.03 * size,

		offset = size / 4;


	drawEllipse(0, 0 - offset, raioXC, raioYC, 0, 0, 0);//Elipse do cefalotorax
	drawEllipse(0, 0 + offset, raioXA, raioYA, 0, 0, 0);//Elipse do abdome

	drawEllipse(0 + raioXC / 5, 0 - raioYC, raioOlho, raioOlho, 1, 0, 0);	//Desenhando os olhos
	drawEllipse(0 - raioXC / 5, 0 - raioYC, raioOlho, raioOlho, 1, 0, 0);

    


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

void Spider::updateLegs(double delta){

}
