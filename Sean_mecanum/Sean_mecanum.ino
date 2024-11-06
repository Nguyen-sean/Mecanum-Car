// Macro tạo độ trễ không chặn, cho phép các tác vụ khác chạy trong khi đợi
#define time_delay(t) for (static uint32_t _lasttime; \
                           (uint32_t)((uint32_t)millis() - _lasttime) >= (t); \
                           _lasttime = millis())

#include "Gamepad_setup.h"
#include "Step_function.h"
// #include "Car_formula.h"
#include "Car_formula_GPT.h"
#include "Line_follow.h"

// Biến lưu tốc độ và góc cho joystick trái và phải
uint8_t Radius_speed_L = 0;
uint16_t DEG_joystick_L = 0;
uint8_t Radius_speed_R = 0;
uint16_t DEG_joystick_R = 0;

// Enum định nghĩa các góc của cánh tay robot
typedef enum {
  DEG_Open_full = 40,   // Góc mở hoàn toàn
  DEG_gap_banh = 102,   // Góc kẹp bánh
  DEG_Gap_co = 135      // Góc gập cánh tay
} DEG_cang_gap;

// Các biến trạng thái và điều khiển khác
uint8_t DEG_state = DEG_Open_full;
bool DEG_state_change = false;
bool DEG_gap_banh_change = false;
bool Is_motor180 = false;
bool Mode_change_IS_line_follow = false;

void setup() {
  Serial.begin(115200);           // Khởi động Serial với baud rate 115200
  setup_line_follow();             // Thiết lập chế độ đi theo đường
  setup_step();                    // Thiết lập bước động cơ
  Setup_Gamepad();                 // Thiết lập gamepad
  setup_motor_driver();            // Thiết lập điều khiển động cơ

  pinMode(13, OUTPUT);             // Cài đặt chân 13 làm output
  pinMode(11, OUTPUT);             // Cài đặt chân 11 làm output
  pinMode(A0, INPUT);              // Cài đặt chân A0 làm input
}

