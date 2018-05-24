#include "Vector3.h"

Vector3::Vector3(float newX, float newY, float newZ) {
    x = newX;
    y = newY;
    z = newZ;
}

Vector3::Vector3(const Vector3& v) {       
    x = v.x;
    y = v.y;
    z = v.z;
}

Vector3::Vector3(){
    x = y = z = 0;
}

ostream& operator<<(ostream& os, const Vector3& v) {
    return os << "X: " << v.x << "; Y: " << v.y << "; Z: " << v.z << endl;
}

Vector3 Vector3::operator+(const Vector3& v) {
    Vector3 result;
    result.x = this->x + v.x;
    result.y = this->y + v.y;
    result.z = this->z + v.z;
    return result;
}

Vector3 Vector3::operator-(const Vector3& v) {
    Vector3 result;
    result.x = this->x - v.x;
    result.y = this->y - v.y;
    result.z = this->z - v.z;
    return result;
}
Vector3 Vector3::operator*(const Vector3& v){
    Vector3 result;
    result.x = this->x * v.x;
    result.y = this->y * v.y;
    result.z = this->z * v.z;
    return result;
}
Vector3 Vector3::operator/(const Vector3& v) {
    Vector3 result;
    result.x = this->x / v.x;
    result.y = this->y / v.y;
    result.z = this->z / v.z;
    return result;
}
Vector3 Vector3::operator*(const float& f) {
    Vector3 result;
    result.x = this->x * f;
    result.y = this->y * f;
    result.z = this->z * f;
    return result;
}
Vector3 Vector3::operator/(const float& f) {
    Vector3 result;
    result.x = this->x / f;
    result.y = this->y / f;
    result.z = this->z / f;
    return result;
}
void Vector3::operator=(const Vector3& v) {
    x = v.x;
    y = v.y;
    z = v.z;
}
void Vector3::normalize() {
    float lenght = length();
    x /= lenght;
    y /= lenght;
    z /= lenght;
}
float Vector3::squaredLength() {
    return (x*x+y*y+z*z);
}
float Vector3::length(){
    return sqrt(squaredLength());
}

Vector3 Vector3::cross(Vector3 v) {
    Vector3 result;
    result.x = this->y * v.z - this->z * v.y;
    result.y = this->x * v.z - this->z * v.x;
    result.z = this->x * v.y - this->y * v.x;
    return result;
}

float Vector3::dot(Vector3 v) {
    return (this->x * v.x + this->y * v.y + this->z * v.z);
}

Vector3 Vector3::normalized() {
    Vector3 result = Vector3(*this);
    result.normalize();
    return result;
}
