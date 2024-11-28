#ifndef BASE_H
#define BASE_H

#include "component.h"

class Base : public Component {
public:
    Base(double mass, double rad) {
        m = mass;
        r = rad;
        I = 0.5 * m * r * r;
    };
    void update(double deltaTime) override;
};

#endif
