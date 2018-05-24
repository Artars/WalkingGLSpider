#ifndef VECTOR3
#define VECTOR3

#include <cmath>
#include <iostream>
using namespace std;

class Vector3 {
    public:
        float x,y,z;
        Vector3(const Vector3& v);        
        Vector3(float newX, float newY, float newZ);
        Vector3();
        friend ostream& operator<<(ostream& os, const Vector3& v);
        Vector3 operator+(const Vector3& v);
        Vector3 operator-(const Vector3& v);
        Vector3 operator*(const Vector3& v);
        Vector3 operator/(const Vector3& v);
        Vector3 operator*(const float& f);
        Vector3 operator/(const float& f);
        void operator=(const Vector3& v);
        void normalize();
        float squaredLength();
        float length();
        Vector3 cross(Vector3 v);
        float dot(Vector3 v);
        Vector3 normalized();
};

ostream& operator<<(ostream& os, const Vector3& v);

#endif

    