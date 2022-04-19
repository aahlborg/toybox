#ifndef PIN_H
#define PIN_H

#include <pico/stdlib.h>
#include <hardware/pwm.h>
#include <map>
#include <functional>


using IsrCallback_t = std::function<void(int, uint32_t)>;

enum PinFunction
{
    FN_OUTPUT,
    FN_PWM,
    FN_INPUT,
    FN_INPUT_ISR,
};

struct PwmParams
{
    int wrap_value;
    float clock_divider;
};


class Pin
{
public:
    Pin(int pin, PinFunction function);
    Pin(int pin, PinFunction function, PwmParams pwmParams);
    Pin(int pin, PinFunction function, uint32_t events);
    ~Pin();

    void setCallback(IsrCallback_t callback) const
    {
        assert(this->_function == FN_INPUT_ISR);
        Pin::callbackMap[this->_pin] = callback;
    }

    int pin() const { return this->_pin; }
    PinFunction function() const { return this->_function; }
    void set(int value) const { gpio_put(this->_pin, value); }
    void set_duty(int value) const { pwm_set_gpio_level(this->_pin, value); }
    bool get() const { return gpio_get(this->_pin); }

    static std::map<int, IsrCallback_t> callbackMap;

private:
    const int _pin;
    const PinFunction _function;
    const PwmParams _pwmParams;
};

#endif // PIN_H
