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

    loadModel(path);

    children = new vector<Transform*>();

    Transform *newPart;

    newPart = new Transform();
    newPart->loadModel(path2);
    newPart->setColor(1,0,0);

    children->push_back(newPart);
}
