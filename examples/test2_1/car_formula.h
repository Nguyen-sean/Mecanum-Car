#include <Makerlabvn_I2C_Motor_Driver.h>

extern Makerlabvn_I2C_Motor_Driver myDriver(0);
extern Makerlabvn_I2C_Motor_Driver myDriver2(1);

void mov_str(bool direct);
void mov_sdw(bool direct);
void mov_dia(bool direct, bool side);
void mov_ard_bd(bool direct, bool side, uint8_t speed);
void rotation(bool side, uint8_t speed);
void rt_ard_p(bool wd, bool side, uint8_t speed);

unsigned int speed = 0;  // unit: percent (%)
unsigned int speed2 = 0; // unit: percent (%)

bool forward = 1, backward = 0;

enum
{
  left = 0,
  right = 1,
};

typedef enum
{
  front = 1,
  back = 0,
} car_wd;

void mov_str(bool direct) // for go straight forward or backward
{
  myDriver.writeMA(direct, speed);
  myDriver.writeMB(direct, speed);
  myDriver2.writeMA(direct, speed);
  myDriver2.writeMB(direct, speed);
}

void mov_sdw(bool direct) // for go side left or right
{
  myDriver.writeMA(!direct, speed);
  myDriver.writeMB(direct, speed);
  myDriver2.writeMA(direct, speed);
  myDriver2.writeMB(!direct, speed);
}

void mov_dia(bool direct, bool side) // for go through to the left or the right
{
  switch (side)
  {
  case left:
    if (direct)
    {
      myDriver.writeMB(direct, 0);
      myDriver2.writeMA(direct, 0);
      myDriver.writeMA(direct, speed);
      myDriver2.writeMB(direct, speed);
    }
    else
    {
      myDriver.writeMA(direct, 0);
      myDriver2.writeMB(direct, 0);
      myDriver.writeMB(direct, speed);
      myDriver2.writeMA(direct, speed);
    }
    break;
  case right:
    if (direct)
    {
      myDriver.writeMA(direct, 0);
      myDriver2.writeMB(direct, 0);
      myDriver.writeMB(direct, speed);
      myDriver2.writeMA(direct, speed);
    }
    else
    {
      myDriver.writeMB(direct, 0);
      myDriver2.writeMA(direct, 0);
      myDriver.writeMA(direct, speed);
      myDriver2.writeMB(direct, speed);
    }

    break;
  default:
    break;
  }
}

void mov_ard_bd(bool direct, bool side, uint8_t speed) // for go cylce 135 to 225
{
  switch (side)
  {
  case left:
    myDriver.writeMA(direct, speed);
    myDriver2.writeMA(direct, speed);
    myDriver.writeMB(direct, 0);
    myDriver2.writeMB(direct, 0);
    break;
  case right:
    myDriver.writeMB(direct, speed);
    myDriver2.writeMB(direct, speed);
    myDriver.writeMA(direct, 0);
    myDriver2.writeMA(direct, 0);
    break;
  default:
    break;
  }
}

void rotation(bool side, uint8_t speed) // rotate by the stand side
{
  myDriver.writeMA(!side, speed);
  myDriver.writeMB(side, speed);
  myDriver2.writeMA(!side, speed);
  myDriver2.writeMB(side, speed);
}

void rt_ard_p(bool wd, bool side, uint8_t speed) // rotate 135 to 45 degree
{
  switch (wd)
  {
  case front:
    myDriver.writeMA(!side, speed);
    myDriver.writeMB(side, speed);
    myDriver2.writeMA(side, 0);
    myDriver2.writeMB(!side, 0);
    break;

  case back:
    myDriver2.writeMA(side, speed);
    myDriver2.writeMB(!side, speed);
    myDriver.writeMA(side, 0);
    myDriver.writeMB(!side, 0);
    break;

  default:
    break;
  }
}

void stop()
{
  myDriver.writeMA(0, 0);
  myDriver.writeMB(0, 0);
  myDriver2.writeMA(0, 0);
  myDriver2.writeMB(0, 0);
}
