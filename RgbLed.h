#ifndef RGBLED_H
#define RGBLED_H

#include <pico/types.h>

class RgbLed
{
public:
    explicit RgbLed(uint redPin, uint greenPin, uint bluePin);
    void set_color(uint red, uint green, uint blue);

private:
    uint _redPin;
    uint _greenPin;
    uint _bluePin;
};

#endif // RGBLED_H
