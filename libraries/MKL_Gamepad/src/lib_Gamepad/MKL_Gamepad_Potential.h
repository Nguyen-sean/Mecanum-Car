#ifndef MKL_Gamepad_Potential_SEAN__
#define MKL_Gamepad_Potential_SEAN__
#include "Arduino.h"
#include "kxnTask.h"
#include <lib_Gamepad/MKL_SimpleKalmanFilter.h>

CREATE_TASK(MKL_Gamepad_Potential)

private:
    MKL_SimpleKalmanFilter KalmanFilter;
    uint8_t _pin;

public:
    MKL_Gamepad_Potential() : KalmanFilter(1, 2, 0.03) {} // Khởi tạo KalmanFilter trong hàm tạo
    void setup(uint8_t pin);

    int readValue();
    int RawValue();
END

#endif
