#include "../include/gimbal.h"

void Gimbal::rotate(double d_angle){
    angle+=d_angle;
}

void Gimbal::update(double dt){

    Vector3 L_rotor = rotor->L;
    double d_angle = L_rotor.dot(axis) * dt;
    rotate(d_angle);

    if(parent){
        parent->update(dt);
    }

}