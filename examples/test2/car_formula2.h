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

/*
đầu
1 2
3 4
đít
*/
void motor1(bool direct,uint8_t speed){
  myDriver.writeMA(!direct, speed);
}
void motor2(bool direct,uint8_t speed){
  myDriver2.writeMB(direct, speed);
}
void motor3(bool direct,uint8_t speed){
  myDriver2.writeMA(direct, speed);
}
void motor4(bool direct,uint8_t speed){
  myDriver.writeMB(!direct, speed);
}

void mov_str(bool direct) // for go straight forward or backward
{
  motor2(direct, speed);
  motor1(direct, speed);
  motor3(direct, speed);
  motor4(direct, speed);
}

void mov_sdw(bool direct) // for go side left or right
{
  motor2(!direct, speed);
  motor1(direct, speed);
  motor3(direct, speed);
  motor4(!direct, speed);
}

void mov_dia(bool direct, bool side) // for go through to the left or the right
{
  switch (side)
  {
  case left:
    if (direct)
    {
      motor1(direct, 0);
      motor3(direct, 0);
      motor2(direct, speed);
      motor4(direct, speed);
    }
    else
    {
      motor2(direct, 0);
      motor4(direct, 0);
      motor1(direct, speed);
      motor3(direct, speed);
    }
    break;
  case right:
    if (direct)
    {
      motor2(direct, 0);
      motor4(direct, 0);
      motor1(direct, speed);
      motor3(direct, speed);
    }
    else
    {
      motor1(direct, 0);
      motor3(direct, 0);
      motor2(direct, speed);
      motor4(direct, speed);
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
    motor2(direct, speed);
    motor3(direct, speed);
    motor1(direct, 0);
    motor4(direct, 0);
    break;
  case right:
    motor1(direct, speed);
    motor4(direct, speed);
    motor2(direct, 0);
    motor3(direct, 0);
    break;
  default:
    break;
  }
}

void rotation(bool side, uint8_t speed) // rotate by the stand side
{
  motor2(!side, speed);
  motor1(side, speed);
  motor3(!side, speed);
  motor4(side, speed);
}

void rt_ard_p(bool wd, bool side, uint8_t speed) // rotate 135 to 45 degree
{
  switch (wd)
  {
  case front:
    motor2(!side, speed);
    motor1(side, speed);
    motor3(side, 0);
    motor4(!side, 0);
    break;

  case back:
    motor3(side, speed);
    motor4(!side, speed);
    motor2(side, 0);
    motor1(!side, 0);
    break;

  default:
    break;
  }
}

void stop()
{
  motor2(1, 0);
  motor1(1, 0);
  motor3(1, 0);
  motor4(1, 0);
}
