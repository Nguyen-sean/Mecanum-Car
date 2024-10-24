#include "MKL_Gamepad_joystick.h"

void MKL_Gamepad_joystick::setup(uint8_t joystickXPin_, uint8_t joystickYPin_, uint8_t buttonPin_)
{
    joystickXPin = joystickXPin_;
    joystickYPin = joystickYPin_;
    buttonPin = buttonPin_;

    pinMode(joystickXPin, INPUT);
    pinMode(joystickYPin, INPUT);
    pinMode(buttonPin, INPUT_PULLUP);

    Joystick_configureCenter(); // config tọa độ gốc
}

float MKL_Gamepad_joystick::analogRead_Ox()
{
    return map(analogRead(joystickXPin), 0, 1024, 1024, 0) - xCenter;
}

float MKL_Gamepad_joystick::analogRead_Oy()
{
    return analogRead(joystickYPin) - yCenter;
}

int MKL_Gamepad_joystick::AngleDed()
{
    // Chuyển đổi giá trị theo tọa độ trung tâm
    x = analogRead_Ox();
    y = analogRead_Oy();

    if (((-5 < x) && (x < 5)) && ((-5 < y) && (y < 5)))
    {
        angleDeg = 0;
        radius = 0;
    }
    else
    {
        angleDeg = atan2(y, x) * (180.0 / PI);

        // Điều chỉnh góc để nằm trong khoảng từ 0 đến 360 độ
        if (angleDeg < 0)
        {
            angleDeg += 360.0;
        }
    }
    return angleDeg;
}

int MKL_Gamepad_joystick::Radius()
{
    x = analogRead_Ox();
    y = analogRead_Oy();

    if (((-5 < x) && (x < 5)) && ((-5 < y) && (y < 5)))
    {
        angleDeg = 0;
        radius = 0;
    }
    else
    {
        // Tính bán kính (khoảng cách từ gốc tọa độ)
        radius = sqrt(x * x + y * y);
        if (radius > max_radius)
        {
            radius = max_radius;
        }
    }
    return map(radius, 0, max_radius, 0, 512);
}

int MKL_Gamepad_joystick::Radius_approximately(uint8_t num_approximately)
{
    return map(Radius(), 0, max_radius, 0, num_approximately);
}

void MKL_Gamepad_joystick::Serial_debug()
{

    // In kết quả
    // Serial.print("X: ");
    // Serial.print(x);
    // Serial.print(" Y: ");
    // Serial.print(y);
    Serial.print(" || DEG: ");
    Serial.print(AngleDed());
    Serial.print(" || Radius: ");
    Serial.println(Radius());
}
void MKL_Gamepad_joystick::Joystick_configureCenter()
{
    long xSum = 0;
    long ySum = 0;
    const int sampleCount = 5; // Số lần đọc để lấy trung bình

    for (int i = 0; i < sampleCount; i++)
    {
        xSum += map(analogRead(joystickXPin), 0, 1024, 1024, 0);
        ySum += analogRead(joystickYPin);
        delay(10);
    }

    xCenter = xSum / sampleCount;
    yCenter = ySum / sampleCount;

    max_radius = min(min(xCenter, 1024 - xCenter), min(yCenter, 1024 - yCenter));
}