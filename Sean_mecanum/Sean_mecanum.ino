
#include "Gamepad_setup.h"
#include "Car_formula.h"

// Khởi tạo driver và tốc độ
void setup() {
  Serial.begin(115200);
  Setup_Gamepad();
  myDriver1.begin();
  myDriver2.begin();
  setSpeed(75); // Đặt tốc độ mặc định là 75%
  pinMode(11,OUTPUT);
  myDriver1.SetS1(90,140);
}

void loop() {
  Gamepad.getdata_Gamepad_I2C();

  myDriver1.writeS1(map(Gamepad.Get_POT_R(),0,100,90,140));
  digitalWrite(11,Gamepad.Get_status_Joystick_Button_Right());
// Gamepad_debug();
  // Di chuyển thẳng với tốc độ 75%
  moveStraight_F(100);
  // delay(1000);

  // // Điều khiển động cơ thứ 1 với tốc độ riêng 50%
  // controlMotor(Motor_FR, clockwise, 50); // Bánh trước trái tiến với tốc độ 50%
  // moveDiagonalForwardRight(100); 
  // delay(1000);

  // // Điều khiển động cơ thứ 3 với tốc độ riêng 30%
  // controlMotor(3, 0, 30); // Bánh sau trái lùi với tốc độ 30%
  // delay(1000);

  // // Xoay tại chỗ theo chiều kim đồng hồ với tốc độ 90%
  // rotate(1, 90);
  // delay(1000);

  // // Dừng xe
  // stop();
  // delay(1000);

  //   if (Gamepad.Get_RAD_Joy_L() > 10)
  // {
  //   uint16_t DEG_joystick_L = Gamepad.Get_DEG_Joy_L();
  //   uint16_t Speed_MT = Gamepad.Get_RAD_Joy_L();

  //   if (DEG_joystick_L >= 0 && DEG_joystick_L < 10)
  //   {
  //     // command = 'I';
  //     forwardright();
  //   }
  //   else if (DEG_joystick_L >= 10 && DEG_joystick_L < 80)
  //   {
  //     // command = 'I';
  //     forwardright();
  //   }
  //   else if (DEG_joystick_L >= 80 && DEG_joystick_L < 100) /// no change
  //   {
  //     // command = 'F';
  //     forward();
  //   }
  //   else if (DEG_joystick_L >= 100 && DEG_joystick_L < 170)
  //   {
  //     // command = 'G';
  //     forwardleft();
  //   }
  //   else if (DEG_joystick_L >= 170 && DEG_joystick_L < 180)
  //   {
  //     // command = 'G';
  //     Speed_MT = 150;
  //     forwardleft();
  //   }
  //   else if (DEG_joystick_L >= 180 && DEG_joystick_L < 190)
  //   {
  //     // command = 'H';
  //     Speed_MT = 150;
  //     backleft();
  //   }
  //   else if (DEG_joystick_L >= 190 && DEG_joystick_L < 260)
  //   {
  //     // command = 'H';
  //     backleft();
  //   }
  //   else if (DEG_joystick_L >= 260 && DEG_joystick_L < 280) /// no change
  //   {
  //     // command = 'B';
  //     back();
  //   }
  //   else if (DEG_joystick_L >= 280 && DEG_joystick_L < 350)
  //   {
  //     // command = 'J';
  //     backright();
  //   }
  //   else if (DEG_joystick_L >= 350 && DEG_joystick_L < 0)
  //   {
  //     // command = 'J';
  //     Speed_MT = 150;
  //     backright();
  //   }
  // }
}
