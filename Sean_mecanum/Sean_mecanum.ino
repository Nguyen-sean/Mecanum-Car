

#include "Car_formula.h"

// Khởi tạo driver và tốc độ
void setup() {
  myDriver1.begin();
  myDriver2.begin();
  setSpeed(75); // Đặt tốc độ mặc định là 75%
}

void loop() {
  // Di chuyển thẳng với tốc độ 75%
  // moveStraight(1);
  // delay(1000);

  // // Điều khiển động cơ thứ 1 với tốc độ riêng 50%
  // controlMotor(Motor_FR, clockwise, 50); // Bánh trước trái tiến với tốc độ 50%
  // moveDiagonalForwardRight(100); 
  delay(1000);

  // // Điều khiển động cơ thứ 3 với tốc độ riêng 30%
  // controlMotor(3, 0, 30); // Bánh sau trái lùi với tốc độ 30%
  // delay(1000);

  // // Xoay tại chỗ theo chiều kim đồng hồ với tốc độ 90%
  // rotate(1, 90);
  // delay(1000);

  // // Dừng xe
  stop();
  delay(1000);
}
