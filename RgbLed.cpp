#include "RgbLed.h"


RgbLed::RgbLed(int redPin, int greenPin, int bluePin) :
    Driver({Pin(redPin, FN_PWM, {.wrap_value = 100, .clock_divider = 8.f}),
            Pin(greenPin, FN_PWM, {.wrap_value = 100, .clock_divider = 8.f}),
            Pin(bluePin, FN_PWM, {.wrap_value = 100, .clock_divider = 8.f})})
{}

void RgbLed::set_color(int red, int green, int blue)
{
    this->redPin().set_duty(red);
    this->greenPin().set_duty(green);
    this->bluePin().set_duty(blue);
}
