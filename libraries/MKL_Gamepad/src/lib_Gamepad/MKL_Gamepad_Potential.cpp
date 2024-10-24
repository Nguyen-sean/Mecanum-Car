#include "MKL_Gamepad_Potential.h"

void MKL_Gamepad_Potential::setup(uint8_t pin)
{
    this->_pin = pin;
    pinMode(_pin, INPUT);
}

int MKL_Gamepad_Potential::readValue()
{
    return KalmanFilter.updateEstimate(map(analogRead(_pin), 0, 1024, 1024, 0));
}
int MKL_Gamepad_Potential::RawValue()
{
    return map(analogRead(_pin), 0, 1024, 1024, 0);
}