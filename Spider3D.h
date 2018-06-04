#ifndef SPIDER3D
#define SPIDER3D

#include "Transform.h"

class Spider3D : public Transform {

    public:
        Spider3D();
        Spider3D(Vector3 position, Vector3 scale, Vector3 rotation);

    protected:
        void finishConstruction();


};

#endif