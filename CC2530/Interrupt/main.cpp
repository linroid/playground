#include<stdio.h>
#include <stdint.h>
#include <ioCC2530.h>

#define DEBUG

#ifdef DEBUG
#define DEBUG_LOG(...) printf(__VA_ARGS__)
#else
#define DEBUG_LOG(...) 
#endif

#define LED P0_7
#define LED_ON 1
#define LED_OFF 0

#define KEY P1_2
#define KEY_DOWN 0
#define KEY_UP 1

void delay(uint16_t milliseconds) {
  uint16_t i,j;
  
  for (i = 0; i < milliseconds; i++) {
    for (j = 0; j < 535; j++);
  }
}

void init_buzzer() {
  P0SEL &= ~(1 << 6);
  P0DIR |= 1 << 6;
  P0_6 = 0;
}

void init_led() {
  P0SEL &= ~(1 << 7);
  P0DIR |= 1 << 7;
  LED = LED_OFF;
}

void init_key() {
  // Set P1ICONL 1
  PICTL |= 1 << 1;
  // Clear interrupt on port 1
  P1IFG = 0;
  // Allow interrupt on P1_2
  P1IEN |= 1 << 2;
  // Clera register
  P1IF = 0;
  // Allow all interrupt
  EA = 1;
  // Allow interrupt on port 1
  IEN2 |= 1 << 4;
}

#pragma vector = P1INT_VECTOR
__interrupt void handle_key() {
  delay(10);
  if (KEY == KEY_DOWN) {
    DEBUG_LOG("Key Down\n");
    LED = LED == LED_ON ? LED_OFF : LED_ON; 
  }
  P1IFG = 0;
  P1IF = 0;
}

int main()
{
  init_led();
  init_buzzer();
  init_key();
  while (true) {
    delay(1000);
  }
  return 0;
}
