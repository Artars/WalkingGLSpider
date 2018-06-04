#ifndef TRANSFORM
#define TRANSFORM

#include "Vector3.h"
#include <GL/glut.h>
#include <vector>
#include "Objector.h"

#define rad2Deg 57.295779513

class Transform{
    public:
        Transform();
        Transform(Vector3 position, Vector3 scale, Vector3 rotation);
        Vector3 position;
        Vector3 scale;
        Vector3 rotation;
        Transform *getChild(int i);
        void addChild(Transform *newChild);
        void draw();
        int loadModel(char *path);
        void setColor(GLfloat r, GLfloat g, GLfloat b);
        vector<Transform*> *children = NULL;        
    protected:
        GLfloat color[3];
        void drawItself();
        vector<Vector3> *vertices = NULL;
        vector<unsigned int> *faces = NULL;
        bool hasMesh = false;

};

#endif