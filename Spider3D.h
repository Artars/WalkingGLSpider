#ifndef SPIDER3D
#define SPIDER3D

#include "Transform.h"

class Spider3D : public Transform {

    public:
        Spider3D();
        Spider3D(Vector3 position, Vector3 scale, Vector3 rotation);
        void setColor(GLfloat r, GLfloat g, GLfloat b);
        void update(double delta);
        void turn(float axis);
        void advance(float axis);
        GLfloat animationTime = 1;
        GLfloat angularSpeed = 30;
        GLfloat fowardSpeed = 1;
        GLfloat axisRot = 0;
        GLfloat axisFow = 0;

    protected:
        void finishConstruction();
        void updateLegs(double delta);

};

#endif