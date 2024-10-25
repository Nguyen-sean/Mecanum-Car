#pragma once

#include "kxnTask.h"

DEFINE_TASK_STATE(joystick_dir){
    joystick_dir_ON,
    joystick_dir_OFF,
};

CREATE_TASK(joystick_dir)

const float per_deg[8] = {337.5, 22.5, 67.5, 112.5, 157.5, 202.5, 247.5, 292.5};

float temp_deg = 0;
uint8_t r_Dir = 0;

typedef enum
{
  E = 10,
  NE,
  N,
  NW,
  W,
  SW,
  S,
  S_E,
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
  kxnTaskManager.add(this);
  setState(joystick_dir_ON);
  return this->r_Dir;
}

void read_Joystick(float deg)
{
  kDelay(0);
  this->temp_deg = deg;
  stop();
}

void stop()
{
  kDelay(0);
  setStateIdle();
}

bool resetData()
{
  this->temp_deg = 0;
  this->r_Dir = 0;
  if (this->temp_deg != 0 || this->r_Dir != 0)
    return false;
  return true;
}

END
