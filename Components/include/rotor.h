#ifndef ROTOR_H
#define ROTOR_H

#include "component.h"
#include "vector3.h"
#include <iostream>
#include <fstream>

class Rotor : public Component {

    Vector3 L, tau;
    double tilt, omega_p;

public:
    Rotor(){};
Rotor(double m, double r, double omega_i, const Vector3& pos_i, double tilt_i) : tilt(tilt_i) {
    this->m = m;
    this->r = r;
    this->omega = omega_i;
    this->position = pos_i;
    this->I = 0.5 * m * r * r;

    std::cout << "Mass (m): " << m << ", Radius (r): " << r << ", Angular Velocity (omega): " << omega << std::endl;
    std::cout << "Position: " << position << std::endl;
    std::cout << "Moment of Inertia (I): " << I << std::endl;

    Vector3 r_hat = Vector3(sin(tilt), 0, cos(tilt)).normalize();
    std::cout << "Direction vector (r_hat): " << r_hat << std::endl;

    L = r_hat * (I * omega);
    std::cout << "Angular Momentum (L): " << L << std::endl;

    tau = position.cross(Vector3(0, 0, -m * 9.81));
    std::cout << "Torque (tau): " << tau << std::endl;

    if (L.magnitude() != 0) {
        omega_p = tau.magnitude() / (L.magnitude() * sin(tilt));
        std::cout << "Precession Angular Velocity (omega_p): " << omega_p << std::endl;
    } 
    else {
        omega_p = 0;
    }
    position.updateSphericalCoordinates();
    L.updateSphericalCoordinates();
}
    friend class Gimbal;
    
    void update(double deltaTime, std::ofstream &out);
    virtual void update(double deltaTime);
};

#endif
