#ifndef PIN_H
#define PIN_H

#include <pico/stdlib.h>
#include <hardware/pwm.h>

enum PinFunction
{
    FN_OUTPUT,
    FN_PWM,
    FN_INPUT,
};

struct PwmParams
{
    int wrap_value;
    float clock_divider;
};

class Pin
{
public:
    Pin(int pin, PinFunction function) :
        _pin(pin),
        _function(function),
        _pwmParams()
    {
        switch (function)
        {
        case FN_OUTPUT:
            gpio_init(pin);
            gpio_set_dir(pin, GPIO_OUT);
            break;
        case FN_PWM:
            gpio_set_function(pin, GPIO_FUNC_PWM);
            pwm_set_enabled(pwm_gpio_to_slice_num(pin), true);
            break;
        case FN_INPUT:
            gpio_init(pin);
            gpio_set_dir(pin, GPIO_IN);
            break;
        default:
            assert(false);
        }
    }

    Pin(int pin, PinFunction function, PwmParams pwmParams) :
        _pin(pin),
        _function(function),
        _pwmParams(pwmParams)
    {
        // Only valid for PWM
        assert(FN_PWM == function);
        gpio_set_function(pin, GPIO_FUNC_PWM);
        pwm_set_wrap(pwm_gpio_to_slice_num(pin), pwmParams.wrap_value);
        pwm_set_clkdiv(pwm_gpio_to_slice_num(pin), pwmParams.clock_divider);
        pwm_set_enabled(pwm_gpio_to_slice_num(pin), true);
    }

    int pin() const { return this->_pin; }
    void set(int value) const { gpio_put(this->_pin, value); }
    void set_duty(int value) const { pwm_set_gpio_level(this->_pin, value); }

private:
    const int _pin;
    const PinFunction _function;
    const PwmParams _pwmParams;
};

#endif // PIN_H