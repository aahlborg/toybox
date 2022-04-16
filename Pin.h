#ifndef PIN_H
#define PIN_H

#include <pico/stdlib.h>
#include <hardware/pwm.h>
#include <map>
#include <functional>

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

struct InputIsrParams
{
    std::function<void(uint32_t)> callback;
    uint32_t events;
};

// GPIO ISR callback function
void isr_callback(uint gpio, uint32_t events);

class Pin
{
public:
    Pin(int pin, PinFunction function);
    Pin(int pin, PinFunction function, PwmParams pwmParams);
    Pin(int pin, PinFunction function, std::function<void(uint32_t)> callback, uint32_t events);

    ~Pin()
    {
        // Remove callback references
        Pin::callbackMap.erase(this->_pin);
    }

    // TODO: Violates constness since Pin is reconfigured
    void setCallback(std::function<void(uint32_t)> callback, uint32_t events) const
    {
        // Only valid for INPUT
        assert(this->_function == FN_INPUT);
        Pin::callbackMap[this->_pin] = callback;
        gpio_set_irq_enabled_with_callback(this->_pin,
                                           events,
                                           true,
                                           &isr_callback);
    }

    int pin() const { return this->_pin; }
    void set(int value) const { gpio_put(this->_pin, value); }
    void set_duty(int value) const { pwm_set_gpio_level(this->_pin, value); }

    static std::map<int, std::function<void(uint32_t)>> callbackMap;

private:
    const int _pin;
    const PinFunction _function;
    const PwmParams _pwmParams;
    const InputIsrParams _isrParams;
};

#endif // PIN_H
