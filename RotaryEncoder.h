#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include "Driver.h"
#include <functional>

class RotaryEncoder : Driver
{
public:
    explicit RotaryEncoder(int aPin, int bPin, int swPin);

    int position() const { return this->_position; }
    void setRotaryCallback(std::function<void(int)> callback) { this->rotaryCallback = callback; }
    void setSwitchCallback(std::function<void(bool)> callback) { this->switchCallback = callback; }

private:
    void rotaryEventHandler(int gpio, uint32_t events);
    void switchEventHandler(int gpio, uint32_t events);
    const Pin& aPin() const { return this->pin(RotaryEncoder::_aIdx); }
    const Pin& bPin() const { return this->pin(RotaryEncoder::_bIdx); }
    const Pin& swPin() const { return this->pin(RotaryEncoder::_swIdx); }

    static constexpr int _aIdx = 0;
    static constexpr int _bIdx = 1;
    static constexpr int _swIdx = 2;

    std::function<void(int)> rotaryCallback;
    std::function<void(bool)> switchCallback;
    int _position;
    int _direction;
};

#endif // ROTARYENCODER_H
