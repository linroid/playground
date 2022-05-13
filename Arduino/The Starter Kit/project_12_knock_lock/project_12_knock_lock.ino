#include <Servo.h>

Servo locker;
bool locked = false;
int counter = 0;

void lock() {
  locker.write(0);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  locked = true;
}

void unlock() {
  locker.write(90);
  
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  locked = false;
  counter = 0;
}

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT); // green led
  pinMode(4, OUTPUT); // yellow led
  pinMode(5, OUTPUT); // red led
  locker.attach(8);
  unlock();
}

void loop() {
  if (!locked) {
    if (digitalRead(2) == HIGH) {
      lock();
    }
    return;
  }
  int sound = analogRead(A0);
  Serial.println(sound);
  if (sound > 10) {
    counter++;
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
  }
  if (counter >= 2) {
    unlock();
  }
}
