#include "setup.h"

void setup(void)
{
  setup_IIC();
  Serial.begin(115200);
}

void loop(void)
{
  getData();
  Serial.println(sGamepad.Get_DEG_Joy_L());

  if (GamePad.isUpPressed())
  {
    // value = "UP";
    mov_str(forward);
  }
  else if (GamePad.isDownPressed())
  {
    // value = "DOWN";
    mov_str(backward);
  }
  else if (GamePad.isLeftPressed())
  {
    // value = "LEFT";
    mov_sdw(left);
  }
  else if (GamePad.isRightPressed())
  {
    // value = "RIGHT";
    mov_sdw(right);
  }
  else if (GamePad.isCirclePressed())
  {
    // mov_dia(forward, right);
    rotation(right);
  }
  else if (GamePad.isSquarePressed())
  {
    // mov_dia(forward, left);
    rotation(left);
  }
  else if (GamePad.isTrianglePressed())
  {
    // mov_dia(backward, left);
    rt_ard_p(front, left);
  }
  else if (GamePad.isCrossPressed())
  {
    // mov_dia(backward, right);
    rt_ard_p(front, right);
  }
  else if (GamePad.isSelectPressed())
  {
    // mov_ard_bd(forward, right);
    rt_ard_p(back, left);
  }
  else if (GamePad.isStartPressed())
  {
    // mov_ard_bd(backward, right);
    rt_ard_p(back, right);
  }
  else
  {
    // value = "0";
    stop();
  }
}
