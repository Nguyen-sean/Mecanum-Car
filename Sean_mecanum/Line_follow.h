#include <QTRSensors.h>

QTRSensors qtr;
const uint8_t SensorCount = 2;  // Số lượng cảm biến là 2
uint16_t sensors[SensorCount];  // Mảng lưu giá trị cảm biến

void setup_line_follow() {
  // Thiết lập cảm biến
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){ A1, A2 }, SensorCount);
  // Hiệu chỉnh cảm biến
  // for (uint16_t i = 0; i < 400; i++) {
  qtr.calibrate();
  // delay(20);
  // }
  qtr.calibrationOn.minimum[0] = 462;  // trái
  qtr.calibrationOn.maximum[0] = 792;

  qtr.calibrationOn.minimum[1] = 446;  // phải
  qtr.calibrationOn.maximum[1] = 795;
}
int16_t read_line_Black() {
  return qtr.readLineBlack(sensors);
}