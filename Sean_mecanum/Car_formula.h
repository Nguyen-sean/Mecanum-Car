#include <Makerlabvn_I2C_Motor_Driver.h>
// Khởi tạo các driver điều khiển với địa chỉ I2C
Makerlabvn_I2C_Motor_Driver myDriver1(0);
Makerlabvn_I2C_Motor_Driver myDriver2(1);

/*
Đây là thứ tự bánh xe
          Đầu xe
motor_1 ---------- motor_2
-------------------------
motor_3 ---------- motor_4
*/

typedef enum
{
  Motor_FL = 1,
  Motor_FR = 2,
  Motor_BL = 3,
  Motor_BR = 4,
} car_wd_Select;

typedef enum
{
  counter_clockwise = 0,
  clockwise = 1,
} Motor_direct;

// Biến tốc độ toàn cục (từ 0 đến 100%)
uint8_t speed = 100;

// Thiết lập tốc độ từ 0 đến 100%
void setSpeed(uint8_t newSpeed) {
  if (newSpeed > 100) newSpeed = 100;
  speed = newSpeed;
}

// Hàm điều khiển từng động cơ với tỉ lệ phần trăm từ 0 đến 100
void setMotor1(bool direct, uint8_t motorSpeedPercent) {
  if (motorSpeedPercent > 100) motorSpeedPercent = 100;
  myDriver1.writeMA(direct, motorSpeedPercent);
}

void setMotor2(bool direct, uint8_t motorSpeedPercent) {
  if (motorSpeedPercent > 100) motorSpeedPercent = 100;
  myDriver2.writeMB(direct, motorSpeedPercent);
}

void setMotor3(bool direct, uint8_t motorSpeedPercent) {
  if (motorSpeedPercent > 100) motorSpeedPercent = 100;
  myDriver1.writeMB(direct, motorSpeedPercent);
}

void setMotor4(bool direct, uint8_t motorSpeedPercent) {
  if (motorSpeedPercent > 100) motorSpeedPercent = 100;
  myDriver2.writeMA(direct, motorSpeedPercent);
}

// Hàm điều khiển động cơ theo ID
//
 /*
Đây là thứ tự bánh xe

          Đầu xe
motor_1 ---------- motor_2
-------------------------
motor_3 ---------- motor_4
*/
void controlMotor(uint8_t motorID, bool direct, uint8_t motorSpeedPercent) {
  switch (motorID) {
    case 1:
      setMotor1(direct, motorSpeedPercent);
      break;
    case 2:
      setMotor2(direct, motorSpeedPercent);
      break;
    case 3:
      setMotor3(direct, motorSpeedPercent);
      break;
    case 4:
      setMotor4(direct, motorSpeedPercent);
      break;
    default:
      break;
  }
}

/*************************************************************************/
/*************************************************************************/
// Hàm di chuyển thẳng (forward hoặc backward)
void moveStraight_F(uint8_t speed) {
  setMotor1(clockwise, speed);
  setMotor2(clockwise, speed);
  setMotor3(clockwise, speed);
  setMotor4(clockwise, speed);
}

void moveStraight_B(uint8_t speed) {
  setMotor1(counter_clockwise, speed);
  setMotor2(counter_clockwise, speed);
  setMotor3(counter_clockwise, speed);
  setMotor4(counter_clockwise, speed);
}

/*************************************************************************/
/*************************************************************************/
// Hàm di chuyển ngang (trái hoặc phải)

void moveSideways_R(uint8_t speed) {
  setMotor1(clockwise, speed);
  setMotor2(counter_clockwise, speed);
  setMotor3(clockwise, speed);
  setMotor4(counter_clockwise, speed);
}

// Hàm di chuyển chéo
void moveDiagonal(bool direct, bool side) {
  if (side == 0) {  // left
    if (direct) {
      setMotor1(direct, 0);
      setMotor3(direct, 0);
      setMotor2(direct, speed);
      setMotor4(direct, speed);
    } else {
      setMotor2(direct, 0);
      setMotor4(direct, 0);
      setMotor1(direct, speed);
      setMotor3(direct, speed);
    }
  } else {  // right
    if (direct) {
      setMotor2(direct, 0);
      setMotor4(direct, 0);
      setMotor1(direct, speed);
      setMotor3(direct, speed);
    } else {
      setMotor1(direct, 0);
      setMotor3(direct, 0);
      setMotor2(direct, speed);
      setMotor4(direct, speed);
    }
  }
}

// Hàm di chuyển vòng cung
void moveArc(bool direct, bool side, uint8_t arcSpeedPercent) {
  if (arcSpeedPercent > 100) arcSpeedPercent = 100;
  if (side == 0) {  // left
    setMotor2(direct, arcSpeedPercent);
    setMotor3(direct, arcSpeedPercent);
    setMotor1(direct, 0);
    setMotor4(direct, 0);
  } else {  // right
    setMotor1(direct, arcSpeedPercent);
    setMotor4(direct, arcSpeedPercent);
    setMotor2(direct, 0);
    setMotor3(direct, 0);
  }
}

// Hàm xoay tại chỗ
void rotate(bool side, uint8_t rotateSpeedPercent) {
  if (rotateSpeedPercent > 100) rotateSpeedPercent = 100;
  setMotor1(side, rotateSpeedPercent);
  setMotor2(!side, rotateSpeedPercent);
  setMotor3(!side, rotateSpeedPercent);
  setMotor4(side, rotateSpeedPercent);
}

// Hàm xoay 45 đến 135 độ
void rotatePartial(bool wd, bool side, uint8_t partialSpeedPercent) {
  if (partialSpeedPercent > 100) partialSpeedPercent = 100;
  if (wd == 1) {  // front
    setMotor1(side, partialSpeedPercent);
    setMotor2(!side, partialSpeedPercent);
    setMotor3(side, 0);
    setMotor4(!side, 0);
  } else {  // back
    setMotor3(side, partialSpeedPercent);
    setMotor4(!side, partialSpeedPercent);
    setMotor1(!side, 0);
    setMotor2(side, 0);
  }
}

// Hàm dừng xe
void stop() {
  setMotor1(1, 0);
  setMotor2(1, 0);
  setMotor3(1, 0);
  setMotor4(1, 0);
}
