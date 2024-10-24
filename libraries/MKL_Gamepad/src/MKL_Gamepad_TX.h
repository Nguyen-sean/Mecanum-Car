#ifndef MKL_Gamepad_TX_SEAN__
#define MKL_Gamepad_TX_SEAN__
#include "kxnTask.h"

#include "lib_Gamepad/MKL_Gamepad_joystick.h"
#include "lib_Gamepad/MKL_Gamepad_Potential.h"

#define MKL_Gamepad_TX_

MKL_Gamepad_joystick joystick_L;
MKL_Gamepad_joystick joystick_R;
MKL_Gamepad_Potential Potential_L;
MKL_Gamepad_Potential Potential_R;

// DEFINE_TASK_STATE(MKL_Gamepad_TX){
//   TX_send,
//   khoiGT_ON_Y,
//   khoiGT_ON_G,
//   khoiGT_OFF,
// };

CREATE_TASK(MKL_Gamepad_TX)

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

// ---------------------------------------------------------------
// -------------------       Define Pin        -------------------
// ---------------------------------------------------------------
uint8_t Pin_Joystick_Ox_Left = A0;
uint8_t Pin_Joystick_Oy_Left = A1;
// uint8_t Pin_Joystick_Ox_Left = 2;
// uint8_t Pin_Joystick_Oy_Left = 2;
uint8_t Pin_Joystick_Button_Left = 1;

uint8_t Pin_Joystick_Ox_Right = A2;
uint8_t Pin_Joystick_Oy_Right = A3;
// uint8_t Pin_Joystick_Ox_Right = 2;
// uint8_t Pin_Joystick_Oy_Right = 3;
uint8_t Pin_Joystick_Button_Right = 0;

uint8_t Pin_Pot_left = A7;
uint8_t Pin_Pot_right = A6;
// uint8_t Pin_Pot_left = 7;
// uint8_t Pin_Pot_right = 6;

uint8_t button_1 = 4;
uint8_t button_2 = 5;
uint8_t button_3 = 6;
uint8_t button_4 = 7;

uint8_t button_90D_Left = 2;
uint8_t button_90D_Right = 3;

//
void SET_Pin_Joystick_Ox_Left(uint8_t _pin_Input) { this->Pin_Joystick_Ox_Left = _pin_Input; }
void SET_Pin_Joystick_Oy_Left(uint8_t _pin_Input) { this->Pin_Joystick_Oy_Left = _pin_Input; }
void SET_Pin_Joystick_Button_Left(uint8_t _pin_Input) { this->Pin_Joystick_Button_Left = _pin_Input; }
void SET_Pin_Joystick_Ox_Right(uint8_t _pin_Input) { this->Pin_Joystick_Ox_Right = _pin_Input; }
void SET_Pin_Joystick_Oy_Right(uint8_t _pin_Input) { this->Pin_Joystick_Oy_Right = _pin_Input; }
void SET_Pin_Joystick_Button_Right(uint8_t _pin_Input) { this->Pin_Joystick_Button_Right = _pin_Input; }
void SET_Pin_Pot_left(uint8_t _pin_Input) { this->Pin_Pot_left = _pin_Input; }
void SET_Pin_Pot_right(uint8_t _pin_Input) { this->Pin_Pot_right = _pin_Input; }
void SET_button_1(uint8_t _pin_Input) { this->button_1 = _pin_Input; }
void SET_button_2(uint8_t _pin_Input) { this->button_2 = _pin_Input; }
void SET_button_3(uint8_t _pin_Input) { this->button_3 = _pin_Input; }
void SET_button_4(uint8_t _pin_Input) { this->button_4 = _pin_Input; }
void SET_button_90D_Left(uint8_t _pin_Input) { this->button_90D_Left = _pin_Input; }
void SET_button_90D_Right(uint8_t _pin_Input) { this->button_90D_Right = _pin_Input; }

// ---------------------------------------------------------------
// -------------------     Setup_Gamepad       -------------------
// ---------------------------------------------------------------
const int buttonPins[8] = {button_1, button_2, button_3, button_4, button_90D_Left, button_90D_Right, Pin_Joystick_Button_Left, Pin_Joystick_Button_Right};

void Setup()
{
    for (int i = 0; i < 8; i++)
    {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }

    joystick_L.setup(Pin_Joystick_Ox_Left, Pin_Joystick_Oy_Left, Pin_Joystick_Button_Left);
    joystick_R.setup(Pin_Joystick_Ox_Right, Pin_Joystick_Oy_Right, Pin_Joystick_Button_Right);
    Potential_L.setup(Pin_Pot_left);
    Potential_R.setup(Pin_Pot_right);

    getdata_Gamepad();
}

void getdata_Gamepad()
{
    bitWrite(buttonStates, 0, digitalRead(button_1));
    bitWrite(buttonStates, 1, digitalRead(button_2));
    bitWrite(buttonStates, 2, digitalRead(button_3));
    bitWrite(buttonStates, 3, digitalRead(button_4));
    bitWrite(buttonStates, 4, digitalRead(button_90D_Left));
    bitWrite(buttonStates, 5, digitalRead(button_90D_Right));
    bitWrite(buttonStates, 6, digitalRead(Pin_Joystick_Button_Left));
    bitWrite(buttonStates, 7, digitalRead(Pin_Joystick_Button_Right));

    Data_MKL_Gamepad_push.buttons = buttonStates;
    Data_MKL_Gamepad_push.DEG_Joy_L = map(joystick_L.AngleDed(), 0, 359, 0, 255);
    Data_MKL_Gamepad_push.RAD_Joy_L = map(joystick_L.Radius(), 0, 512, 0, 255);
    Data_MKL_Gamepad_push.DEG_Joy_R = map(joystick_R.AngleDed(), 0, 359, 0, 255);
    Data_MKL_Gamepad_push.RAD_Joy_R = map(joystick_R.Radius(), 0, 512, 0, 255);
    Data_MKL_Gamepad_push.pot_L = map(Potential_L.readValue(), 0, 1023, 0, 100);
    Data_MKL_Gamepad_push.pot_R = map(Potential_R.readValue(), 0, 1023, 0, 100);
}

int Get_POT_L() { return Data_MKL_Gamepad_push.pot_L; }
int Get_POT_R() { return Data_MKL_Gamepad_push.pot_R; }
int Get_DEG_Joy_L() { return map(Data_MKL_Gamepad_push.DEG_Joy_L, 0, 255, 0, 359); }
int Get_DEG_Joy_R() { return map(Data_MKL_Gamepad_push.DEG_Joy_R, 0, 255, 0, 359); }
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

void Serial_check_Gamepab()
{
    Serial.print(Get_DEG_Joy_L());
    Serial.print(" || ");
    Serial.print(Get_RAD_Joy_L());
    Serial.print(" ||<==>|| ");
    Serial.print(Get_DEG_Joy_R());
    Serial.print(" || ");
    Serial.print(Get_RAD_Joy_R());
    Serial.print(" || ");
    Serial.print(Get_POT_L());
    Serial.print(" || ");
    Serial.print(Get_POT_R());
    Serial.print(" || ");
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

        for (size_t i = 0; i < sizeof(Data_MKL_Gamepad_push); i++)
        {
            dataPtr[i] = Wire.read(); // Đọc từng byte dữ liệu từ Arduino Uno
        }
    }
}

// void senddata_gamepad_I2C()
// {
//     Wire.begin(I2C_ADDRESS); // join I2C bus with address #8
//     Wire.onRequest(requestEvent);
// }
END

#endif