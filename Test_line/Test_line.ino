#include <QTRSensors.h>

QTRSensors qtr;
const uint8_t SensorCount = 2;  // Số lượng cảm biến là 2
uint16_t sensors[SensorCount];  // Mảng lưu giá trị cảm biến

#include <Makerlabvn_I2C_Motor_Driver.h>
// Khởi tạo các driver điều khiển với địa chỉ I2C
Makerlabvn_I2C_Motor_Driver myDriver1(0);
Makerlabvn_I2C_Motor_Driver myDriver2(1);


#define CONFIG_Motor_1 0.8
#define CONFIG_Motor_2 0.8
#define CONFIG_Motor_3 1
#define CONFIG_Motor_4 0.8




void setMotor1(bool direct, uint8_t motorSpeedPercent) {
  if (motorSpeedPercent > 100) motorSpeedPercent = 100;
  if (direct) {
    myDriver1.writeMA(direct, motorSpeedPercent * CONFIG_Motor_1);
  } else {
    myDriver1.writeMA(direct, motorSpeedPercent * CONFIG_Motor_1 * 0.83);
  }
}

void setMotor2(bool direct, uint8_t motorSpeedPercent) {
  if (motorSpeedPercent > 100) motorSpeedPercent = 100;
  if (direct) {
    myDriver2.writeMB(direct, motorSpeedPercent * CONFIG_Motor_2);
  } else {
    myDriver2.writeMB(direct, motorSpeedPercent * CONFIG_Motor_2 * 0.97);
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
    myDriver2.writeMA(direct, motorSpeedPercent * CONFIG_Motor_4 * 0.87);
  }
}



void setup() {
  // Thiết lập cảm biến
  myDriver1.begin();
  myDriver2.begin();
  myDriver1.writeS1(130);
  myDriver2.writeS1(0);

  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){ A1, A2 }, SensorCount);
  Serial.begin(115200);


  // Hiệu chỉnh cảm biến
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  // for (uint16_t i = 0; i < 400; i++) {
    qtr.calibrate();
    // delay(20);
  // }

  qtr.calibrationOn.minimum[0] = 462;
  qtr.calibrationOn.maximum[0] = 702;

  qtr.calibrationOn.minimum[1] = 446;
  qtr.calibrationOn.maximum[1] = 705;

  digitalWrite(LED_BUILTIN, LOW);
}

// Hàm xử lý điều chỉnh động cơ
void adjustMotorSpeed(int16_t position) {
  int16_t error = position - 500;  // 500 là điểm giữa

  // Tốc độ cơ bản của động cơ
  int16_t baseSpeed = 70;           // Tốc độ cơ bản thấp hơn giới hạn tối đa
  float Kp = 0.2;                   // Hệ số tỷ lệ để điều chỉnh độ nhạy
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

  setMotor1(1, leftSpeed);
  setMotor2(1, rightSpeed);
  setMotor3(1, leftSpeed);
  setMotor4(1, rightSpeed);
}

void loop() {
  // Đọc vị trí đường thẳng với 2 cảm biến
  int16_t position = qtr.readLineBlack(sensors);

  // Gọi hàm điều chỉnh tốc độ động cơ dựa trên vị trí đường
  adjustMotorSpeed(position);

  // delay(100); // Điều chỉnh lại sau mỗi 100 ms
}
