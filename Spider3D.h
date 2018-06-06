#ifndef SPIDER3D
#define SPIDER3D

#include "Transform.h"

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

enum Estados {
    P1,P2,P3
};

class Spider3D : public Transform {

    public:
        Spider3D();
        Spider3D(Vector3 position, Vector3 scale, Vector3 rotation);
        void setColor(GLfloat r, GLfloat g, GLfloat b);
        void update(double delta);
        void turn(float axis);
        void advance(float axis);
        GLfloat animationTime = 0.5;
        GLfloat angularSpeed = 45;
        GLfloat fowardSpeed = 2;
        GLfloat axisRot = 0;
        GLfloat axisFow = 0;
        Estados currentState = P1;

    protected:
        void finishConstruction();
        void updateLegs(double delta);
        GLfloat animationCounter;

};

#endif