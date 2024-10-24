#include "kxnTask.h"
#include "MKL_Gamepad.h"
// #include "Oled_menu.h"
MKL_Gamepad_NRF24 radio;
byte Address_RF_1[6] = "12345";
void setup() {
  // put your setup code here, to run once:
// radio.begin(9,10);
// radio.setPALevel(RF24_PA_HIGH);
// radio.setChannel(80);
// radio.setDataRate(RF24_250KBPS);

radio.begin(9,10,Address_RF_1,RF24_PA_HIGH,80,RF24_250KBPS);
}

void loop() {
  // put your main code here, to run repeatedly:
// kxnTaskManager.run(millis());
}
