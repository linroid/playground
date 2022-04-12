const int kPiezoPin = 8;

int notes[] = {262, 294, 330, 349};

void setup() {
  Serial.begin(9600);
  pinMode(kPiezoPin, OUTPUT);
  digitalWrite(kPiezoPin, HIGH);
}

void loop() {
  int value = analogRead(A0);
  Serial.print("Value: ");
  Serial.println(value);
  if (value >= 1020) {
    tone(kPiezoPin, notes[0]);
  } else if (value >= 990 && value < 1010) {
    tone(kPiezoPin, notes[1]);
  } else if (value >= 505 && value < 515) {
    tone(kPiezoPin, notes[2]);
  } else if (value > 5 && value < 10) {
    tone(kPiezoPin, notes[3]);
  } else {
    noTone(8);
  }
}
