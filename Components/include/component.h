#ifndef COMPONENT_H
#define COMPONENT_H
#include "../../Physics/include/vector3.h"

class Component {
protected:
    double m,r,I;
    double theta,phi, omega;   
    Vector3 position;
public:
    virtual void update(double dt) = 0; 
    virtual ~Component() = default; 
};

#endif
