#pragma once

#include "kxnTask.h"

DEFINE_TASK_STATE(joystick_dir){
    joystick_dir_ON,
    joystick_dir22_ON,
    joystick_dir_OFF,
};

CREATE_TASK(joystick_dir)

const float per_deg_p22[9] = {315, 360, 0, 45, 90, 135, 180, 225, 270};
const float per_deg[8] = {337.5, 22.5, 67.5, 112.5, 157.5, 202.5, 247.5, 292.5};

float temp_deg = 0;
uint8_t r_Dir = 0;
uint8_t r_Dir22 = 0;

typedef enum
{
  E = 10,
  ENE, // 11
  NE,  // 12
  NNE, // 13
  N,   // 14
  NNW, // 15
  NW,  // 16
  WNW, // 17
  W,   // 18
  WSW, // 19
  SW,  // 20
  SSW, // 21
  S,   // 22
  SSE, // 23
  S_E, // 24
  ESE, // 25

} joystick_dir_char;

void setup()
{
  this->resetData();
  kDelay(0);
  this->stop();
}

void loop()
{

  switch (getState())
  {
  case joystick_dir_ON:

    if (this->temp_deg == 0)
      this->r_Dir = E;
    else if (this->temp_deg >= per_deg[0] || this->temp_deg < per_deg[1])
      this->r_Dir = E;
    else if (this->temp_deg >= per_deg[1] && this->temp_deg < per_deg[2])
      this->r_Dir = NE;
    else if (this->temp_deg >= per_deg[2] && this->temp_deg < per_deg[3])
      this->r_Dir = N;
    else if (this->temp_deg >= per_deg[3] && this->temp_deg < per_deg[4])
      this->r_Dir = NW;
    else if (this->temp_deg >= per_deg[4] && this->temp_deg < per_deg[5])
      this->r_Dir = W;
    else if (this->temp_deg >= per_deg[5] && this->temp_deg < per_deg[6])
      this->r_Dir = SW;
    else if (this->temp_deg >= per_deg[6] && this->temp_deg < per_deg[7])
      this->r_Dir = S;
    else if (this->temp_deg >= per_deg[7] && this->temp_deg < per_deg[0])
      this->r_Dir = S_E;

    kDelay(0);

    setState(joystick_dir_OFF);

    break;

  case joystick_dir22_ON:

    if (this->temp_deg >= per_deg_p22[0] && this->temp_deg < per_deg_p22[1])
      this->r_Dir22 = ESE;
    else if (this->temp_deg >= per_deg_p22[2] && this->temp_deg < per_deg_p22[3])
      this->r_Dir22 = ENE;
    else if (this->temp_deg >= per_deg_p22[3] && this->temp_deg < per_deg_p22[4])
      this->r_Dir22 = NNE;
    else if (this->temp_deg >= per_deg_p22[4] && this->temp_deg < per_deg_p22[5])
      this->r_Dir22 = NNW;
    else if (this->temp_deg >= per_deg_p22[5] && this->temp_deg < per_deg_p22[6])
      this->r_Dir22 = WNW;
    else if (this->temp_deg >= per_deg_p22[6] && this->temp_deg < per_deg_p22[7])
      this->r_Dir22 = WSW;
    else if (this->temp_deg >= per_deg_p22[7] && this->temp_deg < per_deg_p22[8])
      this->r_Dir22 = SSW;
    else if (this->temp_deg >= per_deg_p22[8] && this->temp_deg < per_deg_p22[0])
      this->r_Dir22 = SSE;

    kDelay(0);

    setState(joystick_dir_OFF);

    break;

  case joystick_dir_OFF:
    this->resetData();
    kDelay(0);
    this->stop();
    break;

  default:
    this->stop();
    break;
  }
}

uint8_t getDir()
{
  this->stop();
  kxnTaskManager.add(this);
  setState(joystick_dir_ON);
  return this->r_Dir;
}

uint8_t getDir22()
{
  this->stop();
  kxnTaskManager.add(this);
  setState(joystick_dir22_ON);
  return this->r_Dir22;
}

void read_Joystick(float deg)
{
  kDelay(0);
  this->temp_deg = deg;
  stop();
}

void stop()
{
  // this->r_Dir = 0;
  kDelay(0);
  setStateIdle();
}

bool resetData()
{
  this->temp_deg = 0;
  this->r_Dir = 0;
  this->r_Dir22 = 0;

  // if (this->temp_deg != 0 || this->r_Dir != 0)
  //   return false;
  // return true;
}

END
