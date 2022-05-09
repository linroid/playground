const int kMotorPin = 8;
const int kSwitchPin = 2;

void setup() {
  pinMode(kMotorPin, OUTPUT);
  pinMode(kSwitchPin, INPUT);
  Serial.begin(9600);
}

int lastSwitchState = LOW;
int motorState = LOW;

void loop() {
   int switchState = digitalRead(kSwitchPin);
   Serial.println(switchState);
   if (lastSwitchState != switchState && lastSwitchState == LOW) {
     if (motorState == LOW) {
       digitalWrite(kMotorPin, HIGH);
       motorState = HIGH;
     } else {
       digitalWrite(kMotorPin, LOW);
       motorState = LOW;
     }
   }
   lastSwitchState = switchState;
}
