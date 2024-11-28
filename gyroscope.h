#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include "Components/include/base.h"
#include "Components/include/rotor.h"
#include "Components/include/gimbal.h"
#include "Components/include/spine_axel.h"
#include "Physics/include/vector3.h"

class Gyroscope {
private:
    Rotor rotor;
    Gimbal gimbal;

public:
    Gyroscope();
    void update(double deltaTime);  // Call update on all components
};

#endif
