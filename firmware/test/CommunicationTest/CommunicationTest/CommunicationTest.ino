const int N = 8;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  while (Serial.available() > 0) {
    int downstream[N];
    for (int i = 0; i < N; ++i) {
      downstream[i] = Serial.parseInt();
    }
    if (Serial.read() == '\n') {
      for (int i = 0; i < N; ++i) {
        if (downstream[i] > 0) {
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

// usage: echo '1 0 1 0 1 1 0 1' > /dev/cu.usbmodem####
