#include "RgbLed.h"
#include <pico/stdlib.h>
#include <hardware/pwm.h>


RgbLed::RgbLed(int redPin, int greenPin, int bluePin) :
    Driver({redPin, greenPin, bluePin})
{
    gpio_set_function(this->redPin(), GPIO_FUNC_PWM);
    gpio_set_function(this->greenPin(), GPIO_FUNC_PWM);
    gpio_set_function(this->bluePin(), GPIO_FUNC_PWM);
    pwm_set_wrap(pwm_gpio_to_slice_num(this->redPin()), 100);
    pwm_set_wrap(pwm_gpio_to_slice_num(this->greenPin()), 100);
    pwm_set_wrap(pwm_gpio_to_slice_num(this->bluePin()), 100);
    pwm_set_clkdiv(pwm_gpio_to_slice_num(this->redPin()), 8.f);
    pwm_set_clkdiv(pwm_gpio_to_slice_num(this->greenPin()), 8.f);
    pwm_set_clkdiv(pwm_gpio_to_slice_num(this->bluePin()), 8.f);
    pwm_set_enabled(pwm_gpio_to_slice_num(this->redPin()), true);
    pwm_set_enabled(pwm_gpio_to_slice_num(this->greenPin()), true);
    pwm_set_enabled(pwm_gpio_to_slice_num(this->bluePin()), true);
}

void RgbLed::set_color(int red, int green, int blue)
{
    pwm_set_gpio_level(this->redPin(), red);
    pwm_set_gpio_level(this->greenPin(), green);
    pwm_set_gpio_level(this->bluePin(), blue);
}
