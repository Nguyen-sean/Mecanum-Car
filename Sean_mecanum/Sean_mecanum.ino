
#include "Gamepad_setup.h"
#include "Step_function.h"
// #include "Car_formula.h"
#include "Car_formula_GPT.h"
uint8_t GOC;
// Khởi tạo driver và tốc độ
void setup() {
  Serial.begin(115200);
  setup_step();
  Setup_Gamepad();
  myDriver1.begin();
  myDriver2.begin();
  // setSpeed(75); // Đặt tốc độ mặc định là 75%
  pinMode(11, OUTPUT);
  pinMode(A0, INPUT);
  // myDriver1.SetS1(90,140);
}

void loop() {
  Gamepad.getdata_Gamepad_I2C();
  if (Gamepad.Get_POT_R() != 0) { GOC = Gamepad.Get_POT_R(); }



  myDriver1.writeS1(map(GOC, 0, 100, 100, 130));
  if (Gamepad.Get_status_button_90D_Left() == true) {
    analogWrite(11, 20);
    motorRun(0, true);
  } else {
    analogWrite(11, 0);
  }

  // Gamepad_debug();
  // Di chuyển thẳng với tốc độ 75%
  // moveStraight_F(100);
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

  if (Gamepad.Get_RAD_Joy_L() > 10) {

    uint8_t Radius_speed = constrain(map(Gamepad.Get_RAD_Joy_L(), 0, 255, 0, 100), 60, 100);
    uint16_t DEG_joystick = constrain(Gamepad.Get_DEG_Joy_L(), 0, 360);
    if ((DEG_joystick >= 337.5) || (DEG_joystick < 22.5)) {
      // Serial.println("R");
      Radius_speed = constrain(Radius_speed, 90, 100);
      moveSideways_R(Radius_speed);
      // right();
    } else if (DEG_joystick >= 22.5 && DEG_joystick < 67.5) {
      // Serial.println("FR");
      moveDiagonalForwardRight(Radius_speed);
      // forwardright();
    } else if (DEG_joystick >= 67.5 && DEG_joystick < 112.5) {
      // Serial.println("F");
      moveStraight_F(Radius_speed);
      // forward();
    } else if (DEG_joystick >= 112.5 && DEG_joystick < 157.5) {
      // Serial.println("FL");
      moveDiagonalForwardLeft(Radius_speed);
      // forwardleft();
    } else if (DEG_joystick >= 157.5 && DEG_joystick < 202.5) {
      // Serial.println("L");
      Radius_speed = constrain(Radius_speed, 90, 100);
      moveSideways_L(Radius_speed);
      // left();
    } else if (DEG_joystick >= 202.5 && DEG_joystick < 247.5) {
      // Serial.println("BL");
      moveDiagonalBackwardLeft(Radius_speed);
      // backleft();
    } else if (DEG_joystick >= 247.5 && DEG_joystick < 292.5) {
      // Serial.println("B");
      moveStraight_B(Radius_speed);
      // back();
    } else if (DEG_joystick >= 292.5 && DEG_joystick < 337.5) {
      // Serial.println("BR");
      moveDiagonalBackwardRight(Radius_speed);
      // backright();
    }
    // Serial.println(Radius_speed);

  } else {
    stop();
  }
  Serial.println(analogRead(A0));
}