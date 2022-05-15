const int kEnableButtonPin = 3;
const int kDirectionButtonPin = 4;
const int kMotorPinEnabled = 2;
const int kMotorPin1 = 8;
const int kMotorPin2 = 9;

int enabled = false;
int pin1Anode = true;

bool lastEnableButtonState = LOW;
bool lastDirectionButtonState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(kEnableButtonPin, INPUT);
  pinMode(kDirectionButtonPin, INPUT);
  pinMode(kMotorPinEnabled, OUTPUT);
  pinMode(kMotorPin1, OUTPUT);
  pinMode(kMotorPin2, OUTPUT);

  digitalWrite(kMotorPinEnabled, LOW);
  digitalWrite(kMotorPin1, HIGH);
  digitalWrite(kMotorPin2, LOW);
}

void loop() {
  int enableButtonState = digitalRead(kEnableButtonPin);
  if (enableButtonState == HIGH && lastEnableButtonState == LOW) {
    Serial.println("Enable button clicked");
    enabled = !enabled;
    Serial.print("Enabled -> ");
    Serial.println(enabled);
    digitalWrite(kMotorPinEnabled, enabled ? HIGH: LOW);
  }
  lastEnableButtonState = enableButtonState;

  int directionButtonState = digitalRead(kDirectionButtonPin);
  if (directionButtonState == HIGH && lastDirectionButtonState == LOW) {
    Serial.println("Direction button clicked");
    pin1Anode = !pin1Anode;
    digitalWrite(kMotorPin1, pin1Anode ? HIGH : LOW);
    digitalWrite(kMotorPin2, pin1Anode ? LOW : HIGH);
    Serial.print("Pin1Anode -> ");
    Serial.println(pin1Anode);
  }
  lastDirectionButtonState = directionButtonState;
}
