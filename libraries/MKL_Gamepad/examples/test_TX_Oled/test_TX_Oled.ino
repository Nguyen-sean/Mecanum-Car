
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
#include "kxnTask.h"
#include "MKL_Gamepad.h"
#include "Oled_menu.h"

// #define AVR
MKL_Gamepad_TX Gamepad;
Oled_menu menu;

RF24 radio;               // CE, CSN
const byte diachi[6] = "12345";  // Mảng kí tự dạng chuỗi có 6 kí tự

void setup() {
  Serial.begin(115200);
  Gamepad.Setup();

  while (!radio.begin(9,10)) {
    Serial.println("Module không khởi động được...!!");
    delay(10);
  }

  radio.openWritingPipe(diachi);

  radio.setPALevel(RF24_PA_MAX);

  radio.setChannel(80);

  radio.setDataRate(RF24_250KBPS);

  radio.stopListening();  // Cài đặt module là TX

  if (!radio.available()) {
    Serial.println("Chưa kết nối được với RX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  }

  menu.setup();

  if ((Gamepad.Get_status_button_90D_Left() == 0) & (Gamepad.Get_status_button_90D_Right() == 0)) {
    menu.start();
  }
}

void loop() {

  kxnTaskManager.run(millis());
  Gamepad.getdata_Gamepad();
  // Gamepad.senddata_Gamepad_I2C();
  radio.write(&Gamepad.Data_MKL_Gamepad_push, sizeof(Gamepad.Data_MKL_Gamepad_push));

  // Gamepad.Serial_check_Gamepab();
}
