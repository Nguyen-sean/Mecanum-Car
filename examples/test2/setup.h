#include "MKL_Gamepad.h"
#include "car_formula.h"
#include "joystick_dir.h"
#include "button.h"


MKL_Gamepad_RX sGamepad;

joystick_dir joyStick1;
joystick_dir joyStick2;

button leftJoyBTT;
button rightJoyBTT;


void setup_IIC();
void getData();

void setup_IIC()
{
  leftJoyBTT.setup();

  joyStick1.setup();
  joyStick2.setup();

  myDriver.begin();
  myDriver2.begin();

  sGamepad.Reset_data_Gamepad();
}

void getData()
{
  leftJoyBTT.read_Button(sGamepad.Get_status_button_90D_Left());
  rightJoyBTT.read_Button(sGamepad.Get_status_button_90D_Right());

  
  // Serial.println(leftJoyBTT.get_bt_Stt());

  joyStick1.read_Joystick(sGamepad.Get_DEG_Joy_L());
  joyStick2.read_Joystick(sGamepad.Get_DEG_Joy_R());

  // Serial.println(sGamepad.Get_RAD_Joy_R());

  sGamepad.Reset_data_Gamepad();
  sGamepad.getdata_Gamepad_I2C();

}