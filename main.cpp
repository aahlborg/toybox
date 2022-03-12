#include <stdio.h>
#include <pico/stdlib.h>
#include "LCD.h"

#define D4_PIN (21u)
#define D5_PIN (20u)
#define D6_PIN (19u)
#define D7_PIN (18u)
#define EN_PIN (16u)
#define RS_PIN (17u)
#define V0_PIN (22u)

int main(void)
{
    stdio_init_all();
    printf("Starting\n");

    LCD _lcd(D4_PIN,
             D5_PIN,
             D6_PIN,
             D7_PIN,
             EN_PIN,
             RS_PIN,
             V0_PIN);
    _lcd.init();
    _lcd.set_contrast(25);

    for (uint i = 0; true; i++)
    {
        sleep_ms(1000);
        printf("Hej\n");

        char buf[100];
        sprintf(buf, "Hello %u", i);
        _lcd.clear();
        _lcd.print(buf);
    }
}
