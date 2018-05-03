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

    float offset = size / 2;

    EstadoAranha = P1;
    animationCounter = animationTime/2;

    //Perna dianteira direita
    legs[0] = new Legs(10,10 - offset,sizeX,sizeY,60);
    legs[0]->createChild(0,0,sizeX/2,sizeY, -30);    

    //Perna traseira direita
    legs[3] = new Legs(10,60- offset,sizeX/2,sizeY, 30);
    legs[3]->createChild(0,0,sizeX,sizeY, -90);

    //Pernas intermediarias direitas
    legs[1] = new Legs(10,20- offset,sizeX/2,sizeY,30);
    legs[1]->createChild(0,0,sizeX/2,sizeY, -90);        
    legs[2] = new Legs(10,40- offset,sizeX/2,sizeY,30);
    legs[2]->createChild(0,0,sizeX/2,sizeY, -90);      

    //Perna dianteira esquerda
    legs[4] = new Legs(-10,10 - offset,sizeX,sizeY,120);
    legs[4]->createChild(0,0,sizeX/2,sizeY, 30);    

    //Perna traseira equerda
    legs[7] = new Legs(-10,60- offset,sizeX/2,sizeY, 150);
    legs[7]->createChild(0,0,sizeX,sizeY, 90);

    //Pernas intermediarias direitas
    legs[5] = new Legs(-10,20 - offset,sizeX/2,sizeY,150);
    legs[5]->createChild(0,0,sizeX/2,sizeY, 90);        
    legs[6] = new Legs(-10,40 - offset,sizeX/2,sizeY,150);
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

    //Ajuste de angulo para que ele fique dentro do intervalo de -180 até 180
    if(angleDir > 180) angleDir =  -(360 - 180);
    if(angleDir < -180) angleDir = (360 + angleDir);


    GLfloat deltaAngle = targetAngle - angleDir;

    currAngleSpeed = ( (deltaAngle) > 0)? angSpeed : -angSpeed;

    EstadoAranha = ( (deltaAngle) > 0)? P3 : P2;


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
            //animationCounter = animationTime/2;
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
	float raioXC = 0.4 * size,
		raioYC = 0.4 * size,
		raioXA = 0.5 * size,
		raioYA = 0.6 * size,
		raioOlho = 0.02 * size,

		offset = size / 4;


    //Pedipalpos
    drawEllipse(-raioXC*0.2, (-0.9f * raioYC)-offset, 0.2*raioXC, 0.4f * raioYC, 0.05, 0.05 , 0.05);
    drawEllipse(+raioXC*0.2, (-0.9f * raioYC)-offset, 0.2*raioXC, 0.4f * raioYC, 0.05, 0.05 , 0.05);

	drawEllipse(0, 0 - offset, raioXC, raioYC, 0.1, 0.1, 0.1);//Elipse do cefalotorax
	drawEllipse(0, 0 + offset*2, raioXA, raioYA, 0.1, 0.1, 0.1);//Elipse do abdome
    

	drawEllipse(0 + raioXC * 0.1f, 0 - raioYC*0.6f - offset, raioOlho, raioOlho, 1, 0, 0);	//Desenhando os olhos
	drawEllipse(0 - raioXC * 0.1f, 0 - raioYC*0.6f - offset, raioOlho, raioOlho, 1, 0, 0);
	drawEllipse(0 - raioXC * 0.3f, 0 - raioYC*0.6f - offset, raioOlho, raioOlho, 1, 0, 0);
	drawEllipse(0 + raioXC * 0.3f, 0 - raioYC*0.6f - offset, raioOlho, raioOlho, 1, 0, 0);
    
	drawEllipse(0 - raioXC * 0.1f, 0 - raioYC * 0.8f - offset, raioOlho, raioOlho, 1, 0, 0);
	drawEllipse(0 + raioXC * 0.1f, 0 - raioYC * 0.8f - offset, raioOlho, raioOlho, 1, 0, 0);
	drawEllipse(0 - raioXC * 0.3f, 0 - raioYC * 0.8f - offset, raioOlho, raioOlho, 1, 0, 0);
	drawEllipse(0 + raioXC * 0.3f, 0 - raioYC * 0.8f - offset, raioOlho, raioOlho, 1, 0, 0);
    
     
    
    

    


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

