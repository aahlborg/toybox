#include "Sonar.h"
#include <pico/stdlib.h>


std::map<int, Sonar*> Sonar::_callback_map;
static constexpr int speedOfSound = 343;

void echo_cb(uint gpio, uint32_t events)
{
    Sonar::_callback_map.at(gpio)->callbackHandler(events);
}

Sonar::Sonar(int trigPin, int echoPin) :
    Driver({Pin(trigPin, FN_OUTPUT),
            Pin(echoPin, FN_INPUT, {.callback = echo_cb, .events = GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE})}),
    _measuring(false),
    _echo_high(false),
    _echo_start_us(0),
    _last_echo_duration(0)
{
    Sonar::_callback_map[this->echoPin().pin()] = this;
}

Sonar::~Sonar()
{
    Sonar::_callback_map.erase(this->echoPin().pin());
}

void Sonar::callbackHandler(uint32_t events)
{
    if (this->_measuring)
    {
        if (events & GPIO_IRQ_EDGE_RISE)
        {
            this->_echo_start_us = time_us_32();
            this->_echo_high = true;
        }
        if (events & GPIO_IRQ_EDGE_FALL && this->_echo_high)
        {
            this->_last_echo_duration = time_us_32() - this->_echo_start_us;
            this->_echo_high = false;
            this->_measuring = false;
        }
    }
}

void Sonar::startMeasurement()
{
    this->_measuring = true;
    this->_echo_high = false;
    this->trigPin().set(1);
    // TODO: Asynchronous trig
    sleep_us(10);
    this->trigPin().set(0);
}

int Sonar::getMeasurementMm()
{
    int distance_x2_um = (speedOfSound * this->_last_echo_duration);
    int distance_mm = distance_x2_um / 2000;
    return distance_mm;
}
