#pragma once

#include "kxnTask.h"

DEFINE_TASK_STATE(joystick_dir){
    joystick_dir_ON,
    joystick_dir_OFF,
};

CREATE_TASK(joystick_dir)
/*Add your variable here*/
const uint8_t count_for_deg = 8;
const _Float16 for_deg[8] = {337.5, 22.5, 67.5, 112.5, 157.5, 202.5, 247.5, 292.5};

_Float16 temp_deg = 0;
void setup(_Float16 deg)
{
  /*Add your code setup here*/
  this->temp_deg = deg;
  stop();
}

enum
{
  N,
  W,
  S,
  E,
  NW,
  SW,
  SE,
  NE,
};

// for (uint8_t i = 0; i < this->count_for_deg; i++)
// {
//   if (/* condition */)
//   {
//     /* code */
//   }

//   if (this->temp_deg >= for_deg[count_for_deg] && this->temp_deg < for_deg[count_for_deg + 1])
//   {
//   }
// }

void loop()
{
  if (this->temp_deg >= for_deg[0] || this->temp_deg < for_deg[1])
  {
    // command = 'I';

    // forwardright();
    return E;
  }
  else if (this->temp_deg >= for_deg[1] && this->temp_deg < for_deg[2])
  {
    // command = 'I';
    // forwardright();
    return NE;
  }
  else if (this->temp_deg >= for_deg[2] && this->temp_deg < for_deg[3]) /// no change
  {
    // command = 'F';
    forward();
    return N;
  }
  else if (this->temp_deg >= for_deg[3] && this->temp_deg < for_deg[4])
  {
    // command = 'G';
    // forwardleft();
    return NW;
  }
  else if (this->temp_deg >= for_deg[4] && this->temp_deg < for_deg[5])
  {
    // command = 'G';

    // forwardleft();
    return W;
  }
  else if (this->temp_deg >= for_deg[5] && this->temp_deg < for_deg[6])
  {
    // command = 'H';

    // backleft();
    return SW;
  }
  else if (this->temp_deg >= for_deg[6] && this->temp_deg < for_deg[7])
  {
    // command = 'H';
    // backleft();
    return S;
  }

  else if (this->temp_deg >= for_deg[7] && this->temp_deg < for_deg[0])
  {
    // command = 'H';
    // backleft();
    return SE;
  }
}

void start()
{
  kxnTaskManager.add(this);
  setState(joystick_dir_ON);
}

void stop()
{
  kDelay(0);
  setStateIdle();
}

END