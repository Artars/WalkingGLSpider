#ifndef SPIDER
#define SPIDER

#include <GL/glut.h>
#include <cmath>
#include "Legs.h"

#define rad2Deg (180.0/3.141592653589793238463);

/*
P 1 caracteriza o estado quando ela está parada, e nenhuma perna se encontra em movimento. Tem-se duas
pernas mais compridas, denominadas “pernas externas”, e as pernas mais curtas, chamadas de “pernas inter-
nas”. As externas são responsáveis pelo impulso do cefalotórax e abdômen da aranha para frente, sendo as
mais internas utilizadas para controle e sustentação de seu corpo.
• P 2 indica o estado em que suas quatro pernas do lado direito do cefalotórax estão impulsionando o corpo para
frente, similar a quando bı́pedes estendem a perna direita para se moverem. Percebe-se que as duas pernas
mais “para fora” se estendem, ao passo que as duas pernas “para dentro” estão indo de encontro uma com a
outra. Do lado esquerdo do cefalotórax, porém, a situação é inversa: as duas pernas mais externas estão se
contraindo, indo de encontro às duas pernas mais internas que estão se estendendo.
• O movimento descrito em P 3 é exatamente o mesmo de P 2, porém acontecendo de maneira inversa - as pernas
externas do lado direito estão se contraindo, ao passo que as externas do lado esquerdo estão se estendendo.
– Portanto, a aranha, quando desenhada e não estiver caminhando em direção a um clique da cena, deve
permanecer de forma similar a P 1. Quando clica-se na cena para mover a aranha até aquela posição,
deve-se alternar entre P 2 e P 3 até alcançar o ponto de clique, aonde ela retornará ao estado P 1.
*/

enum EstadoAranha{
    P1,P2,P3
};

class Spider {
    GLfloat posX, posY, size, angSpeed, frontSpeed;
    GLfloat angleDir, angDegDir, direction[2];
    GLfloat angThreshold = 0.1, posThreshold = 2;	//Originalmente era 0.5, mas as vezes a figura simplesmente escapava do ponto
    int reachedAngle = 1, shouldMove = 0;
    GLfloat currAngleSpeed, targetAngle, targetX, targetY;
    GLfloat angleOffset = 3.14/2;
    Legs* legs[8];
    int EstadoAranha = P1;
    public:
        Spider (GLfloat x,GLfloat y,GLfloat s,GLfloat angS,GLfloat froS);
        void target(GLfloat x, GLfloat y);
        void update(double delta);
        void draw();
        void setPos(GLfloat x, GLfloat y) {posX = x; posY = y;};
    private:
        void drawEllipse(float posX, float posY, float radiusX, float radiusY, float r, float g, float b);
        void updateLegs(double delta);

};

#endif
