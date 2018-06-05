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
    newPart = new Transform(Vector3(-0.2, -0.2, 0), Vector3(1,1,1), Vector3(-15,0,0));
    newPart->loadModel(path4);
    newPart->setColor(color[0],color[1],color[2]);
    children->push_back(newPart);
    newPart2 = new Transform(Vector3(0,-0.6,0),Vector3(1,1,1),Vector3(48,0,0));
    newPart2->loadModel(path4);
    newPart2->setColor(color[0],color[1],color[2]);
    newPart->children = new vector<Transform*>();
    newPart->children->push_back(newPart2);

    //Perna secundaria esquerda
    newPart = new Transform(Vector3(-0.05, -0.2, 0), Vector3(1,1,1), Vector3(-15,0,0));
    newPart->loadModel(path3);
    newPart->setColor(color[0],color[1],color[2]);
    children->push_back(newPart);
    newPart2 = new Transform(Vector3(0,-0.45,0),Vector3(1,1,1),Vector3(60,0,0));
    newPart2->loadModel(path3);
    newPart2->setColor(color[0],color[1],color[2]);
    newPart->children = new vector<Transform*>();
    newPart->children->push_back(newPart2);

    //Perna secundaria esquerda
    newPart = new Transform(Vector3(0.1, -0.2, 0), Vector3(1,1,1), Vector3(-15,0,0));
    newPart->loadModel(path3);
    newPart->setColor(color[0],color[1],color[2]);
    children->push_back(newPart);
    newPart2 = new Transform(Vector3(0,-0.45,0),Vector3(1,1,1),Vector3(60,0,0));
    newPart2->loadModel(path3);
    newPart2->setColor(color[0],color[1],color[2]);
    newPart->children = new vector<Transform*>();
    newPart->children->push_back(newPart2);

    //Perna Traseira esquerda
    newPart = new Transform(Vector3(0.25, -0.2, 0), Vector3(1,1,1), Vector3(-15,0,0));
    newPart->loadModel(path4);
    newPart->setColor(color[0],color[1],color[2]);
    children->push_back(newPart);
    newPart2 = new Transform(Vector3(0,-0.6,0),Vector3(1,1,1),Vector3(48,0,0));
    newPart2->loadModel(path4);
    newPart2->setColor(color[0],color[1],color[2]);
    newPart->children = new vector<Transform*>();
    newPart->children->push_back(newPart2);

    //Perna dianteira direita
    newPart = new Transform(Vector3(-0.2, 0.2, 0), Vector3(1,-1,1), Vector3(15,0,0));
    newPart->loadModel(path4);
    newPart->setColor(color[0],color[1],color[2]);
    children->push_back(newPart);
    newPart2 = new Transform(Vector3(0,-0.6,0),Vector3(1,1,1),Vector3(48,0,0));
    newPart2->loadModel(path4);
    newPart2->setColor(color[0],color[1],color[2]);
    newPart->children = new vector<Transform*>();
    newPart->children->push_back(newPart2);

    //Perna secundaria direita
    newPart = new Transform(Vector3(-0.05, 0.2, 0), Vector3(1,-1,1), Vector3(15,0,0));
    newPart->loadModel(path3);
    newPart->setColor(color[0],color[1],color[2]);
    children->push_back(newPart);
    newPart2 = new Transform(Vector3(0,-0.45,0),Vector3(1,1,1),Vector3(60,0,0));
    newPart2->loadModel(path3);
    newPart2->setColor(color[0],color[1],color[2]);
    newPart->children = new vector<Transform*>();
    newPart->children->push_back(newPart2);

    //Perna terciaria direita
    newPart = new Transform(Vector3(0.1, 0.2, 0), Vector3(1,-1,1), Vector3(15,0,0));
    newPart->loadModel(path3);
    newPart->setColor(color[0],color[1],color[2]);
    children->push_back(newPart);
    newPart2 = new Transform(Vector3(0,-0.45,0),Vector3(1,1,1),Vector3(60,0,0));
    newPart2->loadModel(path3);
    newPart2->setColor(color[0],color[1],color[2]);
    newPart->children = new vector<Transform*>();
    newPart->children->push_back(newPart2);

    //Perna traseira esquerda
    newPart = new Transform(Vector3(0.25, 0.2, 0), Vector3(1,-1,1), Vector3(15,0,0));
    newPart->loadModel(path4);
    newPart->setColor(color[0],color[1],color[2]);
    children->push_back(newPart);
    newPart2 = new Transform(Vector3(0,-0.6,0),Vector3(1,1,1),Vector3(48,0,0));
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

    if(axisRot == -1 && currentState == P1){
        currentState = P2;
    }
    else if (axisRot == 1 && currentState == P1) {
        currentState = P3;
    }
    if(axisFow != 0 && currentState == P1) {
        currentState = P2;
    }

    if(axisRot == 0 && axisFow == 0 && currentState != P1){
        /*if(currentState == P2){currentState == anteriorP2;}
        else if(currentState == P3){currentState == anteriorP3;}
        else*/ currentState = P1;    
    }

    updateLegs(delta);
}


