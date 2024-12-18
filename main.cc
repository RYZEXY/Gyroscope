#include <iostream>
#include "rotor.h"
#define M_PI 3.14159265358979323846
#include <cmath>

int main(){


    std::ofstream outFile("simulation_output.txt");

    if (!outFile) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    double mass = 0.1;               // kg
    double radius = 0.1;             // meters
    double initialAngularVelocity = 100.0; // rad/s
    double initialTiltAngle = M_PI / 4;    // 30 degrees in radians

    // Initial position vector (e.g., offset in x-direction)
    Vector3 initialPosition(1, 0, 1);
    initialPosition.phi = 0;
    initialPosition.theta = M_PI/4;
    // Create Rotor instance
    Rotor rotor(mass, radius, initialAngularVelocity, initialPosition, initialTiltAngle);
    double dt = 0.01;
    double time;
    
    std::cin >> time;

    for(int i = 0; i < (time/dt); i++){
        outFile<<"-------------------------"<<std::endl;
        outFile<<"t = "<<i*dt<<std::endl;

        rotor.update(dt, outFile);
    }

    outFile.close();
}