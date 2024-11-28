#include "../include/vector3.h"


Vector3 Vector3::operator+(const Vector3& o) const{

    return Vector3(x+o.x, y+o.y, z+o.z);

}
Vector3 Vector3::operator-(const Vector3& o) const{

    return Vector3(x-o.x, y-o.y, z-o.z);

}
Vector3 Vector3::operator*(double scalar) const{

    return Vector3(x*scalar, y*scalar, z*scalar);

}
Vector3 Vector3::operator/(double scalar) const{

    return Vector3(x/scalar, y/scalar, z/scalar);

}
Vector3& Vector3::operator=(const Vector3& other){
    x=other.x;
    y=other.y;
    z=other.z;
    return *this;

}
double Vector3::dot(const Vector3& o) const{

    return x*o.x + y*o.y + z*o.z;

}
Vector3 Vector3::cross(const Vector3& o) const{

    return Vector3(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);

}
double Vector3::magnitude() const{

    return std::sqrt(x * x + y * y + z * z);

}
Vector3 Vector3::normalize() const{

    double mag = magnitude();

    if (mag == 0){
        return Vector3(0, 0, 0); 
    }
    
    return Vector3(x / mag, y / mag, z / mag);

}

void Vector3::updateSphericalCoordinates() {
    phi = std::atan2(y,x);
    theta = (magnitude() == 0) ? 0 : std::acos(z / magnitude());
}

Vector3 Vector3::rotateAround(const Vector3& axis, double angle) const {
    Vector3 k = axis.normalize();
    return *this * cos(angle) + k.cross(*this) * sin(angle) + k * k.dot(*this) * (1 - cos(angle));
}