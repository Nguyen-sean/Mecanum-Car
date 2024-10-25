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
    if (joyStick2_RAD > 10)
    {
        switch (joyStick2.getDir())
        {
        case joyStick2.W:
            if (joyStick2.getDir() == joyStick2.NW)
                mov_ard_bd(front, left);
            else if (joyStick2.getDir() == joyStick2.SW)
                mov_ard_bd(back, left);
            else
                rotation(left, speed2);
            break;

        case joyStick2.E:
            if (joyStick2.getDir() == joyStick2.NE)
                mov_ard_bd(front, right);
            else if (joyStick2.getDir() == joyStick2.SW)
                mov_ard_bd(back, right);
            else
                rotation(right, speed2);
            break;

        case joyStick2.N:
            if (joyStick2.getDir() == joyStick2.NW)
                rt_ard_p(front, left);
            else if (joyStick2.getDir() == joyStick2.NE)
                rt_ard_p(front, right);
            break;

        case joyStick2.S:
            if (joyStick2.getDir() == joyStick2.SW)
                rt_ard_p(back, left);
            else if (joyStick2.getDir() == joyStick2.S_E)
                rt_ard_p(back, right);
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
    }
    else
    {
        stop();
    }
}
