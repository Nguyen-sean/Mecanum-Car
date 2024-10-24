#include "MKL_Gamepad.h"

// #define AVR_sean

MKL_Gamepad_RX Gamepad;

enum Motor_direction
{
  Stop_Motor,
  Clockwise,
  Counter_Clockwise
};

typedef enum Num_Motor
{
  Motor_1,
  Motor_2,
  Motor_3,
  Motor_4
};

typedef enum Motor_happen
{
  run_forward,
  run_backward,
  no_run,
};

const int motor1_in1 = 14;
const int motor1_in2 = 27;
// Motor 2
const int motor2_in1 = 2;
const int motor2_in2 = 13;
// Motor 3
const int motor3_in1 = 26;
const int motor3_in2 = 25;
// Motor 4
const int motor4_in1 = 16;
const int motor4_in2 = 17;

int ratio_map = 10;
const int max_ratio_map = 20;
const int min_ratio_map = 0;
void Motor_RUN(int Choose_Motor, int direction, int _speed);

void forward();
void back();
void left();
void right();
void forwardleft();
void forwardright();
void backright();
void backleft();
void Stop();
// Motor 1

// int command = 1;
float DEG_joystick_L;
float DEG_joystick_R;
int Speed_MT = 250;

char servo_compare = 'B';
char servo_compare_s = 'A';
void setup()
{
  Wire.begin(21, 22); // join I2C bus (address optional for master)
  // Wire.setClock(100000);
  Serial.begin(115200);

  pinMode(motor1_in1, OUTPUT);
  pinMode(motor1_in2, OUTPUT);
  pinMode(motor2_in1, OUTPUT);
  pinMode(motor2_in2, OUTPUT);
  pinMode(motor3_in1, OUTPUT);
  pinMode(motor3_in2, OUTPUT);
  pinMode(motor4_in1, OUTPUT);
  pinMode(motor4_in2, OUTPUT);
  Gamepad.Reset_data_Gamepad();
  // delay(100);
}

