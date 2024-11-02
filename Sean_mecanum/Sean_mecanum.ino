#define time_delay(t) for (static uint32_t _lasttime; \
                           (uint32_t)((uint32_t)millis() - _lasttime) >= (t); \
                           _lasttime = millis())

#include "Gamepad_setup.h"
#include "Step_function.h"
// #include "Car_formula.h"
#include "Car_formula_GPT.h"
#include "Line_follow.h"

uint8_t Radius_speed_L = 0;
uint16_t DEG_joystick_L = 0;
uint8_t Radius_speed_R = 0;
uint16_t DEG_joystick_R = 0;

typedef enum {
  DEG_Open_full = 40,
  DEG_gap_banh = 102,
  DEG_Gap_co = 135,
} DEG_cang_gap;


uint8_t DEG_state = DEG_Open_full;
bool DEG_state_change = false;
bool DEG_gap_banh_change = false;
bool Is_motor180 = false;

bool Mode_change_IS_line_follow = false;

void setup() {
  Serial.begin(115200);
  setup_line_follow();
  setup_step();
  Setup_Gamepad();
  setup_motor_driver();

  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(A0, INPUT);
}

void loop() {
  Serial.println(analogRead(A0));
  // Gamepad_debug();

  Gamepad.getdata_Gamepad_I2C();
  //////////////////////////////////////////////////
  time_delay(1000) {
    if (Gamepad.Get_status_button_90D_Right() && Gamepad.Get_status_button_1()) {
      Mode_change_IS_line_follow = !Mode_change_IS_line_follow;
    }
  }

  if (Mode_change_IS_line_follow) {
    adjustMotorSpeed(read_line_Black());
    digitalWrite(13, HIGH);
    myDriver1.writeS1(130);
    myDriver2.writeS1(0);

  } else {
    digitalWrite(13, LOW);
    if (Is_motor180 == false) {
      Serial.println(analogRead(A0));
      if (Gamepad.Get_status_button_1()) {
        DEG_state = DEG_Open_full;
        DEG_state_change = true;
      }
      if (Gamepad.Get_status_button_2()) {
        time_delay(250) {
          if (DEG_state != DEG_gap_banh) {
            DEG_state = DEG_gap_banh;
          } else {
            DEG_state = DEG_Open_full;
          }
        }
        DEG_state_change = true;
      }
      if (Gamepad.Get_status_button_4()) {
        time_delay(250) {
          if (DEG_state != DEG_Gap_co) {
            DEG_state = DEG_Gap_co;
          } else {
            DEG_state = DEG_Open_full;
          }
        }
        DEG_state_change = true;
      }
      Serial.println(DEG_state);
      if (DEG_state_change) {
        myDriver2.writeS2(constrain(DEG_state, 40, 135));
        DEG_state_change = false;
      }

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
        // myDriver2.writeS1(30);
        myDriver2.writeS1(map(Gamepad.Get_POT_L(), 100, 0, 0, 140));
        DEG_state = DEG_Open_full;
        delay(100);
      }
    }

    if (Gamepad.Get_POT_R() != 0) { myDriver1.writeS1(map(Gamepad.Get_POT_R(), 100, 0, 105, 130)); }
    if (Gamepad.Get_POT_L() != 0) { myDriver2.writeS1(map(Gamepad.Get_POT_L(), 100, 0, 0, 140)); }
    if (Gamepad.Get_status_button_90D_Left()) {
      analogWrite(11, 25);
      motorRun(3, true);
      Is_motor180 = true;
    } else {
      analogWrite(11, 0);
      Is_motor180 = false;
    }

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

    // if (Gamepad.Get_RAD_Joy_L() > 10 && Gamepad.Get_RAD_Joy_R() > 10) {
    //   // Serial.println("both");

    // }
    if (Gamepad.Get_RAD_Joy_R() > 10) {
      // Serial.println("R");
      if ((DEG_joystick_R >= 315) || (DEG_joystick_R < 45)) {

        rotateClockwise(Radius_speed_R);
        // right
      } else if (DEG_joystick_R >= 45 && DEG_joystick_R < 135) {

      } else if (DEG_joystick_R >= 135 && DEG_joystick_R < 225) {

        rotateCounterClockwise(Radius_speed_R);

      } else if (DEG_joystick_R >= 225 && DEG_joystick_R < 315) {
      }
    } else if (Gamepad.Get_RAD_Joy_L() > 10) {
      // Serial.println("L");
      if ((DEG_joystick_L >= 315) || (DEG_joystick_L < 45)) {
        // Serial.println("R");
        // Radius_speed_L = constrain(map(Gamepad.Get_RAD_Joy_L(), 0, 255, 60 , 70), 0, 100);
        moveSideways_R(Radius_speed_L);
        // right
      } else if (DEG_joystick_L >= 45 && DEG_joystick_L < 135) {
        moveStraight_F(Radius_speed_L);
        // forward
      } else if (DEG_joystick_L >= 135 && DEG_joystick_L < 225) {
        // Serial.println("F");
        moveSideways_L(Radius_speed_L);
        // forward();
      } else if (DEG_joystick_L >= 225 && DEG_joystick_L < 315) {
        // Serial.println("FL");
        Radius_speed_L = constrain(Radius_speed_L, 60, 80);
        moveStraight_B(Radius_speed_L);
        // forwardleft();
      }
    } else {
      stop();
    }
  }
}