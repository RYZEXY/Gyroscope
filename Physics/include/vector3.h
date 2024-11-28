#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>
#include <cmath>

class Vector3 {

    protected:
        

    public: 
        
        Vector3(): x(0), y(0), z(0){};
        Vector3(double x, double y, double z): x{x}, y{y}, z{z}, phi{std::atan(y/x)}, theta{magnitude()==0 ? 0 : std::acos(z/magnitude())} {};
        Vector3(const Vector3 &other){
            this->x=other.x;
            this->y=other.y;
            this->z=other.z;
            this->phi=other.phi;
            this->theta=other.theta;
        }

        Vector3 operator+(const Vector3& other) const;
        Vector3 operator-(const Vector3& other) const;
        Vector3 operator*(double scalar) const;
        Vector3 operator/(double scalar) const;
        Vector3& operator=(const Vector3& other);
        double dot(const Vector3& other) const;
        Vector3 cross(const Vector3& other) const;
        double magnitude() const;
        Vector3 normalize() const;
        void updateSphericalCoordinates();
        Vector3 rotateAround(const Vector3& axis, double angle) const;
        double x,y,z,phi,theta;

        friend std::ostream& operator<<(std::ostream& out, const Vector3& vec) {
            out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
            return out;
        }
        
        friend class Motion;
        friend class Rotor;
};

#endif