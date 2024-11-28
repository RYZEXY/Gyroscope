#include "../include/rotor.h"

void Rotor::update(double dt, std::ofstream& out){
    // Calculate the torque based on the current position and gravitational force
    tau = position.cross(Vector3(0, 0, -m * 9.81));
    out << "tau = " << tau << std::endl;

    // Calculate the precession angle increment
    double d_phi = omega_p * dt;
    out << "d_phi = " << d_phi << std::endl;

    // Rotate L by d_phi and update its components
    L.phi += d_phi;

    double magnitude = L.magnitude();
    L.x = magnitude * sin(L.theta) * cos(L.phi);
    L.y = magnitude * sin(L.theta) * sin(L.phi);
    L.z = magnitude * cos(L.theta);

    L.updateSphericalCoordinates();

    // Rotate Position by d_phi
    position.phi += d_phi;

    magnitude = position.magnitude();
    position.x = magnitude * sin(position.theta) * cos(position.phi);
    position.y = magnitude * sin(position.theta) * sin(position.phi);
    position.z = magnitude * cos(position.theta);

    position.updateSphericalCoordinates();


    out << "L = " << L << std::endl;
    out << "|L| = " << L.magnitude() << " L theta = " << L.theta << " L phi = " << L.phi << std::endl;


    out << "Position = " << position << " | Position Magnitude = " << position.magnitude() << std::endl;
}

void Rotor::update(double dt){
    
}