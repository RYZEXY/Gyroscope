#ifndef MOTION_H
#define MOTION_H

#include "vector3.h"
#include <cmath>

class Motion {
    
    double phi(const Vector3& s);
    double theta(const Vector3& s);
    Vector3 Displcement(const Vector3& s1, const Vector3& s2);
    Vector3 AngularMomentum(const Vector3& omega, double I);
    Vector3 Torque(const Vector3& L1, const Vector3& L2, double dt);
    Vector3 Precession(const Vector3& tau, const Vector3& L);
    Vector3 updateOmega(const Vector3& omega, const Vector3& tau, double I, double dt);
    

};

#endif