#include "Spider3D.h"

Spider3D::Spider3D(){
    finishConstruction();
}

Spider3D::Spider3D(Vector3 position, Vector3 scale, Vector3 rotation){
    this->position = position;
    this->scale = scale;
    this->rotation = rotation;

    finishConstruction();
}

void Spider3D::finishConstruction() {
    char path[] = "SBody.obj";
    char path2[] = "SEyes.obj";
    char path3[] = "SLeg2.obj";
    char path4[] = "SLeg1.obj";
    

    loadModel(path);

    children = new vector<Transform*>();

    Transform *newPart, *newPart2;

    newPart = new Transform();
    newPart->loadModel(path2);
    newPart->setColor(1,0,0);

    children->push_back(newPart);


    //Perna dianteira esquerda
    newPart = new Transform(Vector3(-0.2, -0.2, 0), Vector3(1,1,1), Vector3(-30,0,0));
    newPart->loadModel(path4);
    newPart->setColor(color[0],color[1],color[2]);
    children->push_back(newPart);
    newPart2 = new Transform(Vector3(0,-0.6,0),Vector3(1,1,1),Vector3(60,0,0));
    newPart2->loadModel(path4);
    newPart2->setColor(color[0],color[1],color[2]);
    newPart->children = new vector<Transform*>();
    newPart->children->push_back(newPart2);

    //Perna secundaria esquerda
    newPart = new Transform(Vector3(-0.05, -0.2, 0), Vector3(1,1,1), Vector3(-30,0,0));
    newPart->loadModel(path3);
    newPart->setColor(color[0],color[1],color[2]);
    children->push_back(newPart);
    newPart2 = new Transform(Vector3(0,-0.45,0),Vector3(1,1,1),Vector3(60,0,0));
    newPart2->loadModel(path3);
    newPart2->setColor(color[0],color[1],color[2]);
    newPart->children = new vector<Transform*>();
    newPart->children->push_back(newPart2);

    //Perna secundaria esquerda
    newPart = new Transform(Vector3(0.1, -0.2, 0), Vector3(1,1,1), Vector3(-30,0,0));
    newPart->loadModel(path3);
    newPart->setColor(color[0],color[1],color[2]);
    children->push_back(newPart);
    newPart2 = new Transform(Vector3(0,-0.45,0),Vector3(1,1,1),Vector3(60,0,0));
    newPart2->loadModel(path3);
    newPart2->setColor(color[0],color[1],color[2]);
    newPart->children = new vector<Transform*>();
    newPart->children->push_back(newPart2);

    //Perna Traseira esquerda
    newPart = new Transform(Vector3(0.25, -0.2, 0), Vector3(1,1,1), Vector3(-30,0,0));
    newPart->loadModel(path4);
    newPart->setColor(color[0],color[1],color[2]);
    children->push_back(newPart);
    newPart2 = new Transform(Vector3(0,-0.6,0),Vector3(1,1,1),Vector3(60,0,0));
    newPart2->loadModel(path4);
    newPart2->setColor(color[0],color[1],color[2]);
    newPart->children = new vector<Transform*>();
    newPart->children->push_back(newPart2);

    //Perna dianteira direita
    newPart = new Transform(Vector3(-0.2, 0.2, 0), Vector3(1,-1,1), Vector3(30,0,0));
    newPart->loadModel(path4);
    newPart->setColor(color[0],color[1],color[2]);
    children->push_back(newPart);
    newPart2 = new Transform(Vector3(0,-0.6,0),Vector3(1,1,1),Vector3(60,0,0));
    newPart2->loadModel(path4);
    newPart2->setColor(color[0],color[1],color[2]);
    newPart->children = new vector<Transform*>();
    newPart->children->push_back(newPart2);

    //Perna secundaria direita
    newPart = new Transform(Vector3(-0.05, 0.2, 0), Vector3(1,-1,1), Vector3(30,0,0));
    newPart->loadModel(path3);
    newPart->setColor(color[0],color[1],color[2]);
    children->push_back(newPart);
    newPart2 = new Transform(Vector3(0,-0.45,0),Vector3(1,1,1),Vector3(60,0,0));
    newPart2->loadModel(path3);
    newPart2->setColor(color[0],color[1],color[2]);
    newPart->children = new vector<Transform*>();
    newPart->children->push_back(newPart2);

    //Perna terciaria direita
    newPart = new Transform(Vector3(0.1, 0.2, 0), Vector3(1,-1,1), Vector3(30,0,0));
    newPart->loadModel(path3);
    newPart->setColor(color[0],color[1],color[2]);
    children->push_back(newPart);
    newPart2 = new Transform(Vector3(0,-0.45,0),Vector3(1,1,1),Vector3(60,0,0));
    newPart2->loadModel(path3);
    newPart2->setColor(color[0],color[1],color[2]);
    newPart->children = new vector<Transform*>();
    newPart->children->push_back(newPart2);

    //Perna traseira esquerda
    newPart = new Transform(Vector3(0.25, 0.2, 0), Vector3(1,-1,1), Vector3(30,0,0));
    newPart->loadModel(path4);
    newPart->setColor(color[0],color[1],color[2]);
    children->push_back(newPart);
    newPart2 = new Transform(Vector3(0,-0.6,0),Vector3(1,1,1),Vector3(60,0,0));
    newPart2->loadModel(path4);
    newPart2->setColor(color[0],color[1],color[2]);
    newPart->children = new vector<Transform*>();
    newPart->children->push_back(newPart2);





}

void Spider3D::setColor(GLfloat r, GLfloat g, GLfloat b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;    

    int i;
    if(children != NULL){
        for(i = 1; i < children->size(); i++){
            (*children)[i]->setColor(r,g,b);
            (*(*children)[i]->children)[0]->setColor(r,g,b);            
        }
    }
}

void Spider3D::turn(float axis) {
    axisRot = axis;
}

void Spider3D::advance(float axis) {
    axisFow = axis;
}

void Spider3D::update(double delta){
    float angleVar = angularSpeed * axisRot * delta/1000;
    rotation = rotation + Vector3(0,0,angleVar);

    float deltaPos = fowardSpeed * axisFow * delta/1000;
    Vector3 deltaPosition = Vector3(cos(rotation.z/rad2Deg)*deltaPos,sin(rotation.z/rad2Deg)*deltaPos,0);
	position = position + deltaPosition;
    /*
    if (!reachedAngle) {		//Realiza c�lculo de �ngulo a ser encontrado
        angleDir += currAngleSpeed * delta/1000;
        float delta = angleDir - targetAngle;
        if(std::abs(delta) <= angThreshold){
            reachedAngle = 1;
            shouldMove = 1;
            angleDir = targetA2ngle;
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
    */
}


void Spider3D::updateLegs(double delta) {
    float angularSpeed = M_PI/animationTime;
}
