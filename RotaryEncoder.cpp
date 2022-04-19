#include "RotaryEncoder.h"
#include <pico/stdlib.h>
#include <functional>


RotaryEncoder::RotaryEncoder(int aPin, int bPin, int swPin) :
    Driver({Pin(aPin, FN_INPUT_ISR, GPIO_IRQ_EDGE_FALL),
            Pin(bPin, FN_INPUT),
            Pin(bPin, FN_INPUT_ISR, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE)}),
    _position(0),
    _direction(1)
{
    // TODO: Add pull option to Pin class
    gpio_set_pulls(this->aPin().pin(), true, false);
    gpio_set_pulls(this->swPin().pin(), true, false);
    this->aPin().setCallback(std::bind(&RotaryEncoder::rotaryEventHandler, this, std::placeholders::_1, std::placeholders::_2));
    this->swPin().setCallback(std::bind(&RotaryEncoder::switchEventHandler, this, std::placeholders::_1, std::placeholders::_2));
}

void RotaryEncoder::rotaryEventHandler(int gpio, uint32_t events)
{
    if (this->bPin().get())
    {
        this->_position += this->_direction;
    }
    else
    {
        this->_position -= this->_direction;
    }
    if (this->rotaryCallback)
    {
        // Notify user
        this->rotaryCallback(this->_position);
    }
}

void RotaryEncoder::switchEventHandler(int gpio, uint32_t events)
{
    if (this->switchCallback)
    {
        if (events & GPIO_IRQ_EDGE_FALL)
        {
            // Button pressed
            this->switchCallback(true);
        }
        else if (events & GPIO_IRQ_EDGE_RISE)
        {
            // Button released
            this->switchCallback(false);
        }
        else
        {
            // Unexpected
        }
    }
}
