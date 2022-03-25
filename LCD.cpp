#include "LCD.h"
#include <pico/stdlib.h>
#include <hardware/pwm.h>


LCD::LCD(uint d4, uint d5, uint d6, uint d7, uint en, uint rs, uint v0)
{
    this->_d4Pin = d4;
    this->_d5Pin = d5;
    this->_d6Pin = d6;
    this->_d7Pin = d7;
    this->_enPin = en;
    this->_rsPin = rs;
    this->_v0Pin = v0;

    gpio_init(this->_d4Pin);
    gpio_init(this->_d5Pin);
    gpio_init(this->_d6Pin);
    gpio_init(this->_d7Pin);
    gpio_init(this->_enPin);
    gpio_init(this->_rsPin);
    gpio_set_dir(this->_d4Pin, GPIO_OUT);
    gpio_set_dir(this->_d5Pin, GPIO_OUT);
    gpio_set_dir(this->_d6Pin, GPIO_OUT);
    gpio_set_dir(this->_d7Pin, GPIO_OUT);
    gpio_set_dir(this->_enPin, GPIO_OUT);
    gpio_set_dir(this->_rsPin, GPIO_OUT);

    // V0 PWM signal
    gpio_set_function(this->_v0Pin, GPIO_FUNC_PWM);
    pwm_set_wrap(pwm_gpio_to_slice_num(this->_v0Pin), 100);
    pwm_set_clkdiv(pwm_gpio_to_slice_num(this->_v0Pin), 8.f);
    pwm_set_enabled(pwm_gpio_to_slice_num(this->_v0Pin), true);
}

void LCD::init(void)
{
    gpio_put(this->_rsPin, 0);
    // Set interface 8-bit
    this->send4(0b0011);
    // Set interface 8-bit
    this->send4(0b0011);
    // Set interface 8-bit
    this->send4(0b0011);
    // Set interface 4-bit
    this->send4(0b0010);
    // Set interface 4-bit, 2-lines, 5x8 font
    this->send8(0b00101000);
    // Set display on, cursor off
    this->send8(0b00001100);
    // Increment cursor, no shift
    this->send8(0b00000110);
    gpio_put(this->_rsPin, 1);
    this->clear();
}

void LCD::clear(void)
{
    gpio_put(this->_rsPin, 0);
    // Clear display
    this->send8(0b00000001);
    sleep_ms(2);
    gpio_put(this->_rsPin, 1);
}

void LCD::print(char str[])
{
    int i = 0;
    while (str[i])
    {
        send8(str[i]);
        i++;
    }
}

void LCD::set_contrast(uint val)
{
    pwm_set_gpio_level(this->_v0Pin, val);
}

void LCD::pulse(void)
{
    gpio_put(this->_enPin, 1);
    sleep_us(40);
    gpio_put(this->_enPin, 0);
    sleep_us(80);
}

void LCD::send4(uint8_t data)
{
    gpio_put(this->_d4Pin, (data & 0x1) >> 0);
    gpio_put(this->_d5Pin, (data & 0x2) >> 1);
    gpio_put(this->_d6Pin, (data & 0x4) >> 2);
    gpio_put(this->_d7Pin, (data & 0x8) >> 3);
    this->pulse();
}

void LCD::send8(uint8_t data)
{
    this->send4((data & 0xf0) >> 4);
    this->send4((data & 0x0f) >> 0);
}
