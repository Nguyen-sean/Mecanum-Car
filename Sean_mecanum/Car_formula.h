#include <Makerlabvn_I2C_Motor_Driver.h>
// Khởi tạo các driver điều khiển với địa chỉ I2C
Makerlabvn_I2C_Motor_Driver myDriver1(0);
Makerlabvn_I2C_Motor_Driver myDriver2(1);

#define CONFIG_Motor_1 1
#define CONFIG_Motor_2 1
#define CONFIG_Motor_3 1
#define CONFIG_Motor_4 1

/*
Đây là thứ tự bánh xe
          Đầu xe
motor_1 ---------- motor_2
-------------------------
motor_3 ---------- motor_4
*/

typedef enum {
  Motor_FL = 1,
  Motor_FR = 2,
  Motor_BL = 3,
  Motor_BR = 4,
} car_wd_Select;

typedef enum {
  counter_clockwise = 0,
  clockwise = 1,
} Motor_direct;

void setup_motor_driver() {
  myDriver1.begin();
  myDriver2.begin();
}

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
  if (direct) {
    myDriver1.writeMA(direct, motorSpeedPercent * CONFIG_Motor_1);
  } else {
    myDriver1.writeMA(direct, motorSpeedPercent * CONFIG_Motor_1);
  }
}

void setMotor2(bool direct, uint8_t motorSpeedPercent) {
  if (motorSpeedPercent > 100) motorSpeedPercent = 100;
  if (direct) {
    myDriver2.writeMB(direct, motorSpeedPercent * CONFIG_Motor_2);
  } else {
    myDriver2.writeMB(direct, motorSpeedPercent * CONFIG_Motor_2);
  }
}

void setMotor3(bool direct, uint8_t motorSpeedPercent) {
  if (motorSpeedPercent > 100) motorSpeedPercent = 100;
  if (direct) {
    myDriver1.writeMB(direct, motorSpeedPercent * CONFIG_Motor_3);
  } else {
    myDriver1.writeMB(direct, motorSpeedPercent * CONFIG_Motor_3);
  }
}

void setMotor4(bool direct, uint8_t motorSpeedPercent) {
  if (motorSpeedPercent > 100) motorSpeedPercent = 100;
  if (direct) {
    myDriver2.writeMA(direct, motorSpeedPercent * CONFIG_Motor_4);
  } else {
    myDriver2.writeMA(direct, motorSpeedPercent * CONFIG_Motor_4);
  }
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
  setMotor3(counter_clockwise, speed);
  setMotor4(clockwise, speed);
}

void moveSideways_L(uint8_t speed) {
  setMotor1(counter_clockwise, speed);
  setMotor2(clockwise, speed);
  setMotor3(clockwise, speed);
  setMotor4(counter_clockwise, speed);
}
/*************************************************************************/
/*************************************************************************/
// Hàm đi chéo về phía trước bên phải
void moveDiagonalForwardRight(uint8_t speedPercent) {
  setMotor1(1, speedPercent);  // Bánh trước bên trái
  setMotor2(1, 0);             // Bánh trước bên phải dừng
  setMotor3(1, 0);             // Bánh sau bên trái
  setMotor4(1, speedPercent);  // Bánh sau bên phải dừng
}

// Hàm đi chéo về phía trước bên trái
void moveDiagonalForwardLeft(uint8_t speedPercent) {
  setMotor1(1, 0);             // Bánh trước bên trái dừng
  setMotor2(1, speedPercent);  // Bánh trước bên phải
  setMotor3(1, speedPercent);  // Bánh sau bên trái dừng
  setMotor4(1, 0);             // Bánh sau bên phải
}

// Hàm đi chéo về phía sau bên phải
void moveDiagonalBackwardRight(uint8_t speedPercent) {
  setMotor1(0, 0);             // Bánh trước bên trái dừng
  setMotor2(0, speedPercent);  // Bánh trước bên phải
  setMotor3(0, speedPercent);  // Bánh sau bên trái dừng
  setMotor4(0, 0);             // Bánh sau bên phải
}

// Hàm đi chéo về phía sau bên trái
void moveDiagonalBackwardLeft(uint8_t speedPercent) {
  setMotor1(0, speedPercent);  // Bánh trước bên trái
  setMotor2(0, 0);             // Bánh trước bên phải dừng
  setMotor3(0, 0);             // Bánh sau bên trái
  setMotor4(0, speedPercent);  // Bánh sau bên phải dừng
}

