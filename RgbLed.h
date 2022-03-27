#ifndef RGBLED_H
#define RGBLED_H

#include "Driver.h"

class RgbLed : Driver
{
public:
    explicit RgbLed(int redPin, int greenPin, int bluePin);
    void set_color(int red, int green, int blue);

private:
    const int redPin() { return this->pin(RgbLed::_redIdx); }
    const int greenPin() { return this->pin(RgbLed::_greenIdx); }
    const int bluePin() { return this->pin(RgbLed::_blueIdx); }

    static constexpr int _redIdx = 0;
    static constexpr int _greenIdx = 1;
    static constexpr int _blueIdx = 2;
};

#endif // RGBLED_H
