#include "LCD.h"


LCD::LCD(int d4, int d5, int d6, int d7, int en, int rs, int v0) :
    Driver({Pin(d4, FN_OUTPUT),
            Pin(d5, FN_OUTPUT),
            Pin(d6, FN_OUTPUT),
            Pin(d7, FN_OUTPUT),
            Pin(en, FN_OUTPUT),
            Pin(rs, FN_OUTPUT),
            Pin(v0, FN_PWM, {.wrap_value = 100, .clock_divider = 8.f})})
{
}

void LCD::init(void)
{
    this->rsPin().set(0);
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
    this->rsPin().set(1);
    this->clear();
}

void LCD::clear(void)
{
    this->rsPin().set(0);
    // Clear display
    this->send8(0b00000001);
    sleep_ms(2);
    this->rsPin().set(1);
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

void LCD::set_contrast(int val)
{
    this->v0Pin().set_duty(val);
}

void LCD::pulse(void)
{
    this->enPin().set(1);
    sleep_us(40);
    this->enPin().set(0);
    sleep_us(80);
}

void LCD::send4(uint8_t data)
{
    this->d4Pin().set((data & 0x1) >> 0);
    this->d5Pin().set((data & 0x2) >> 1);
    this->d6Pin().set((data & 0x4) >> 2);
    this->d7Pin().set((data & 0x8) >> 3);
    this->pulse();
}

void LCD::send8(uint8_t data)
{
    this->send4((data & 0xf0) >> 4);
    this->send4((data & 0x0f) >> 0);
}
