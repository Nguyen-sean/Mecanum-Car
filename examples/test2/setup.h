#include "MKL_Gamepad.h"
#include "car_formula.h"
#include "joystick_dir.h"

MKL_Gamepad_RX sGamepad;
joystick_dir joyStick1;
joystick_dir joyStick2;


#define TX_PIN 12
#define RX_PIN 13

void setup_IIC();
void getData();



void setup_IIC()
{
  joyStick1.setup();
  joyStick2.setup();

  myDriver.begin();
  myDriver2.begin();

  sGamepad.Reset_data_Gamepad();
}

void getData()
{
  joyStick1.read_Joystick(sGamepad.Get_DEG_Joy_L());
  joyStick2.read_Joystick(sGamepad.Get_DEG_Joy_R());


  sGamepad.Reset_data_Gamepad();
  sGamepad.getdata_Gamepad_I2C();

  bt_left = sGamepad.Get_status_button_90D_Left();
bt_right = sGamepad.Get_status_button_90D_Right();
}