#ifndef MKL_Gamepad_joystick_SEAN__
#define MKL_Gamepad_joystick_SEAN__

#include "Arduino.h"
#include "kxnTask.h"

CREATE_TASK(MKL_Gamepad_joystick)

private:
    uint8_t joystickXPin; // Chân analog cho trục X của joystick
    uint8_t joystickYPin; // Chân analog cho trục Y của joystick
    uint8_t buttonPin;    // Chân digital cho nút nhấn

    float x;
    float y;
    int xCenter = 512;    // Giá trị trung tâm mặc định cho trục X
    int yCenter = 512;    // Giá trị trung tâm mặc định cho trục Y
    int max_radius = 512; // bán kính tối đa của Joystick

    int radius;
    int angleDeg;
    void Joystick_configureCenter(); // Hàm cấu hình tọa độ trung tâm

public:
    void setup(uint8_t joystickXPin_, uint8_t joystickYPin_, uint8_t buttonPin_);

    float analogRead_Ox();

    float analogRead_Oy();

    int AngleDed();

    int Radius();
    int Radius_approximately(uint8_t num_approximately);

    void Serial_debug();
END

#endif