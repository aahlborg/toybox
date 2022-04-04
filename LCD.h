#ifndef LCD_H
#define LCD_H

#include "Driver.h"
#include <cstdint>

class LCD : Driver
{
public:
    explicit LCD(int d4, int d5, int d6, int d7, int en, int rs, int v0);
    void init(void);
    void clear(void);
    void print(char str[]);
    void set_contrast(int val);

private:
    const Pin& d4Pin() { return this->pin(LCD::_d4Idx); }
    const Pin& d5Pin() { return this->pin(LCD::_d5Idx); }
    const Pin& d6Pin() { return this->pin(LCD::_d6Idx); }
    const Pin& d7Pin() { return this->pin(LCD::_d7Idx); }
    const Pin& enPin() { return this->pin(LCD::_enIdx); }
    const Pin& rsPin() { return this->pin(LCD::_rsIdx); }
    const Pin& v0Pin() { return this->pin(LCD::_v0Idx); }
    void pulse(void);
    void send4(uint8_t data);
    void send8(uint8_t data);

    static constexpr int _d4Idx = 0;
    static constexpr int _d5Idx = 1;
    static constexpr int _d6Idx = 2;
    static constexpr int _d7Idx = 3;
    static constexpr int _enIdx = 4;
    static constexpr int _rsIdx = 5;
    static constexpr int _v0Idx = 6;
};

#endif // LCD_H
