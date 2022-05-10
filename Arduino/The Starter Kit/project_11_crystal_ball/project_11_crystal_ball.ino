#include<LiquidCrystal.h>

const int kSwitchPin = 2;
const char* kAnswers[] = {"Yes", "Most likely", "Certainly", "Outlook good", "Unsure", "Ask again", "Doubtful", "No"};

LiquidCrystal lcd(3, 4, 8, 9, 10, 11);
int preSwitchState = LOW;
int switchState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(kSwitchPin, INPUT);
  lcd.begin(16, 2);
  lcd.print("Hello LCD :)");
  delay(1000);

  lcd.clear();
  lcd.print("Ask the");
  lcd.setCursor(0, 1);
  lcd.print("Crystal Ball!");
}

void loop() {
  switchState = digitalRead(kSwitchPin);
  
  if (switchState == preSwitchState) return;
  
  if (preSwitchState == LOW) {
    int reply = random(8);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("The ball says:");
    lcd.setCursor(0, 1);
    lcd.print(kAnswers[reply]);
  }
  preSwitchState = switchState;
}
