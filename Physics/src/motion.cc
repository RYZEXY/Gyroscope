#include "../include/motion.h"

double Motion::phi(const Vector3& s){
    return std::atan(s.y/s.x);
}

double Motion::theta(const Vector3& s){
    if(s.magnitude()==0){
        return 0;
    }
    return std::acos(s.z/s.magnitude());
}

Vector3 Motion::Displcement(const Vector3& s1, const Vector3& s2){

    return s2-s1;

}

Vector3 Motion::AngularMomentum(const Vector3& omega, double I){

    return omega*I;

}

Vector3 Motion::Torque(const Vector3& L1, const Vector3& L2, double dt){

    return (L2 - L1)/dt;

}

Vector3 Motion::Precession(const Vector3& tau, const Vector3& L){

    if(L.magnitude()==0){
        return Vector3(0,0,0);
    }

    return tau/L.magnitude();

}

Vector3 Motion::updateOmega(const Vector3& omega, const Vector3& tau, double I, double dt){

    Vector3 alpha = tau/I;

    return omega + alpha * dt;

}