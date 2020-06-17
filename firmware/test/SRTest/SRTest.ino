const int PIN_CLR   =  2;
const int PIN_SCLK  =  3;
const int PIN_RCLK  =  4;
const int PIN_SOUT1 =  5;

void setup() {
  pinMode(PIN_SOUT1, OUTPUT);
  pinMode(PIN_RCLK,  OUTPUT);
  pinMode(PIN_SCLK,  OUTPUT);
  pinMode(PIN_CLR,   OUTPUT);

  digitalWrite(PIN_CLR, HIGH);
}

void loop() { 
  for (int i = 0; i < 8; ++i) {
    digitalWrite(PIN_RCLK, LOW);
    shiftOut(PIN_SOUT1, PIN_SCLK, LSBFIRST, 1 << i);
    digitalWrite(PIN_RCLK, HIGH);
    delay(100);
  }
}