// // Hàm đi vòng cung về phía trước bên trái
// void moveArcForwardLeft(uint8_t speedPercent) {
//   setMotor2(1, speedPercent); // Bánh trước bên phải
//   setMotor3(1, speedPercent); // Bánh sau bên trái
//   setMotor1(1, 0);            // Bánh trước bên trái dừng
//   setMotor4(1, 0);            // Bánh sau bên phải dừng
// }

// // Hàm đi vòng cung về phía trước bên phải
// void moveArcForwardRight(uint8_t speedPercent) {
//   setMotor1(1, speedPercent); // Bánh trước bên trái
//   setMotor4(1, speedPercent); // Bánh sau bên phải
//   setMotor2(1, 0);            // Bánh trước bên phải dừng
//   setMotor3(1, 0);            // Bánh sau bên trái dừng
// }

// // Hàm đi vòng cung về phía sau bên trái
// void moveArcBackwardLeft(uint8_t speedPercent) {
//   setMotor3(0, speedPercent); // Bánh sau bên trái
//   setMotor2(0, speedPercent); // Bánh trước bên phải
//   setMotor1(0, 0);            // Bánh trước bên trái dừng
//   setMotor4(0, 0);            // Bánh sau bên phải dừng
// }

// // Hàm đi vòng cung về phía sau bên phải
// void moveArcBackwardRight(uint8_t speedPercent) {
//   setMotor1(0, speedPercent); // Bánh trước bên trái
//   setMotor4(0, speedPercent); // Bánh sau bên phải
//   setMotor2(0, 0);            // Bánh trước bên phải dừng
//   setMotor3(0, 0);            // Bánh sau bên trái dừng
// }

// Hàm xoay tại chỗ theo chiều kim đồng hồ
void rotateClockwise(uint8_t speedPercent) {
  setMotor1(1, speedPercent);
  setMotor2(0, speedPercent);
  setMotor3(1, speedPercent);
  setMotor4(0, speedPercent);
}

// Hàm xoay tại chỗ ngược chiều kim đồng hồ
void rotateCounterClockwise(uint8_t speedPercent) {
  setMotor1(0, speedPercent);
  setMotor2(1, speedPercent);
  setMotor3(0, speedPercent);
  setMotor4(1, speedPercent);
}

// Hàm dừng xe
void stop() {
  setMotor1(1, 0);
  setMotor2(1, 0);
  setMotor3(1, 0);
  setMotor4(1, 0);
}

void adjustMotorSpeed(int16_t position) {
  int16_t error = position - 500;  // 500 là điểm giữa

  // Tốc độ cơ bản của động cơ
  int16_t baseSpeed = 50;          // Tốc độ cơ bản thấp hơn giới hạn tối đa
  float Kp = 0.7;                   // Hệ số tỷ lệ để điều chỉnh độ nhạy
  int16_t correction = Kp * error;  // Tính độ lệch dựa trên sai số

  // Tính tốc độ của mỗi động cơ, đảm bảo không vượt quá 100
  int16_t leftMotorSpeed = baseSpeed + correction;
  int16_t rightMotorSpeed = baseSpeed - correction;

  // Giới hạn tốc độ trong khoảng 0 đến 100
  leftMotorSpeed = constrain(leftMotorSpeed, 0, 100);
  rightMotorSpeed = constrain(rightMotorSpeed, 0, 100);

  // Hiển thị tốc độ để kiểm tra
  // Serial.print("Tốc độ động cơ trái: ");
  // Serial.print(leftMotorSpeed);
  // Serial.print("\tTốc độ động cơ phải: ");
  // Serial.println(rightMotorSpeed);
  if (leftMotorSpeed < 5) {
    setMotor1(0, 10);
    setMotor2(1, rightMotorSpeed);
    setMotor3(0, 10);
    setMotor4(1, rightMotorSpeed);
  } else if (rightMotorSpeed < 5) {
    setMotor1(1, leftMotorSpeed);
    setMotor2(0, 10);
    setMotor3(1, leftMotorSpeed);
    setMotor4(0, 10);
  } else {
    setMotor1(1, leftMotorSpeed);
    setMotor2(1, rightMotorSpeed);
    setMotor3(1, leftMotorSpeed);
    setMotor4(1, rightMotorSpeed);
  }
}