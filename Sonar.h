#ifndef SONAR_H
#define SONAR_H

#include "Driver.h"

class Sonar : Driver
{
public:
    explicit Sonar(int trigPin, int echoPin);

    void startMeasurement();
    int getMeasurementMm();

private:
    void callbackHandler(int gpio, uint32_t events);
    const Pin& trigPin() { return this->pin(Sonar::_trigIdx); }
    const Pin& echoPin() { return this->pin(Sonar::_echoIdx); }

    static constexpr int _trigIdx = 0;
    static constexpr int _echoIdx = 1;

    bool _measuring;
    bool _echo_high;
    int _echo_start_us;
    int _last_echo_duration;
};

#endif // SONAR_H
