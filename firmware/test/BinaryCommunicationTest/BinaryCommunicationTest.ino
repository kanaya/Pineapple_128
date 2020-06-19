const int N = 8;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  while (Serial.available() > 0) {
    byte downstream[N];
    int n;
    n = Serial.readBytes(downstream, N);
    if (n > 0) {
      for (int i = 0; i < N; ++i) {
        if ((downstream[i] & 0x01) == 1) {
          digitalWrite(LED_BUILTIN, HIGH);
        }
        else {
          digitalWrite(LED_BUILTIN, LOW);
        }
        delay(100);
      }
    }
  }
}

// usage: echo {BINARY_FILE} > /dev/cu.usbmodem####
