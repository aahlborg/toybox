#include <stdio.h>
#include <pico/stdlib.h>

int main()
{
    stdio_init_all();
    printf("Starting\n");

    for (;;)
    {
        sleep_ms(1000);
        printf("Hej\n");
    }
}
