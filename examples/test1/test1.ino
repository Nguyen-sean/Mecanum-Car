#include <Makerlabvn_I2C_Motor_Driver.h>
#include <kxnTask.h>

void mov_str(bool direct);
void mov_sdw(bool direct);
void mov_dia(bool direct, bool side);
void mov_ard_bd(bool direct, bool side);
void rotation(bool side);
void rt_ard_p(bool wd, bool side);


Makerlabvn_I2C_Motor_Driver myDriver(0);
Makerlabvn_I2C_Motor_Driver myDriver2(1);

unsigned int speed = 70; // unit: percent (%)
bool forward = 1, backward = 0;
void setup(void)
{
}

void loop(void)
{
    kxnTaskManager.run(millis());
}

void mov_str(bool direct) // for go straight forward or backward
{
    myDriver.writeMA(direct, speed);
    myDriver.writeMB(direct, speed);
    myDriver2.writeMA(direct, speed);
    myDriver2.writeMB(direct, speed);
}

void mov_sdw(bool direct) // for go side left or right
{
    myDriver.writeMA(direct, speed);
    myDriver.writeMB(!direct, speed);
    myDriver2.writeMA(!direct, speed);
    myDriver2.writeMB(direct, speed);
}
enum
{
    left = 0,
    right = 1,
};
void mov_dia(bool direct, bool side) // for go through to the left or the right
{
    switch (side)
    {
    case left:
        myDriver.writeMA(direct, speed);
        myDriver.writeMB(!direct, 0);
        myDriver2.writeMA(!direct, 0);
        myDriver2.writeMB(direct, speed);
        break;
    case right:
        myDriver.writeMA(!direct, speed);
        myDriver.writeMB(direct, speed);
        myDriver2.writeMA(direct, speed);
        myDriver2.writeMB(!direct, speed);
        break;
    default:
        break;
    }
}

void mov_ard_bd(bool direct, bool side) // for go cylce 135 to 225
{
    switch (side)
    {
    case left:
        myDriver.writeMA(direct, 0);
        myDriver.writeMB(direct, speed);
        myDriver2.writeMA(direct, speed);
        myDriver2.writeMB(direct, 0);
        break;
    case right:
        myDriver.writeMA(direct, speed);
        myDriver.writeMB(direct, 0);
        myDriver2.writeMA(direct, 0);
        myDriver2.writeMB(direct, speed);
        break;
    default:
        break;
    }
}

void rotation(bool side) // rotate by the stand side
{
    myDriver.writeMA(side, speed);
    myDriver.writeMB(side, speed);
    myDriver2.writeMA(!side, speed);
    myDriver2.writeMB(!side, speed);
}
typedef enum
{
    front = 1,
    back = 0,
} car_wd;
void rt_ard_p(bool wd, bool side) // rotate 135 to 45 degree
{
    switch (wd)
    {
    case front:
        myDriver.writeMA(side, speed);
        myDriver.writeMB(!side, speed);
        break;

    case back:
        myDriver2.writeMA(side, speed);
        myDriver2.writeMB(!side, speed);
        break;

    default:
        break;
    }
}