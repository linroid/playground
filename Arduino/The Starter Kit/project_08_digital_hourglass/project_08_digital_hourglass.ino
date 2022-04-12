const int kTiltPin = 8;
const int kPiezoPin = 9;

const int kInterval = 2000;
const int kLedCount = 6;

int tiltState = 0;
int ledOnCount = 0;
unsigned long lastTs = 0;

void setup() {
  Serial.begin(9600);
  pinMode(kTiltPin, INPUT);
  pinMode(kPiezoPin, OUTPUT);
  for (int i = 0; i < kLedCount; ++i) {
    pinMode(i + 2, OUTPUT);
  }
  tiltState = digitalRead(kTiltPin);
  lastTs = millis();
}

void loop() {
  int value = digitalRead(kTiltPin);
  if (value != tiltState) {
    tiltState = value;
    lastTs = millis();
  } else if (millis() - lastTs > kInterval) {
    lastTs = millis();
    if (value) {
      ledOnCount = min(kLedCount, ledOnCount + 1);
    } else {
      ledOnCount = max(0, ledOnCount - 1);
    }
    refreshLeds();
  }
  
  Serial.print("Tilt value: ");
  Serial.print(value);  
  Serial.print(", led on count: ");
  Serial.println(ledOnCount);
}

void refreshLeds() {
  for (int i = 0; i < kLedCount; ++i) {
    digitalWrite(i + 2, ledOnCount > i ? HIGH : LOW);
  }
  if (ledOnCount == kLedCount) {
    tone(kPiezoPin, 50);
  } else {
    tone(kPiezoPin, 200 * ledOnCount + 100);
    delay(100);
    noTone(kPiezoPin);
  }
}
