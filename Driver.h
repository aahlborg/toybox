#ifndef DRIVER_H
#define DRIVER_H

#include <vector>

class Driver
{
protected:
    Driver(std::vector<int> pins) :
        _pins(pins)
    {}
    int pin(int index) { return this->_pins.at(index); }

private:
    const std::vector<int> _pins;
};

#endif // DRIVER_H