void Spider3D::updateLegs(double delta) {
    float angularSpeed = M_PI/animationTime;
	float risingTime = (3.14)*(animationCounter/animationTime);
    int re2,fo2,re3,fo3;
	
	if(axisFow == -1){
        re2 = 0; fo2 = 1; re3 = 0; fo3 = 1;
    }
    else if(axisFow == 1){
        re2 = 1; fo2 = 0; re3 = 1; fo3 = 0;
    }
    else if(axisRot == -1){
        re2 = 0; fo2 = 1; re3 = 1; fo3 = 0;
    }
	else if(axisRot == 1){
        re2 = 1; fo2 = 0; re3 = 0; fo3 = 1;
    }

        
    if(currentState == P2){
	
		(*children)[1]->rotation = Vector3(-15,0,0)+Vector3(-15*sin(risingTime)*re2,0, +8*cos(angularSpeed * animationCounter));
		(*children)[2]->rotation = Vector3(-15,0,0)+Vector3(-15*sin(risingTime)*fo2,0, -4*cos(angularSpeed * animationCounter));
		(*children)[3]->rotation = Vector3(-15,0,0)+Vector3(-15*sin(risingTime)*re2,0, +4*cos(angularSpeed * animationCounter));
		(*children)[4]->rotation = Vector3(-15,0,0)+Vector3(-15*sin(risingTime)*fo2,0, -8*cos(angularSpeed * animationCounter));
		
		(*children)[5]->rotation = Vector3(15,0,0)+Vector3(15*sin(risingTime)*fo3,0, +8*cos(angularSpeed * animationCounter));
		(*children)[6]->rotation = Vector3(15,0,0)+Vector3(15*sin(risingTime)*re3,0, -4*cos(angularSpeed * animationCounter));
		(*children)[7]->rotation = Vector3(15,0,0)+Vector3(15*sin(risingTime)*fo3,0, +4*cos(angularSpeed * animationCounter));
		(*children)[8]->rotation = Vector3(15,0,0)+Vector3(15*sin(risingTime)*re3,0, -8*cos(angularSpeed * animationCounter));
		
        animationCounter -= delta/1000;
	}
    else if(currentState == P3){

		(*children)[1]->rotation = Vector3(-15,0,0)+Vector3(-15*sin(risingTime)*fo2,0, +8*cos(angularSpeed * animationCounter));
		(*children)[2]->rotation = Vector3(-15,0,0)+Vector3(-15*sin(risingTime)*re2,0, -4*cos(angularSpeed * animationCounter));
		(*children)[3]->rotation = Vector3(-15,0,0)+Vector3(-15*sin(risingTime)*fo2,0, +4*cos(angularSpeed * animationCounter));
		(*children)[4]->rotation = Vector3(-15,0,0)+Vector3(-15*sin(risingTime)*re2,0, -8*cos(angularSpeed * animationCounter));
		
		(*children)[5]->rotation = Vector3(15,0,0)+Vector3(15*sin(risingTime)*re3,0, +8*cos(angularSpeed * animationCounter));
		(*children)[6]->rotation = Vector3(15,0,0)+Vector3(15*sin(risingTime)*fo3,0, -4*cos(angularSpeed * animationCounter));
		(*children)[7]->rotation = Vector3(15,0,0)+Vector3(15*sin(risingTime)*re3,0, +4*cos(angularSpeed * animationCounter));
		(*children)[8]->rotation = Vector3(15,0,0)+Vector3(15*sin(risingTime)*fo3,0, -8*cos(angularSpeed * animationCounter));	
	
        animationCounter += delta/1000;
    }
    //Fazer suavização para o ponto de parada da animação
    else if(currentState == 1){    //(currentState == anteriorP2 || currentState == anteriorP3){
        int up2=fo2+re2, up3=fo3+re3;
        if(up2 > 1){up2=1;}
        if(up3 > 1){up3=1;}
        
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
        
        // if(currentState == anteriorP2){
        
        //     (*children)[1]->rotation = Vector3(-15,0,0)+Vector3(-15*sin(risingTime)*re2,0, +8*cos(angularSpeed * animationCounter));
        //     (*children)[2]->rotation = Vector3(-15,0,0)+Vector3(-15*sin(risingTime)*fo2,0, -4*cos(angularSpeed * animationCounter));
        //     (*children)[3]->rotation = Vector3(-15,0,0)+Vector3(-15*sin(risingTime)*re2,0, +4*cos(angularSpeed * animationCounter));
        //     (*children)[4]->rotation = Vector3(-15,0,0)+Vector3(-15*sin(risingTime)*fo2,0, -8*cos(angularSpeed * animationCounter));
            
        //     (*children)[5]->rotation = Vector3(15,0,0)+Vector3(15*sin(risingTime)*fo3,0, +8*cos(angularSpeed * animationCounter));
        //     (*children)[6]->rotation = Vector3(15,0,0)+Vector3(15*sin(risingTime)*re3,0, -4*cos(angularSpeed * animationCounter));
        //     (*children)[7]->rotation = Vector3(15,0,0)+Vector3(15*sin(risingTime)*fo3,0, +4*cos(angularSpeed * animationCounter));
        //     (*children)[8]->rotation = Vector3(15,0,0)+Vector3(15*sin(risingTime)*re3,0, -8*cos(angularSpeed * animationCounter));
        // }
        // else if(currentState == anteriorP3){
        //     (*children)[1]->rotation = Vector3(-15,0,0)+Vector3(-15*sin(risingTime)*fo2,0, +8*cos(angularSpeed * animationCounter));
        //     (*children)[2]->rotation = Vector3(-15,0,0)+Vector3(-15*sin(risingTime)*re2,0, -4*cos(angularSpeed * animationCounter));
        //     (*children)[3]->rotation = Vector3(-15,0,0)+Vector3(-15*sin(risingTime)*fo2,0, +4*cos(angularSpeed * animationCounter));
        //     (*children)[4]->rotation = Vector3(-15,0,0)+Vector3(-15*sin(risingTime)*re2,0, -8*cos(angularSpeed * animationCounter));
            
        //     (*children)[5]->rotation = Vector3(15,0,0)+Vector3(15*sin(risingTime)*re3,0, +8*cos(angularSpeed * animationCounter));
        //     (*children)[6]->rotation = Vector3(15,0,0)+Vector3(15*sin(risingTime)*fo3,0, -4*cos(angularSpeed * animationCounter));
        //     (*children)[7]->rotation = Vector3(15,0,0)+Vector3(15*sin(risingTime)*re3,0, +4*cos(angularSpeed * animationCounter));
        //     (*children)[8]->rotation = Vector3(15,0,0)+Vector3(15*sin(risingTime)*fo3,0, -8*cos(angularSpeed * animationCounter));	
        // }

        // if(animationCounter == 0){currentState = P1;}
    }
	
	if(animationCounter < 0){
        currentState = P3;
        animationCounter = 0;
    }

    if(animationCounter > animationTime){
        currentState = P2;
        animationCounter = animationTime;
    }

}
