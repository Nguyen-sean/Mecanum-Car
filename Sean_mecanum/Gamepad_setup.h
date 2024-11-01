#include "MKL_Gamepad.h"

MKL_Gamepad_RX Gamepad;

void Setup_Gamepad(){
    Gamepad.Reset_data_Gamepad();
}

void Gamepad_debug(){
  Gamepad.getdata_Gamepad_I2C();

  uint16_t DEG_joystick_L = constrain(Gamepad.Get_DEG_Joy_L(), 0, 360);
  uint16_t DEG_joystick_R = constrain(Gamepad.Get_DEG_Joy_R(), 0, 360);
  // Wire.requestFrom(8, sizeof(Gamepad.Data_MKL_Gamepad_push));
  // while (Wire.available())
  // { // slave may send less than requested
  // Wire.readBytes((char *)&Gamepad.Data_MKL_Gamepad_push, sizeof(Gamepad.Data_MKL_Gamepad_push));
  // Serial.print(ratio_map);
  // Serial.print(" || ");
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
}

void GetData_gamepad(){
  Gamepad.getdata_Gamepad_I2C();
  
}