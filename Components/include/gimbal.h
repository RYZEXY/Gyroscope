#ifndef GIMBAL_H
#define GIMBAL_H

#include "component.h"
#include "vector3.h"
#include "rotor.h"

class Gimbal : public Component {

public:
    Vector3 axis;
    double angle;
    Gimbal *parent;
    Rotor *rotor;

    Gimbal(const Vector3& axis, Gimbal* parent = nullptr, Rotor *rotor = nullptr) : axis(axis), angle(0), parent(parent), rotor(rotor){};

    void rotate(double d_angle);
    void update(double dt);

    Vector3 getAxis() const;
    void setAxis(const Vector3& axis);
};

#endif
