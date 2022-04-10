const int PIN_PIEZO = 3;
const int PIN_LED = 8;
const int LIGHT_SENSOR = A0;

int lightHigh = 0;
int lightLow = 1023;

void calibrate() {
  pinMode(PIN_LED, OUTPUT);
  Serial.println("Start calibrating");
  digitalWrite(PIN_LED, HIGH);
  while (millis() < 5000) {
    int value = analogRead(LIGHT_SENSOR);
    lightHigh = max(value, lightHigh);
    lightLow = min(value, lightLow);
  }
  digitalWrite(PIN_LED, LOW);
  Serial.println("Calibrating finished!");
  Serial.print("Light range: ");
  Serial.print(lightLow);
  Serial.print(" - ");
  Serial.println(lightHigh);
}

void setup() {
   pinMode(PIN_PIEZO, OUTPUT);
   Serial.begin(9600);
   calibrate();
}

void loop() {
  int light = analogRead(A0);
  int sound = map(light, lightLow, lightHigh, 50, 4000);
  Serial.print("light: ");
  Serial.print(light);
  Serial.print(", sound: ");
  Serial.println(sound);
  tone(PIN_PIEZO, sound);
}
