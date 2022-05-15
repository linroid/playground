const int kOptocouplerPin = 8;

void setup() {
  pinMode(kOptocouplerPin, OUTPUT);
}

void loop() {
  digitalWrite(kOptocouplerPin, HIGH);
  delay(1000);
  digitalWrite(kOptocouplerPin, LOW);
  delay(1000);
}
