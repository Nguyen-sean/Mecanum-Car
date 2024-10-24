

// #define AVR_sean



enum Motor_direction {
  Stop_Motor,
  Clockwise,
  Counter_Clockwise
};

typedef enum Num_Motor {
  Motor_1,
  Motor_2,
  Motor_3,
  Motor_4
};

const int motor1_in1 = 15;
const int motor1_in2 = 16;
// Motor 2
const int motor2_in1 = 13;
const int motor2_in2 = 14;
// Motor 3
const int motor3_in1 = 39;
const int motor3_in2 = 38;
// Motor 4
const int motor4_in1 = 41;
const int motor4_in2 = 40;

int ratio_map = 10;
void Motor_RUN(int Choose_Motor, int direction, int _speed);

void forward();
void back();
void left();
void right();
void forwardleft();
void forwardright();
void backright();
void backleft();
void Stop();
// Motor 1

int command = 1;
float DEG_joystick;
int Speed_MT = 250;

char servo_compare = 'B';
char servo_compare_s = 'A';
void setup() {

  Serial.begin(115200);

  pinMode(motor1_in1, OUTPUT);
  pinMode(motor1_in2, OUTPUT);
  pinMode(motor2_in1, OUTPUT);
  pinMode(motor2_in2, OUTPUT);
  pinMode(motor3_in1, OUTPUT);
  pinMode(motor3_in2, OUTPUT);
  pinMode(motor4_in1, OUTPUT);
  pinMode(motor4_in2, OUTPUT);

  delay(100);
}



void loop() {
  
  Speed_MT = 255;
  forward();
  delay(10000);
  // //
  // Stop();
  // delay(500);
  // //
  // Speed_MT = 100;
  // forward();
  // delay(2000);
  // //
  // Stop();
  // delay(500);
  // //
  // Speed_MT = 200;
  // forward();
  // delay(2000);
  // //
  // Stop();
  // delay(500);
  // //
  // Speed_MT = 255;
  // forward();
  // delay(2000);
  //  //
  // Stop();
  // delay(500);
  //
  // backright();
  // delay(2000);
  // left();
  // delay(2000);


  // Serial.println(command);
  // analogWrite(pwm_1, Speed_MT);
  // analogWrite(pwm_2, Speed_MT);
}

void Motor_RUN(int Choose_Motor, int direction, int _speed) {
  if (Choose_Motor >= 0 && Choose_Motor <= 4) {

    if (Choose_Motor == Motor_1) {
      if (direction == Clockwise) {
        analogWrite(motor1_in1, _speed);
        analogWrite(motor1_in2, 0);
      } else if (direction == Counter_Clockwise) {
        analogWrite(motor1_in1, 0);
        analogWrite(motor1_in2, _speed);
      } else if (direction == Stop_Motor) {
        analogWrite(motor1_in1, 0);
        analogWrite(motor1_in2, 0);
      }
    }

    else if (Choose_Motor == Motor_2) {
      if (direction == Clockwise) {
        analogWrite(motor2_in1, _speed);
        analogWrite(motor2_in2, 0);
      } else if (direction == Counter_Clockwise) {
        analogWrite(motor2_in1, 0);
        analogWrite(motor2_in2, _speed);
      } else if (direction == Stop_Motor) {
        analogWrite(motor2_in1, 0);
        analogWrite(motor2_in2, 0);
      }
    }

    else if (Choose_Motor == Motor_3) {
      if (direction == Clockwise) {
        analogWrite(motor3_in1, _speed);
        analogWrite(motor3_in2, 0);
      } else if (direction == Counter_Clockwise) {
        analogWrite(motor3_in1, 0);
        analogWrite(motor3_in2, _speed);
      } else if (direction == Stop_Motor) {
        analogWrite(motor3_in1, 0);
        analogWrite(motor3_in2, 0);
      }
    }

    else if (Choose_Motor == Motor_4) {
      if (direction == Clockwise) {
        analogWrite(motor4_in1, _speed);
        analogWrite(motor4_in2, 0);
      } else if (direction == Counter_Clockwise) {
        analogWrite(motor4_in1, 0);
        analogWrite(motor4_in2, _speed);
      } else if (direction == Stop_Motor) {
        analogWrite(motor4_in1, 0);
        analogWrite(motor4_in2, 0);
      }
    }
  }
}
void forward() {
  Motor_RUN(Motor_1, Clockwise, Speed_MT);
  Motor_RUN(Motor_2, Clockwise, Speed_MT);
  Motor_RUN(Motor_3, Clockwise, Speed_MT);
  Motor_RUN(Motor_4, Clockwise, Speed_MT);
}

void back() {
  Motor_RUN(Motor_1, Counter_Clockwise, Speed_MT);
  Motor_RUN(Motor_2, Counter_Clockwise, Speed_MT);
  Motor_RUN(Motor_3, Counter_Clockwise, Speed_MT);
  Motor_RUN(Motor_4, Counter_Clockwise, Speed_MT);
}

void left() {
  Motor_RUN(Motor_1, Clockwise, Speed_MT);
  Motor_RUN(Motor_2, Clockwise, Speed_MT);
  Motor_RUN(Motor_3, Counter_Clockwise, Speed_MT);
  Motor_RUN(Motor_4, Counter_Clockwise, Speed_MT);
}

void right() {
  Motor_RUN(Motor_1, Counter_Clockwise, Speed_MT);
  Motor_RUN(Motor_2, Counter_Clockwise, Speed_MT);
  Motor_RUN(Motor_3, Clockwise, Speed_MT);
  Motor_RUN(Motor_4, Clockwise, Speed_MT);
}
void forwardleft() {
  Motor_RUN(Motor_1, Clockwise, Speed_MT);
  Motor_RUN(Motor_2, Clockwise, Speed_MT);
  Motor_RUN(Motor_3, Clockwise, Speed_MT / ratio_map);
  Motor_RUN(Motor_4, Clockwise, Speed_MT / ratio_map);
}
void forwardright() {
  Motor_RUN(Motor_1, Clockwise, Speed_MT / ratio_map);
  Motor_RUN(Motor_2, Clockwise, Speed_MT / ratio_map);
  Motor_RUN(Motor_3, Clockwise, Speed_MT);
  Motor_RUN(Motor_4, Clockwise, Speed_MT);
}
void backright() {
  Motor_RUN(Motor_1, Counter_Clockwise, Speed_MT / ratio_map);
  Motor_RUN(Motor_2, Counter_Clockwise, Speed_MT / ratio_map);
  Motor_RUN(Motor_3, Counter_Clockwise, Speed_MT);
  Motor_RUN(Motor_4, Counter_Clockwise, Speed_MT);
}
void backleft() {
  Motor_RUN(Motor_1, Counter_Clockwise, Speed_MT);
  Motor_RUN(Motor_2, Counter_Clockwise, Speed_MT);
  Motor_RUN(Motor_3, Counter_Clockwise, Speed_MT / ratio_map);
  Motor_RUN(Motor_4, Counter_Clockwise, Speed_MT / ratio_map);
}

void Stop() {
  Motor_RUN(Motor_1, Stop_Motor, 0);
  Motor_RUN(Motor_2, Stop_Motor, 0);
  Motor_RUN(Motor_3, Stop_Motor, 0);
  Motor_RUN(Motor_4, Stop_Motor, 0);
}
