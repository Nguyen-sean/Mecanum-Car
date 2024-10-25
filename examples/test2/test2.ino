#include "setup.h"

void setup(void)
{
    setup_IIC();
    Serial.begin(115200);
}

void loop(void)
{
    kxnTaskManager.run(millis());

    uint8_t joyStick1_RAD = sGamepad.Get_RAD_Joy_L();
    uint8_t joyStick2_RAD = sGamepad.Get_RAD_Joy_R();
    speed = map(sGamepad.Get_RAD_Joy_L(), 0, 255, 0, 70);
    speed2 = map(sGamepad.Get_RAD_Joy_R(), 0, 255, 0, 70);

    getData();

    // switch (leftJoyBTT.get_bt_Stt())
    // {
    // case leftJoyBTT.ON:
    //     rotation(left, 80);
    //     break;

    // case leftJoyBTT.OFF:
    //     // stop();
    //     break;

    // default:
    //     break;
    // }
    if (joyStick2_RAD > 50)
    {
        switch (joyStick2.getDir())
        {
        case joyStick2.W:
            rotation(left, speed2);
            break;
        case joyStick2.E:
            rotation(right, speed2);
            break;

        default:
            break;
        }
    }
    else if (joyStick1_RAD > 10)
    {
        switch (joyStick1.getDir())
        {
        case joyStick1.N:
            mov_str(forward);
            break;
        case joyStick1.W:
            mov_sdw(left);
            break;
        case joyStick1.S:
            mov_str(backward);
            break;
        case joyStick1.E:
            mov_sdw(right);
            break;
        case joyStick1.NW:
            mov_dia(forward, left);
            break;
        case joyStick1.SW:
            mov_dia(backward, left);
            break;
        case joyStick1.S_E:
            mov_dia(backward, right);
            break;
        case joyStick1.NE:
            mov_dia(forward, right);
            break;

        default:
            break;
        }
    } else {
        stop();
    }
}
