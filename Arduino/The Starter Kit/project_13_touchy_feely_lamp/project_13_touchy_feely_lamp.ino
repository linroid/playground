#include <CapacitiveSensor.h>

const int kLedPin = 8;
CapacitiveSensor sensor(3 /* send pin */, 2 /* receive pin */);

void setup() {
  pinMode(kLedPin, OUTPUT);
  digitalWrite(kLedPin, LOW);
  Serial.begin(9600);
}

void loop() {
  auto sensorValue = sensor.capacitiveSensor(30000000);
  Serial.println(sensorValue);
  if (sensorValue > 500) {
    digitalWrite(kLedPin, HIGH);
  } else {
    digitalWrite(kLedPin, LOW);
  }
}