void loop() {
  Serial.println(analogRead(A0));  // Đọc giá trị analog từ chân A0 và in ra Serial

  // Nhận dữ liệu từ gamepad qua giao tiếp I2C
  Gamepad.getdata_Gamepad_I2C();

  // Chuyển đổi chế độ khi nhấn nút Right 90 độ và nút 1 cùng lúc
  time_delay(1000) {
    if (Gamepad.Get_status_button_90D_Right() && Gamepad.Get_status_button_1()) {
      Mode_change_IS_line_follow = !Mode_change_IS_line_follow;
    }
  }

  // Kiểm tra chế độ hiện tại
  if (Mode_change_IS_line_follow) {
    // Chế độ đi theo đường
    adjustMotorSpeed(read_line_Black());    // Điều chỉnh tốc độ dựa trên cảm biến line
    digitalWrite(13, HIGH);                 // Bật đèn báo
    myDriver1.writeS1(130);                 // Điều khiển động cơ 1
    myDriver2.writeS1(0);                   // Điều khiển động cơ 2

  } else {
    // Chế độ điều khiển thủ công
    digitalWrite(13, LOW);                  // Tắt đèn báo

    if (Is_motor180 == false) {
      Serial.println(analogRead(A0));       // Đọc giá trị analog từ chân A0 và in ra Serial
      
      // Điều khiển các góc của cánh tay robot dựa vào nút bấm trên gamepad
      if (Gamepad.Get_status_button_1()) {
        DEG_state = DEG_Open_full;
        DEG_state_change = true;
      }
      if (Gamepad.Get_status_button_2()) {
        time_delay(500) {
          DEG_state = (DEG_state != DEG_gap_banh) ? DEG_gap_banh : DEG_Open_full;
        }
        DEG_state_change = true;
      }
      if (Gamepad.Get_status_button_4()) {
        time_delay(500) {
          DEG_state = (DEG_state != DEG_Gap_co) ? DEG_Gap_co : DEG_Open_full;
        }
        DEG_state_change = true;
      }
      
      // Cập nhật góc của động cơ khi có thay đổi
      if (DEG_state_change) {
        myDriver2.writeS2(constrain(DEG_state, 40, 135));
        DEG_state_change = false;
      }

      // Điều khiển động cơ dựa vào các nút bấm khác
      if (Gamepad.Get_status_button_3()) {
        myDriver2.writeS2(constrain(DEG_gap_banh, 40, 135));
        stop();
        myDriver2.writeS1(140);
        delay(500);
        myDriver1.writeS1(130);
        myDriver2.writeS1(0);
        delay(500);
        myDriver2.writeS2(constrain(DEG_Open_full, 40, 135));
        delay(500);
        myDriver2.writeS1(map(Gamepad.Get_POT_R(), 100, 0, 0, 140));
        DEG_state = DEG_Open_full;
        delay(100);
      }
    }

    // Điều khiển động cơ chính dựa vào giá trị POT từ gamepad
    if (Gamepad.Get_POT_L() != 0) { myDriver1.writeS1(map(Gamepad.Get_POT_L(), 100, 0, 97, 130)); }
    if (Gamepad.Get_POT_R() != 0) { myDriver2.writeS1(map(Gamepad.Get_POT_R(), 100, 0, 0, 140)); }

    // Kiểm tra nút Left 90 độ và điều khiển motor quay 180 độ
    if (Gamepad.Get_status_button_90D_Left()) {
      analogWrite(11, 30);
      motorRun(3, true);
      Is_motor180 = true;
    } else {
      analogWrite(11, 0);
      Is_motor180 = false;
    }
/////////////////////////////////////////////////////////////////////////////////////////////////
    if (Gamepad.Get_status_button_90D_Right()) {
      Radius_speed_L = constrain(map(Gamepad.Get_RAD_Joy_L(), 0, 255, 60, 70), 60, 100);
      DEG_joystick_L = constrain(Gamepad.Get_DEG_Joy_L(), 0, 360);
      Radius_speed_R = constrain(map(Gamepad.Get_RAD_Joy_R(), 0, 255, 60, 60), 60, 100);
      DEG_joystick_R = constrain(Gamepad.Get_DEG_Joy_R(), 0, 360);
    } else {
      Radius_speed_L = constrain(map(Gamepad.Get_RAD_Joy_L(), 0, 255, 60, 100), 60, 100);
      DEG_joystick_L = constrain(Gamepad.Get_DEG_Joy_L(), 0, 360);
      Radius_speed_R = constrain(map(Gamepad.Get_RAD_Joy_R(), 0, 255, 60, 80), 60, 100);
      DEG_joystick_R = constrain(Gamepad.Get_DEG_Joy_R(), 0, 360);
    }


    // Điều khiển chuyển động dựa trên joystick bên phải
    if (Radius_speed_R > 10) {
      if ((DEG_joystick_R >= 315) || (DEG_joystick_R < 45)) {
        rotateClockwise(Radius_speed_R);         // Xoay theo chiều kim đồng hồ
      } else if (DEG_joystick_R >= 135 && DEG_joystick_R < 225) {
        rotateCounterClockwise(Radius_speed_R);  // Xoay ngược chiều kim đồng hồ
      }
    } else if (Radius_speed_L > 10) {
      // Điều khiển chuyển động dựa trên joystick bên trái
      if ((DEG_joystick_L >= 315) || (DEG_joystick_L < 45)) {
        moveSideways_R(Radius_speed_L);         // Di chuyển sang phải
      } else if (DEG_joystick_L >= 45 && DEG_joystick_L < 135) {
        moveStraight_F(Radius_speed_L);         // Tiến lên phía trước
      } else if (DEG_joystick_L >= 135 && DEG_joystick_L < 225) {
        moveSideways_L(Radius_speed_L);         // Di chuyển sang trái
      } else if (DEG_joystick_L >= 225 && DEG_joystick_L < 315) {
        moveStraight_B(Radius_speed_L);         // Lùi lại phía sau
      }
    } else {
      stop();  // Dừng nếu không có điều khiển nào từ joystick
    }
  }
}
