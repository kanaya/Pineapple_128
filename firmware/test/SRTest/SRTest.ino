const int A         =  200;  // ONタイム  [msec]
const int B         =  200;  // OFFタイム [msec]
const int C         =  20;   // 1chずつずらすタイミング [msec] （0の場合は全チャンネル一斉にオンオフする）

const int N         =  8;    // 電磁弁の数

const int PIN_CLR   =  2;
const int PIN_SCLK  =  3;
const int PIN_RCLK  =  4;
const int PIN_SOUT1 =  5;

void full_reset() {
  digitalWrite(PIN_CLR, LOW);
  delay(10);
  digitalWrite(PIN_CLR, HIGH);
}

void setup() {
  pinMode(PIN_SOUT1, OUTPUT);
  pinMode(PIN_RCLK,  OUTPUT);
  pinMode(PIN_SCLK,  OUTPUT);
  pinMode(PIN_CLR,   OUTPUT);

  digitalWrite(PIN_CLR, HIGH);
}

void loop() { 
  if (C == 0) {
    // 全チャンネル同時にオンオフする
    // ON
    digitalWrite(PIN_RCLK, LOW);
    shiftOut(PIN_SOUT1, PIN_SCLK, LSBFIRST, B11111111);
    digitalWrite(PIN_RCLK, HIGH);
    delay(A);
    // OFF
    digitalWrite(PIN_RCLK, LOW);
    shiftOut(PIN_SOUT1, PIN_SCLK, LSBFIRST, B00000000);
    digitalWrite(PIN_RCLK, HIGH);
    delay(B);
  }
  else {
    // 1chずつずらしてオンオフする
    if (C * N < A) {
      // C * N << A の場合
      // ON
      int bitPattern = B00000001;
      for (int i = 0; i < N; ++i) {
        digitalWrite(PIN_RCLK, LOW);
        shiftOut(PIN_SOUT1, PIN_SCLK, LSBFIRST, bitPattern);
        digitalWrite(PIN_RCLK, HIGH);
        bitPattern <<= 1;
        bitPattern |= 1;
        delay(C);
      }
      delay(A);
      // OFF
      bitPattern = B11111110;
      for (int i = 0; i < N; ++i) {
        digitalWrite(PIN_RCLK, LOW);
        shiftOut(PIN_SOUT1, PIN_SCLK, LSBFIRST, bitPattern);
        digitalWrite(PIN_RCLK, HIGH);
        bitPattern <<= 1;
        delay(C);
      }
      delay(B);
    }
    else {
      // C * N >> A + B の場合
      int bitPattern = B00000001;
      for (int i = 0; i < N; ++i) {
        // ON
        digitalWrite(PIN_RCLK, LOW);
        shiftOut(PIN_SOUT1, PIN_SCLK, LSBFIRST, bitPattern);
        digitalWrite(PIN_RCLK, HIGH);
        bitPattern <<= 1;
        delay(A);
        // OFF
        digitalWrite(PIN_RCLK, LOW);
        shiftOut(PIN_SOUT1, PIN_SCLK, LSBFIRST, B00000000);
        digitalWrite(PIN_RCLK, HIGH);
        delay(B);
      }
      delay(C);
    }
  }
}