/*
    Vão ser utilizados cossenos para a animação, de tal maneira que o intervalo utilizado da onda seja de 0 a PI
    Dessa maneira, é calculado uma velocidade angular para tal
    Quando em P2, o tempo é crescente. Quando em P3, o tempo é decrescente
    Quando em P1, o tempo é parado na metade do ciclo, posição equivalente a 0, onde o cosseno não interfere
*/

void Spider::updateLegs(double delta){

    float angularSpeed = M_PI/animationTime;

    GLfloat sizeX = size;
    GLfloat sizeY = size/16;


    //Uso de cossenos pra rotação
    legs[0]->setRotation(60 + 5 * cos(angularSpeed * animationCounter));
    legs[1]->setRotation(30 - 8 * cos(angularSpeed * animationCounter));
    legs[2]->setRotation(30 + 8 * cos(angularSpeed * animationCounter));
    legs[3]->setRotation(30 - 6 * cos(angularSpeed * animationCounter));

    legs[4]->setRotation(120 + 5 * cos(angularSpeed * animationCounter));
    legs[5]->setRotation(150 - 8 * cos(angularSpeed * animationCounter));
    legs[6]->setRotation(150 + 8 * cos(angularSpeed * animationCounter));
    legs[7]->setRotation(150 - 6 * cos(angularSpeed * animationCounter));
    
    //Uso de cossenos para escala do lado direito
    legs[0]->setScale(sizeX - sizeX/8 *cos(angularSpeed * animationCounter), sizeY);
    //Necessidade de ajustar o filho, devido à mudança do final da perna
    legs[0]->getChild()->setPosition(sizeX - sizeX/8 *cos(angularSpeed * animationCounter), legs[0]->getChild()->position[1]);
    legs[0]->getChild()->setScale(sizeX/4 - sizeX/8*cos(angularSpeed * animationCounter), sizeY);

    legs[1]->getChild()->setScale(sizeX*0.3 - sizeX*0.1*cos(angularSpeed * animationCounter), sizeY);
    legs[2]->getChild()->setScale(sizeX*0.3 + sizeX*0.1*cos(angularSpeed * animationCounter), sizeY);
    

    legs[3]->getChild()->setScale(sizeX*0.75 - 0.25*sizeX* cos(angularSpeed * animationCounter), sizeY);

    //Uso de cossenos para escala do lado esquerdo
    legs[4]->setScale(sizeX + sizeX/8 *cos(angularSpeed * animationCounter), sizeY);
    legs[4]->getChild()->setPosition(sizeX + sizeX/8 *cos(angularSpeed * animationCounter), legs[0]->getChild()->position[1]);
    legs[4]->getChild()->setScale(sizeX/4 + sizeX/8*cos(angularSpeed * animationCounter), sizeY);

    legs[5]->getChild()->setScale(sizeX*0.3 + sizeX*0.1*cos(angularSpeed * animationCounter), sizeY);
    legs[6]->getChild()->setScale(sizeX*0.3 - sizeX*0.1*cos(angularSpeed * animationCounter), sizeY);

    legs[7]->getChild()->setScale(sizeX*0.75 + 0.25*sizeX* cos(angularSpeed * animationCounter), sizeY);
    

    if(EstadoAranha == P2){
        animationCounter -= delta/1000;
    }
    else if(EstadoAranha == P3){
        animationCounter += delta/1000;
    }
    //Fazer suavização para o ponto de parada da animação
    else if(EstadoAranha == P1){
        if((animationCounter - (animationTime)/2) > 0){
            animationCounter -= delta/1000;
            if(((animationCounter - (animationTime)/2) < 0)){
                animationCounter = (animationTime)/2;
            }
        }
        else if((animationCounter - (animationTime)/2) < 0) {
            animationCounter += delta/1000;
            if(((animationCounter - (animationTime)/2) > 0)){
                animationCounter = (animationTime)/2;
            }
        }
    }


    if(animationCounter < 0){
        EstadoAranha = P3;
        animationCounter = 0;
    }

    if(animationCounter > animationTime){
        EstadoAranha = P2;
        animationCounter = animationTime;
    }

}