void loop()
{
  Gamepad.Reset_data_Gamepad();
  Gamepad.getdata_Gamepad_I2C();

  DEG_joystick_L = constrain(Gamepad.Get_DEG_Joy_L(), 0, 360);
  DEG_joystick_R = constrain(Gamepad.Get_DEG_Joy_R(), 0, 360);
  // Wire.requestFrom(8, sizeof(Gamepad.Data_MKL_Gamepad_push));
  // while (Wire.available())
  // { // slave may send less than requested
  // Wire.readBytes((char *)&Gamepad.Data_MKL_Gamepad_push, sizeof(Gamepad.Data_MKL_Gamepad_push));
  Serial.print(ratio_map);
  Serial.print(" || ");
  Serial.print(Gamepad.Get_DEG_Joy_L());
  Serial.print(" || ");
  Serial.print(Gamepad.Data_MKL_Gamepad_push.RAD_Joy_L);
  Serial.print(" ||<==>|| ");
  Serial.print(Gamepad.Get_DEG_Joy_R());
  Serial.print(" || ");
  Serial.print(Gamepad.Data_MKL_Gamepad_push.RAD_Joy_R);
  Serial.print(" || ");
  Serial.print(Gamepad.Get_POT_L());
  Serial.print(" || ");
  Serial.print(Gamepad.Get_POT_R());
  Serial.print(" || ");
  Serial.println(Gamepad.Data_MKL_Gamepad_push.buttons, BIN);
  //-------------------------------------------------------------------

  if (DEG_joystick_L >= 1 && DEG_joystick_L < 80)
  {
    ratio_map = map(DEG_joystick_L, 1, 80, max_ratio_map, min_ratio_map);
  }
  else if (DEG_joystick_L >= 100 && DEG_joystick_L < 180)
  {
    ratio_map = map(DEG_joystick_L, 100, 180, max_ratio_map, min_ratio_map);
  }
  else if (DEG_joystick_L >= 180 && DEG_joystick_L < 260)
  {
    ratio_map = map(DEG_joystick_L, 180, 260, max_ratio_map, min_ratio_map);
  }
  else if (DEG_joystick_L >= 280 && DEG_joystick_L < 360)
  {
    ratio_map = map(DEG_joystick_L, 280, 360, min_ratio_map, max_ratio_map);
  }

  if (Gamepad.Get_RAD_Joy_L() > 10)
  {
    Speed_MT = Gamepad.Get_RAD_Joy_L();

    if (DEG_joystick_L >= 0 && DEG_joystick_L < 10)
    {
      // command = 'I';
      Speed_MT = 150;
      forwardright();
    }
    else if (DEG_joystick_L >= 10 && DEG_joystick_L < 80)
    {
      // command = 'I';
      forwardright();
    }
    else if (DEG_joystick_L >= 80 && DEG_joystick_L < 100) /// no change
    {
      // command = 'F';
      forward();
    }
    else if (DEG_joystick_L >= 100 && DEG_joystick_L < 170)
    {
      // command = 'G';
      forwardleft();
    }
    else if (DEG_joystick_L >= 170 && DEG_joystick_L < 180)
    {
      // command = 'G';
      Speed_MT = 150;
      forwardleft();
    }
    else if (DEG_joystick_L >= 180 && DEG_joystick_L < 190)
    {
      // command = 'H';
      Speed_MT = 150;
      backleft();
    }
    else if (DEG_joystick_L >= 190 && DEG_joystick_L < 260)
    {
      // command = 'H';
      backleft();
    }
    else if (DEG_joystick_L >= 260 && DEG_joystick_L < 280) /// no change
    {
      // command = 'B';
      back();
    }
    else if (DEG_joystick_L >= 280 && DEG_joystick_L < 350)
    {
      // command = 'J';
      backright();
    }
    else if (DEG_joystick_L >= 350 && DEG_joystick_L < 0)
    {
      // command = 'J';
      Speed_MT = 150;
      backright();
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  else if (Gamepad.Get_RAD_Joy_R() > 10)
  {
    Speed_MT = Gamepad.Get_RAD_Joy_R();
    if ((DEG_joystick_R >= 337.5) || (DEG_joystick_R < 22.5))
    {

      right();
    }
    else if (DEG_joystick_R >= 157.5 && DEG_joystick_R < 202.5)
    {

      left();
    }
  }
  else
  {
    Speed_MT = 0;
    Stop();
  }

  // Serial.println(//command);
  // analogWrite(pwm_1, Speed_MT);
  // analogWrite(pwm_2, Speed_MT);
}

void Motor_RUN(int Choose_Motor, int direction, int _speed)
{
  constrain(_speed, 0, 255);
  if (Choose_Motor >= 0 && Choose_Motor <= 4)
  {

    if (Choose_Motor == Motor_1)
    {
      if (direction == Clockwise)
      {
        analogWrite(motor1_in1, _speed);
        analogWrite(motor1_in2, 0);
      }
      else if (direction == Counter_Clockwise)
      {
        analogWrite(motor1_in1, 0);
        analogWrite(motor1_in2, _speed);
      }
      else if (direction == Stop_Motor)
      {
        analogWrite(motor1_in1, 0);
        analogWrite(motor1_in2, 0);
      }
    }

    else if (Choose_Motor == Motor_2)
    {
      if (direction == Clockwise)
      {
        analogWrite(motor2_in1, _speed);
        analogWrite(motor2_in2, 0);
      }
      else if (direction == Counter_Clockwise)
      {
        analogWrite(motor2_in1, 0);
        analogWrite(motor2_in2, _speed);
      }
      else if (direction == Stop_Motor)
      {
        analogWrite(motor2_in1, 0);
        analogWrite(motor2_in2, 0);
      }
    }

    else if (Choose_Motor == Motor_3)
    {
      if (direction == Clockwise)
      {
        analogWrite(motor3_in1, _speed);
        analogWrite(motor3_in2, 0);
      }
      else if (direction == Counter_Clockwise)
      {
        analogWrite(motor3_in1, 0);
        analogWrite(motor3_in2, _speed);
      }
      else if (direction == Stop_Motor)
      {
        analogWrite(motor3_in1, 0);
        analogWrite(motor3_in2, 0);
      }
    }

    else if (Choose_Motor == Motor_4)
    {
      if (direction == Clockwise)
      {
        analogWrite(motor4_in1, _speed);
        analogWrite(motor4_in2, 0);
      }
      else if (direction == Counter_Clockwise)
      {
        analogWrite(motor4_in1, 0);
        analogWrite(motor4_in2, _speed);
      }
      else if (direction == Stop_Motor)
      {
        analogWrite(motor4_in1, 0);
        analogWrite(motor4_in2, 0);
      }
    }
  }
}
void forward()
{
  Motor_RUN(Motor_1, Clockwise, Speed_MT);
  Motor_RUN(Motor_2, Clockwise, Speed_MT);
  Motor_RUN(Motor_3, Clockwise, Speed_MT);
  Motor_RUN(Motor_4, Clockwise, Speed_MT);
}

void back()
{
  Motor_RUN(Motor_1, Counter_Clockwise, Speed_MT);
  Motor_RUN(Motor_2, Counter_Clockwise, Speed_MT);
  Motor_RUN(Motor_3, Counter_Clockwise, Speed_MT);
  Motor_RUN(Motor_4, Counter_Clockwise, Speed_MT);
}

void left()
{
  Motor_RUN(Motor_1, Clockwise, Speed_MT);
  Motor_RUN(Motor_2, Clockwise, Speed_MT);
  Motor_RUN(Motor_3, Counter_Clockwise, Speed_MT);
  Motor_RUN(Motor_4, Counter_Clockwise, Speed_MT);
}

void right()
{
  Motor_RUN(Motor_1, Counter_Clockwise, Speed_MT);
  Motor_RUN(Motor_2, Counter_Clockwise, Speed_MT);
  Motor_RUN(Motor_3, Clockwise, Speed_MT);
  Motor_RUN(Motor_4, Clockwise, Speed_MT);
}
void forwardleft()
{
  Motor_RUN(Motor_1, Clockwise, Speed_MT);
  Motor_RUN(Motor_2, Clockwise, Speed_MT);
  Motor_RUN(Motor_3, Clockwise, Speed_MT / ratio_map);
  Motor_RUN(Motor_4, Clockwise, Speed_MT / ratio_map);
}
void forwardright()
{
  Motor_RUN(Motor_1, Clockwise, Speed_MT / ratio_map);
  Motor_RUN(Motor_2, Clockwise, Speed_MT / ratio_map);
  Motor_RUN(Motor_3, Clockwise, Speed_MT);
  Motor_RUN(Motor_4, Clockwise, Speed_MT);
}
void backright()
{
  Motor_RUN(Motor_1, Counter_Clockwise, Speed_MT / ratio_map);
  Motor_RUN(Motor_2, Counter_Clockwise, Speed_MT / ratio_map);
  Motor_RUN(Motor_3, Counter_Clockwise, Speed_MT);
  Motor_RUN(Motor_4, Counter_Clockwise, Speed_MT);
}
void backleft()
{
  Motor_RUN(Motor_1, Counter_Clockwise, Speed_MT);
  Motor_RUN(Motor_2, Counter_Clockwise, Speed_MT);
  Motor_RUN(Motor_3, Counter_Clockwise, Speed_MT / ratio_map);
  Motor_RUN(Motor_4, Counter_Clockwise, Speed_MT / ratio_map);
}

void Stop()
{
  Motor_RUN(Motor_1, Stop_Motor, 0);
  Motor_RUN(Motor_2, Stop_Motor, 0);
  Motor_RUN(Motor_3, Stop_Motor, 0);
  Motor_RUN(Motor_4, Stop_Motor, 0);
}
