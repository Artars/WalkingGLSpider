#include "Transform.h"

Transform::Transform() {
    position = Vector3();
    scale = Vector3(1,1,1);
    rotation = Vector3();
}


Transform::Transform(Vector3 position, Vector3 scale, Vector3 rotation) {
    this->position = Vector3(position);
    this->scale = Vector3(scale);
    this->rotation = Vector3(rotation);
    

}


void Transform::addChild(Transform *newChild) {
    if(children == NULL) {
        children = new vector<Transform*>();
        children->push_back(newChild);
    }
}

Transform* Transform::getChild(int i) {
    if(children == NULL) {
        if(children->size() > i)
            return (*children)[i];
    }
    return NULL;
}

void Transform::setColor(GLfloat r, GLfloat g, GLfloat b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;    
}


void Transform::draw() {

    GLfloat angle = rotation.length();
    Vector3 rotDir = Vector3(rotation);
    rotDir.normalize();

    glPushMatrix();
    glTranslatef(position.x,position.y, position.z);    //Cria uma matriz de transforma��es: transla��o para origem, rota��o e transla��o de volta ao local incial
    glRotatef(angle,rotDir.x,rotDir.y,rotDir.z);
    glScalef(scale.x,scale.y,scale.z);

    //Draw children
    if(children != NULL)
        for (std::vector<Transform*>::iterator it = children->begin(); it != children->end(); ++it)
            (*it)->draw();

    drawItself();

    glPopMatrix();

}

void Transform::drawItself() {

    glColor3f(color[0],color[1],color[2]);

    if(hasMesh){
        int i = 0;
        glBegin(GL_TRIANGLE_FAN);
        for(std::vector<unsigned int>::iterator it = faces->begin(); it != faces->end(); ++it){
            Vector3 vert = (*vertices)[*it-1];
            glVertex3f(vert.x,vert.y,vert.z);
        }
        glEnd();
    }
}

int Transform::loadModel(char *path) {
    Objector *o = new Objector();
    int result = o->parseFile(path);
    if(result == -1){
        exit(-1);
    }
    else if(result == 1){
        if(vertices != NULL)
            free(vertices);
        vertices = o->vertices;
        if(faces != NULL)
            free(faces);
        faces = o->faces;
        hasMesh = true;
        for(std::vector<unsigned int>::iterator it = faces->begin(); it != faces->end(); ++it){
            Vector3 vert = (*vertices)[*it-1];
        }
    }

}