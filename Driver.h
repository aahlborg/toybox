#ifndef DRIVER_H
#define DRIVER_H

#include <vector>
#include "Pin.h"

class Driver
{
protected:
    Driver(std::vector<Pin> pins) :
        _pins(pins)
    {}
    const Pin& pin(int index) const { return this->_pins[index]; }

private:
    const std::vector<Pin> _pins;
};

#endif // DRIVER_H
