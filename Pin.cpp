#include "Pin.h"


// Maps pins to callback functions
std::map<int, IsrCallback_t> Pin::callbackMap;

// Global ISR callback router
void isr_callback(uint gpio, uint32_t events)
{
    if (Pin::callbackMap.count(gpio) != 0)
    {
        Pin::callbackMap.at(gpio)(gpio, events);
    }
}

// Set up simple I/O or PWM
Pin::Pin(int pin, PinFunction function) :
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

// Set up PWM with parameters
Pin::Pin(int pin, PinFunction function, PwmParams pwmParams) :
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

// Set up input with ISR callback
Pin::Pin(int pin, PinFunction function, uint32_t events) :
    _pin(pin),
    _function(function),
    _pwmParams()
{
    // Only valid for INPUT_ISR
    assert(FN_INPUT_ISR == function);
    gpio_init(pin);
    gpio_set_irq_enabled_with_callback(this->_pin,
                                       events,
                                       true,
                                       &isr_callback);
}

// Disable gpio
Pin::~Pin()
{
    /*if (FN_INPUT_ISR == this->_function)
    {
        // Disable ISR
        gpio_set_irq_enabled(this->_pin, 0, false);
        // Remove callback references
        Pin::callbackMap.erase(this->_pin);
    }
    else if (FN_PWM == this->_function)
    {
        // Disable PWM
        pwm_set_enabled(pwm_gpio_to_slice_num(this->_pin), false);
    }
    // Disable I/O
    gpio_set_dir(this->_pin, GPIO_IN);
    gpio_set_input_enabled(this->_pin, false);*/
}
