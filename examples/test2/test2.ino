#include "setup.h"

void setup(void)
{
    setup_IIC();
    Serial.begin(115200);
}

void loop(void)
{
    kxnTaskManager.run(millis());

    uint8_t joyStick1_Sens_percent = 90;
    uint8_t joyStick2_Sens_percent = 10;

    uint8_t joyStick1_Sens_threshhold = map(joyStick1_Sens_percent, 0, 100, 255, 0);
    uint8_t joyStick2_Sens_threshhold = map(joyStick2_Sens_percent, 0, 100, 255, 0);

    uint8_t joyStick1_RAD = sGamepad.Get_RAD_Joy_L();
    uint8_t joyStick2_RAD = sGamepad.Get_RAD_Joy_R();

    speed = map(sGamepad.Get_RAD_Joy_L(), 0, 255, 0, 70);
    speed2 = map(sGamepad.Get_RAD_Joy_R(), 0, 255, 0, 70);

    getData();
    if (joyStick2_RAD > joyStick2_Sens_threshhold)
    {
            // if (joyStick2.getDir() == joyStick2.E && joyStick1.getDir() == joyStick1.E)
            //     rotation(right, (speed2 + speed) / 2);
            // else if (joyStick2.getDir() == joyStick2.W && joyStick1.getDir() == joyStick1.W)
            //     rotation(left, (speed2 + speed) / 2);
        // Serial.println(joyStick2.getDir22());
        switch (joyStick2.getDir22())
        {
            // case joyStick2.E:
            //     rotation(right, speed2);
            //     break;

            // case joyStick2.W:
            //     rotation(left, speed2);
            //     break;

        case joyStick2.WNW:
            mov_ard_bd(front, left, speed2);
            break;

        case joyStick2.WSW:
            mov_ard_bd(back, left, speed2);
            break;
        case joyStick2.ENE:
            mov_ard_bd(front, right, speed2);
            break;
        case joyStick2.ESE:
            mov_ard_bd(back, right, speed2);
            break;
        case joyStick2.NNW:
            rt_ard_p(front, left, speed2);
            break;
        case joyStick2.SSW:
            rt_ard_p(back, left, speed2);
            break;
        case joyStick2.NNE:
            rt_ard_p(front, right, speed2);
            break;
        case joyStick2.SSE:
            rt_ard_p(back, right, speed2);
        default:
            break;
        }
    }

    else if (joyStick1_RAD > joyStick1_Sens_threshhold)
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
    }
    else if (leftJoyBTT.get_bt_Stt() == leftJoyBTT.ON)
    rotation(left, 70);
    else if (rightJoyBTT.get_bt_Stt() == rightJoyBTT.ON)
    rotation(right, 70);
    else
    {
        stop();
    }
}
