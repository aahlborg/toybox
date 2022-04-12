#include <iostream>
#include <pico/stdlib.h>
#include "LCD.h"
#include "RgbLed.h"
#include "Sonar.h"

static constexpr int lcdD4Pin = 21;
static constexpr int lcdD5Pin = 20;
static constexpr int lcdD6Pin = 19;
static constexpr int lcdD7Pin = 18;
static constexpr int lcdEnPin = 16;
static constexpr int lcdRsPin = 17;
static constexpr int lcdV0Pin = 22;

static constexpr int ledRedPin = 11;
static constexpr int ledGreenPin = 12;
static constexpr int ledBluePin = 13;

static constexpr int sonarTrigPin = 26;
static constexpr int sonarEchoPin = 27;

using std::cout;
using std::endl;

int main(void)
{
    stdio_init_all();
    cout << "Starting" << endl;

    LCD _lcd(lcdD4Pin,
             lcdD5Pin,
             lcdD6Pin,
             lcdD7Pin,
             lcdEnPin,
             lcdRsPin,
             lcdV0Pin);
    _lcd.init();
    _lcd.set_contrast(25);

    RgbLed _rgbLed(ledRedPin,
                   ledGreenPin,
                   ledBluePin);

    Sonar _sonar(sonarTrigPin,
                 sonarEchoPin);

    for (int i = 0; true; i++)
    {
        sleep_ms(100);
        cout << "Hej " << i << endl;

        _sonar.startMeasurement();
        _lcd.clear();
        char str[32];
        int distance = _sonar.getMeasurementMm();
        if (distance < 1000)
        {
            snprintf(str, 32, "%u cm", distance / 10);
            int level = distance * distance / 10000;
            _rgbLed.set_color(level, level, level);
        }
        else
        {
            snprintf(str, 32, "-- cm");
            _rgbLed.set_color(0, 0, 0);
        }
        _lcd.print(str);
    }
}
