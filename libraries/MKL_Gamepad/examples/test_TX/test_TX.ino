
/*
 * https://maniacbug.github.io/RF24/classRF24.html
 *
 * VCC - 3.3v
 * GND - GND
 * CSN - 10
 * CE - 9
 * SCK - 13 mặc định SPI
 * MOSI - 11 SPI
 * MISO - 12 SPI
 */
#include "MKL_Gamepad.h"
// #define AVR
MKL_Gamepad_TX Gamepad;

RF24 radio(9, 10);               // CE, CSN
const byte diachi[6] = "12345";  // Mảng kí tự dạng chuỗi có 6 kí tự

void setup() {
  Serial.begin(115200);
  // Gamepad.SET_Pin_Joystick_Ox_Left(A0);
  // Gamepad.SET_Pin_Joystick_Oy_Left(A1);
  // Gamepad.SET_Pin_Joystick_Button_Left(1);
  // Gamepad.SET_Pin_Joystick_Ox_Right(A2);
  // Gamepad.SET_Pin_Joystick_Oy_Right(A3);
  // Gamepad.SET_Pin_Joystick_Button_Right(0);
  // Gamepad.SET_Pin_Pot_left(A7);
  // Gamepad.SET_Pin_Pot_right(A6);
  // Gamepad.SET_button_1(4);
  // Gamepad.SET_button_2(5);
  // Gamepad.SET_button_3(6);
  // Gamepad.SET_button_4(7);
  // Gamepad.SET_button_90D_Left(2);
  // Gamepad.SET_button_90D_Right(3);
  Gamepad.Setup();

  while (!radio.begin()) {
    Serial.println("Module không khởi động được...!!");
    delay(10);
  }

  radio.openWritingPipe(diachi);
  // openWritingPipe defaul là đường truyền 0
  // mở 1 kênh có địa chỉ 12345 trên đường truyền 0
  //  kênh này ghi data lên địa chỉ 12345
  radio.setPALevel(RF24_PA_MAX);
  // RF24_PA_<MIN
  // RF24_PA_LOW
  // RF24_PA_HIGH
  // RF24_PA_MAX
  // Power of NRF24 at MIN, MAX, HIGH, LOW
  radio.setChannel(80);  // 125 kênh từ 0-124; TX và RX phải cùng kênh
                         // 2.4GHz ~ 2400Mhz, bước kênh là 1MHz
                         // setchannel(1) => 2401Mhz
                         // Cao nhất là 2525MHz, Tức là 2.525GHz

  radio.setDataRate(RF24_250KBPS);  // Tốc độ truyền dữ liệu trong không khí
                                    // 250kbps, 1Mbps hoặc 2Mbps
                                    // 250 thấp nhất nhưng truyền xa, 1Mb và 2Mb mạnh nhưng truyền không xa
  /*
   * Tốc độ truyền dữ liệu không khí 2Mbps, băng thông 2MHz bị chiếm dụng nhiều tần số kênh
   * rộng hơn độ phân giải của cài đặt tần số kênh RF
   * Vì vậy, để đảm bảo các kênh không chồng chéo và giảm kết nối chéo ở chế độ 2Mbps
   * bạn cần giữ khoảng cách 2MHz giữa hai kênh.
   *
   * A: Xe TX-RX kênh 80, tốc độ truyền là 2Mb 80, 81, 82
   * B: Máy bay TX-RX kênh 83, tốc độ truyền là 250Kb
   */
  radio.stopListening();  // Cài đặt module là TX

  if (!radio.available()) {
    Serial.println("Chưa kết nối được với RX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  }
}

void loop() {

  Gamepad.getdata_Gamepad();
  // Gamepad.senddata_Gamepad_I2C();
  radio.write(&Gamepad.Data_MKL_Gamepad_push, sizeof(Gamepad.Data_MKL_Gamepad_push));
   
// Gamepad.Serial_check_Gamepab();

  // &: Trả lại địa chỉ của một biến.
  // sizeof: trả về số byte bộ nhớ của một biến
  // hoặc là trả về tổng số byte bộ nhớ của một mảng

  // Serial.println(Data_MKL_Gamepad_push.buttons,BIN);
  // delay(1000);
}

