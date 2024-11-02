// Các chân điều khiển cuộn dây của động cơ bước
int motorCoilPin1 = 7; // Cuộn 1
int motorCoilPin2 = 6; // Cuộn 2
int motorCoilPin3 = 5; // Cuộn 3
int motorCoilPin4 = 4; // Cuộn 4

unsigned long lastStepTime = 0; // Thời gian của bước cuối cùng
int currentStepIndex = 0; // Chỉ số bước hiện tại
void setup_step() {
  // Khai báo các chân cuộn động cơ là OUTPUT
  pinMode(motorCoilPin1, OUTPUT);
  pinMode(motorCoilPin2, OUTPUT);
  pinMode(motorCoilPin3, OUTPUT);
  pinMode(motorCoilPin4, OUTPUT);
}


// Hàm stepMotorClockwise: Điều khiển quay theo chiều kim đồng hồ
void stepMotorClockwise() {
  switch (currentStepIndex) {
    case 0:
      digitalWrite(motorCoilPin1, HIGH);
      digitalWrite(motorCoilPin2, LOW);
      digitalWrite(motorCoilPin3, LOW);
      digitalWrite(motorCoilPin4, LOW);
      break;
    case 1:
      digitalWrite(motorCoilPin1, LOW);
      digitalWrite(motorCoilPin2, HIGH);
      digitalWrite(motorCoilPin3, LOW);
      digitalWrite(motorCoilPin4, LOW);
      break;
    case 2:
      digitalWrite(motorCoilPin1, LOW);
      digitalWrite(motorCoilPin2, LOW);
      digitalWrite(motorCoilPin3, HIGH);
      digitalWrite(motorCoilPin4, LOW);
      break;
    case 3:
      digitalWrite(motorCoilPin1, LOW);
      digitalWrite(motorCoilPin2, LOW);
      digitalWrite(motorCoilPin3, LOW);
      digitalWrite(motorCoilPin4, HIGH);
      break;
  }

  currentStepIndex++;
  if (currentStepIndex > 3) {
    currentStepIndex = 0; // Quay lại bước đầu tiên sau bước thứ 4
  }
}

// Hàm stepMotorCounterClockwise: Điều khiển quay ngược chiều kim đồng hồ
void stepMotorCounterClockwise() {
  switch (currentStepIndex) {
    case 0:
      digitalWrite(motorCoilPin1, LOW);
      digitalWrite(motorCoilPin2, LOW);
      digitalWrite(motorCoilPin3, LOW);
      digitalWrite(motorCoilPin4, HIGH);
      break;
    case 1:
      digitalWrite(motorCoilPin1, LOW);
      digitalWrite(motorCoilPin2, LOW);
      digitalWrite(motorCoilPin3, HIGH);
      digitalWrite(motorCoilPin4, LOW);
      break;
    case 2:
      digitalWrite(motorCoilPin1, LOW);
      digitalWrite(motorCoilPin2, HIGH);
      digitalWrite(motorCoilPin3, LOW);
      digitalWrite(motorCoilPin4, LOW);
      break;
    case 3:
      digitalWrite(motorCoilPin1, HIGH);
      digitalWrite(motorCoilPin2, LOW);
      digitalWrite(motorCoilPin3, LOW);
      digitalWrite(motorCoilPin4, LOW);
      break;
  }

  currentStepIndex--;
  if (currentStepIndex < 0) {
    currentStepIndex = 3; // Quay lại bước cuối cùng sau bước đầu tiên
  }
}
// Hàm motorRun: Cho phép điều khiển động cơ bước với các tham số tốc độ và hướng
void motorRun(int stepDelay, bool isClockwise) {
  unsigned long currentMillis = millis(); // Lấy thời gian hiện tại
  
  // Kiểm tra xem đã đủ thời gian để thực hiện bước tiếp theo chưa
  if (currentMillis - lastStepTime >= stepDelay) {
    lastStepTime = currentMillis; // Cập nhật thời gian của bước cuối cùng
    
    // Gọi hàm thực hiện một bước dựa trên hướng đã chọn
    if (isClockwise) {
      stepMotorClockwise();  // Quay theo chiều kim đồng hồ
    } else {
      stepMotorCounterClockwise(); // Quay ngược chiều kim đồng hồ
    }
  }
}


// void loop() {
//   // Gọi hàm motorRun với tốc độ và hướng mong muốn
//   motorRun(5, true); // Tham số đầu là tốc độ (mili giây), tham số thứ hai là hướng (true = theo chiều kim đồng hồ, false = ngược chiều kim đồng hồ)
// }
