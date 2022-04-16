#include "Pin.h"


std::map<int, std::function<void(uint32_t)>> Pin::callbackMap;

void isr_callback(uint gpio, uint32_t events)
{
    if (Pin::callbackMap.count(gpio) != 0)
    {
        Pin::callbackMap.at(gpio)(events);
    }
}

Pin::Pin(int pin, PinFunction function) :
    _pin(pin),
    _function(function),
    _pwmParams(),
    _isrParams()
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

Pin::Pin(int pin, PinFunction function, PwmParams pwmParams) :
    _pin(pin),
    _function(function),
    _pwmParams(pwmParams),
    _isrParams()
{
    // Only valid for PWM
    assert(FN_PWM == function);
    gpio_set_function(pin, GPIO_FUNC_PWM);
    pwm_set_wrap(pwm_gpio_to_slice_num(pin), pwmParams.wrap_value);
    pwm_set_clkdiv(pwm_gpio_to_slice_num(pin), pwmParams.clock_divider);
    pwm_set_enabled(pwm_gpio_to_slice_num(pin), true);
}

Pin::Pin(int pin, PinFunction function, std::function<void(uint32_t)> callback, uint32_t events) :
    _pin(pin),
    _function(function),
    _pwmParams(),
    _isrParams()
{
    // Only valid for INPUT
    assert(FN_INPUT == function);
    Pin::callbackMap[this->_pin] = callback;
    gpio_init(pin);
    gpio_set_irq_enabled_with_callback(this->_pin,
                                       events,
                                       true,
                                       &isr_callback);
}
