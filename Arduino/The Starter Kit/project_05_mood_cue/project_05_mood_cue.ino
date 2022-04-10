#include <Servo.h>

const int POT_PIN = A0;

Servo servo;

void setup() {
  servo.attach(9);
  Serial.begin(9600);
}

void loop() {
  auto potValue = analogRead(POT_PIN);
  auto angle = map(potValue, 0, 1023, 0, 179);
  Serial.print("The value of potentiometer: ");
  Serial.print(potValue);
  Serial.print(", set angle to ");
  Serial.println(angle);
  servo.write(angle);
  delay(10);
}
