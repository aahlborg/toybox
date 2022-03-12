#ifndef LCD_H
#define LCD_H

#include <pico/types.h>

class LCD
{
public:
    explicit LCD(uint d4, uint d5, uint d6, uint d7, uint en, uint rs, uint v0);
    void init(void);
    void clear(void);
    void print(char str[]);
    void set_contrast(uint val);

private:
    uint _d4Pin;
    uint _d5Pin;
    uint _d6Pin;
    uint _d7Pin;
    uint _enPin;
    uint _rsPin;
    uint _v0Pin;
    void pulse(void);
    void send4(uint8_t data);
    void send8(uint8_t data);
};

#endif // LCD_H
