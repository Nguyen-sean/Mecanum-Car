#ifndef MKL_Gamepad_NRF24_SEAN__
#define MKL_Gamepad_NRF24_SEAN__

#include "Arduino.h"
#include "kxnTask.h"

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define MKL_Gamepad_TX_
// #define MKL_Gamepad_RX

#ifdef MKL_Gamepad_TX_
#define radio_TX
#endif

#ifdef MKL_Gamepad_RX_
#define radio_RX
#endif

DEFINE_TASK_STATE(MKL_Gamepad_NRF24){
    MKL_Gamepad_NRF24_TX_MODE,
    MKL_Gamepad_NRF24_RX_MODE,
};

CREATE_TASK(MKL_Gamepad_NRF24)
// CREATE_TASK(GamepadNRF)

private:
uint8_t _Pin_CE = 9;
uint8_t _Pin_CSN = 10;
// uint8_t Address = Address_RF_1;
uint8_t SetPAlever = RF24_PA_HIGH;
uint8_t Setchannel = 80;
rf24_datarate_e SetDataRate = RF24_250KBPS;

public:
RF24 radio_NRF;

MKL_Gamepad_NRF24()
{ // khởi tạo khi gọi hàm

    byte Address_RF_1[6] = "12345";
    // byte Address_RF_2[6] = "28592";
    // byte Address_RF_3[6] = "93189";
    // byte Address_RF_4[6] = "21659";
    // byte Address_RF_5[6] = "94591";
    // byte Address_RF_6[6] = "74683";
}

void begin(uint8_t Pin_CE, uint8_t Pin_CSN)
{
    radio_NRF.begin(Pin_CE, Pin_CSN);
    setPALevel(SetPAlever);
    setChannel(Setchannel);
    setDataRate(SetDataRate);
    start();
}

void begin(uint8_t Pin_CE, uint8_t Pin_CSN,  uint8_t SetPAlever, uint8_t Setchannel, rf24_datarate_e SetDataRate)
{

    radio_NRF.begin(Pin_CE, Pin_CSN);
    setPALevel(SetPAlever);
    setChannel(Setchannel);
    setDataRate(SetDataRate);
    start();
}

void start()
{
    kxnTaskManager.add(this);
#ifdef radio_TX
    setState(MKL_Gamepad_NRF24_TX_MODE);
#endif

#ifdef radio_RX
    setState(MKL_Gamepad_NRF24_RX_MODE);
#endif
}

void openWritingPipe(uint64_t value){
    radio_NRF.openWritingPipe(value);
}
void setPALevel(uint8_t _level) // Set mức khuếch đại PA
{
    radio_NRF.setPALevel(_level);
}
void setChannel(uint8_t channel) // Set channel cho NRF
{
    if (channel > 124)
    {
        channel = 124;
    }
    radio_NRF.setChannel(channel);
}
void setDataRate(rf24_datarate_e speed)
{
    radio_NRF.setDataRate(speed);
}

#ifdef radio_TX
void loop()
{
    // switch (getState()) {
    //     case MKL_Gamepad_NRF24_TX_MODE:
    //       // do something
    //       break;
    //     case MKL_Gamepad_NRF24_TX_MODE:
    //       // do something
    //       break;
    // }
}
#endif

END

#endif