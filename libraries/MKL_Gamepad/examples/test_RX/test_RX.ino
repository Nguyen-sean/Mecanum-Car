
/*
 * https://maniacbug.github.io/RF24/classRF24.html
 *
 * VCC - 3.3v
 * GND - GND
 * CSN - 10
 * CE - 9
 * SCK - 13
 * MOSI - 11
 * MISO - 12
 */
#include "MKL_Gamepad.h"

#define AVR
#include <Wire.h>

MKL_Gamepad Gamepad;

RF24 radio(9, 10); // CE, CSN
const byte diachi[6] = "12345";
unsigned long lastReceivedTime = 0;

void setup()
{
  Serial.begin(115200);

  Wire.begin(8); // join I2C bus with address #8
  Wire.onRequest(requestEvent);

  if (!radio.begin())
  {
    Serial.println("Module không khởi động được...!!");
    while (1)
    {
    }
  }

  radio.openReadingPipe(1, diachi);
  // Lệnh openReadingPipe có số đường truyền từ 0-5
  // Nhưng đường 0 đã được dùng cho ghi (mặc định)
  // Vì vậy chỉ dùng 1-5, nếu dùng không sẽ bị chồng lấn
  // Mở 1 kênh có địa chỉ 12345 trên đường truyền 1
  // kênh này chỉ đọc data trên địa chỉ 12345
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(80);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
}

void loop()
{
  if (radio.available())
  {
    radio.read(&Gamepad.Data_MKL_Gamepad_push, sizeof(Gamepad.Data_MKL_Gamepad_push));
    Serial.print(Gamepad.Data_MKL_Gamepad_push.DEG_Joy_L);
    Serial.print(" || ");
    Serial.print(Gamepad.Data_MKL_Gamepad_push.RAD_Joy_L);
    Serial.print(" ||<==>|| ");
    Serial.print(Gamepad.Data_MKL_Gamepad_push.DEG_Joy_R);
    Serial.print(" || ");
    Serial.print(Gamepad.Data_MKL_Gamepad_push.RAD_Joy_R);
    Serial.print(" || ");
    Serial.print(Gamepad.Data_MKL_Gamepad_push.pot_L);
    Serial.print(" || ");
    Serial.print(Gamepad.Data_MKL_Gamepad_push.pot_R);
    Serial.print(" || ");
    Serial.println(Gamepad.Data_MKL_Gamepad_push.buttons, BIN);
    lastReceivedTime = millis();
  }

  if (millis() - lastReceivedTime > 100)
  {
    Serial.println("NRF24L01 is disconnected");
    Gamepad.Reset_data_Gamepad();
  }
  
}

void requestEvent()
{
  Wire.write((byte *)&Gamepad.Data_MKL_Gamepad_push, sizeof(Gamepad.Data_MKL_Gamepad_push));
  // Gamepad.senddata_Gamepad_I2C();
}
