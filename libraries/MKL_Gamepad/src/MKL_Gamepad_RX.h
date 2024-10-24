#ifndef MKL_Gamepad_RX_SEAN__
#define MKL_Gamepad_RX_SEAN__
#include "kxnTask.h"

#define MKL_Gamepad_RX_

CREATE_TASK(MKL_Gamepad_RX)

byte buttonStates = 0;
struct DataPacket
{
    byte buttons;
    uint8_t DEG_Joy_L;
    uint8_t RAD_Joy_L;
    uint8_t RAD_Joy_R;
    uint8_t DEG_Joy_R;
    uint8_t pot_L;
    uint8_t pot_R;
    // bool Is_connect_NRF;
} Data_MKL_Gamepad_push;


void Reset_data_Gamepad() // đưa tất cả giá trị về low
{
    bitWrite(buttonStates, 0, 1);
    bitWrite(buttonStates, 1, 1);
    bitWrite(buttonStates, 2, 1);
    bitWrite(buttonStates, 3, 1);
    bitWrite(buttonStates, 4, 1);
    bitWrite(buttonStates, 5, 1);
    bitWrite(buttonStates, 6, 1);
    bitWrite(buttonStates, 7, 1);
    Data_MKL_Gamepad_push.buttons = buttonStates;

    Data_MKL_Gamepad_push.DEG_Joy_L = 0;
    Data_MKL_Gamepad_push.RAD_Joy_L = 0;
    Data_MKL_Gamepad_push.DEG_Joy_R = 0;
    Data_MKL_Gamepad_push.RAD_Joy_R = 0;
    Data_MKL_Gamepad_push.pot_L = 0;
    Data_MKL_Gamepad_push.pot_R = 0;

    // Serial.println( Potential_R.readValue());
}

int Get_POT_L() { return Data_MKL_Gamepad_push.pot_L; }
int Get_POT_R() { return Data_MKL_Gamepad_push.pot_R; }
int Get_DEG_Joy_L() { return map(Data_MKL_Gamepad_push.DEG_Joy_L, 0, 255, 0, 360); }
int Get_DEG_Joy_R() { return map(Data_MKL_Gamepad_push.DEG_Joy_R, 0, 255, 0, 360); }
int Get_RAD_Joy_L() { return Data_MKL_Gamepad_push.RAD_Joy_L; }
int Get_RAD_Joy_R() { return Data_MKL_Gamepad_push.RAD_Joy_R; }
bool Get_status_button_1() { return !bitRead(Data_MKL_Gamepad_push.buttons, 0); }
bool Get_status_button_2() { return !bitRead(Data_MKL_Gamepad_push.buttons, 1); }
bool Get_status_button_3() { return !bitRead(Data_MKL_Gamepad_push.buttons, 2); }
bool Get_status_button_4() { return !bitRead(Data_MKL_Gamepad_push.buttons, 3); }
bool Get_status_button_90D_Left() { return !bitRead(Data_MKL_Gamepad_push.buttons, 4); }
bool Get_status_button_90D_Right() { return !bitRead(Data_MKL_Gamepad_push.buttons, 5); }
bool Get_status_Joystick_Button_Left() { return !bitRead(Data_MKL_Gamepad_push.buttons, 6); }
bool Get_status_Joystick_Button_Right() { return !bitRead(Data_MKL_Gamepad_push.buttons, 7); }

void Serial_check_Gamepab()
{
    Serial.print(Get_DEG_Joy_L());
    Serial.print(" || ");
    Serial.print(Get_RAD_Joy_L());
    Serial.print(" ||<==>|| ");
    Serial.print(Get_DEG_Joy_R());
    Serial.print(" || ");
    Serial.print(Get_RAD_Joy_R());
    Serial.print(" ||<==>|| ");
    Serial.print(Get_POT_L());
    Serial.print(" || ");
    Serial.print(Get_POT_R());
    Serial.print(" ||<==>|| ");
    Serial.println(Data_MKL_Gamepad_push.buttons, BIN);
}

void senddata_Gamepad_I2C()
{
    // Wire.beginTransmission(I2C_ADDRESS); // transmit to device #8

    // Wire.write(__Gamepad_Data__->pot_L);
    // Wire.write(__Gamepad_Data__->pot_R);
    // Wire.write(__Gamepad_Data__->DEG_Joy_L);
    // Wire.write(__Gamepad_Data__->DEG_Joy_R);
    // Wire.write(__Gamepad_Data__->RAD_Joy_L);
    // Wire.write(__Gamepad_Data__->RAD_Joy_R);
    // Wire.write(__Gamepad_Data__->buttons);
    // Wire.endTransmission(); // stop transmitting
}

void getdata_Gamepad_I2C()
{
    Wire.requestFrom(I2C_ADDRESS, sizeof(Data_MKL_Gamepad_push));

    while (Wire.available())
    { // slave may send less than requested
        //   Wire.readBytes((char *)&Data_MKL_Gamepad_push, sizeof(Data_MKL_Gamepad_push));

        byte *dataPtr = (byte *)&Data_MKL_Gamepad_push; // Con trỏ tới dữ liệu

        for (size_t  i = 0; i < sizeof(Data_MKL_Gamepad_push); i++)
        {
            dataPtr[i] = Wire.read(); // Đọc từng byte dữ liệu từ Arduino Uno
        }

        // __Gamepad_Data__->pot_L = Wire.read();
        // __Gamepad_Data__->pot_R = Wire.read();
        // __Gamepad_Data__->DEG_Joy_L = Wire.read();
        // __Gamepad_Data__->DEG_Joy_R = Wire.read();
        // __Gamepad_Data__->RAD_Joy_L = Wire.read();
        // __Gamepad_Data__->RAD_Joy_R = Wire.read();
        // __Gamepad_Data__->buttons = Wire.read();

        // Data_MKL_Gamepad_push.pot_L = Wire.read();
        // Data_MKL_Gamepad_push.pot_R = Wire.read();
        // Data_MKL_Gamepad_push.DEG_Joy_L = Wire.read();
        // Data_MKL_Gamepad_push.DEG_Joy_R = Wire.read();

        // Data_MKL_Gamepad_push.RAD_Joy_L = Wire.read();
        // Data_MKL_Gamepad_push.RAD_Joy_R = Wire.read();

        // Data_MKL_Gamepad_push.buttons = Wire.read();
    }
}

// void senddata_gamepad_I2C()
// {
//     Wire.begin(I2C_ADDRESS); // join I2C bus with address #8
//     Wire.onRequest(requestEvent);
// }
END

#endif