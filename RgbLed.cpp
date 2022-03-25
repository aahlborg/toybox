#include "RgbLed.h"
#include <pico/stdlib.h>
#include <hardware/pwm.h>


RgbLed::RgbLed(uint redPin, uint greenPin, uint bluePin)
{
    this->_redPin = redPin;
    this->_greenPin = greenPin;
    this->_bluePin = bluePin;

    gpio_set_function(this->_redPin, GPIO_FUNC_PWM);
    gpio_set_function(this->_greenPin, GPIO_FUNC_PWM);
    gpio_set_function(this->_bluePin, GPIO_FUNC_PWM);
    pwm_set_wrap(pwm_gpio_to_slice_num(this->_redPin), 100);
    pwm_set_wrap(pwm_gpio_to_slice_num(this->_greenPin), 100);
    pwm_set_wrap(pwm_gpio_to_slice_num(this->_bluePin), 100);
    pwm_set_clkdiv(pwm_gpio_to_slice_num(this->_redPin), 8.f);
    pwm_set_clkdiv(pwm_gpio_to_slice_num(this->_greenPin), 8.f);
    pwm_set_clkdiv(pwm_gpio_to_slice_num(this->_bluePin), 8.f);
    pwm_set_enabled(pwm_gpio_to_slice_num(this->_redPin), true);
    pwm_set_enabled(pwm_gpio_to_slice_num(this->_greenPin), true);
    pwm_set_enabled(pwm_gpio_to_slice_num(this->_bluePin), true);
}

void RgbLed::set_color(uint red, uint green, uint blue)
{
    pwm_set_gpio_level(this->_redPin, red);
    pwm_set_gpio_level(this->_greenPin, green);
    pwm_set_gpio_level(this->_bluePin, blue);
}
