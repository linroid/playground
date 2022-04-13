const int kMotorPin = 9;
const int kSwitchPin = 8;

void setup() {
  pinMode(kMotorPin, OUTPUT);
  pinMode(kSwitchPin, INPUT);
  Serial.begin(9600);
}

void loop() {
   int switchState = digitalRead(kSwitchPin);
   Serial.println(switchState);
   if (switchState == HIGH) {
     digitalWrite(kMotorPin, HIGH);
   } else {
     digitalWrite(kSwitchPin, LOW);
   }
}
