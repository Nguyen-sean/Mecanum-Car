#include "setup.h"

bool bt_left = 0;
bool bt_right = 0;

void setup(void)
{
    setup_IIC();
    Serial.begin(115200);
}

void loop(void)
{
    speed = map(sGamepad.Get_RAD_Joy_L(), 0, 255, 0, 70);
    getData();
    // Serial.print("LEFT: ");
    // Serial.print(joyStick1.getDir());

    // Serial.print("||");

    // Serial.print(" RIGHT: ");
    // Serial.print(joyStick2.getDir());
    // Serial.println(); // Debug Complete y24m10d25
    // Serial.println(joyStick1.temp_deg);

    switch (joyStick1.getDir())
    {
    case joyStick1.N:
        /* code */
        mov_str(forward);
        break;
    case joyStick1.W:
        /* code */
        mov_sdw(left);
        break;
    case joyStick1.S:
        /* code */
        mov_str(backward);
        break;
    case joyStick1.E:
        /* code */
        mov_sdw(right);
        break;
    case joyStick1.NW:
        /* code */
        mov_dia(forward, left);
        break;
    case joyStick1.SW:
        /* code */
        mov_dia(backward, left);
        break;
    case joyStick1.S_E:
        /* code */
        mov_dia(backward, right);
        break;
    case joyStick1.NE:
        /* code */
        mov_dia(forward, right);
        break;

    default:
        stop();
        break;
    }

    // if (bt_left == 1)
    //     rotation(left, 70);
    // else if ( bt_right == 1)
    //     rotation(right, 70);
    // else
    //     stop();
    // switch (sGamepad.Get_status_Joystick_Button_Left())
    // {
    // case 1:
    //     rotation(left, 70);
    //     break;

    // default:
    //     stop();
    //     break;
    // }

    // switch (sGamepad.Get_status_Joystick_Button_Right())
    // {
    // case 1:
    //     rotation(right, 70);
    //     break;

    // default:
    //     stop();
    //     break;
    // }
    // switch (joyStick2.getDir())
    // {
    // case joyStick2.N:
    //     /* code */
    //     mov_str(forward);
    //     break;
    // case joyStick2.W:
    //     /* code */
    //     mov_sdw(left);
    //     break;
    // case joyStick2.S:
    //     /* code */
    //     mov_str(backward);
    //     break;
    // case joyStick2.E:
    //     /* code */
    //     mov_sdw(right);
    //     break;
    // case joyStick2.NW:
    //     /* code */
    //     mov_dia(forward,left);
    //     break;
    // case joyStick2.SW:
    //     /* code */
    //     mov_dia(backward,left);
    //     break;
    // case joyStick2.S_E:
    //     /* code */
    //     mov_dia(backward,right);
    //     break;
    // case joyStick2.NE:
    //     /* code */
    //     mov_dia(forward,right);
    //     break;

    // default:
    //     stop();
    //     break;
    // }

    kxnTaskManager.run(millis());
}
