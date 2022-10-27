#include<stdio.h>
#include <stdint.h>
#include <ioCC2530.h>

#define LED P0_7
#define LED_ON 1
#define LED_OFF 0

void delay(uint16_t milliseconds) {
  uint16_t i,j;
  
  for (i = 0; i < milliseconds; i++) {
    for (j = 0; j < 535; j++);
  }
}

void init_led() {
  P0SEL &= ~(1 << 7);
  P0DIR |= 1 << 7;
  LED = LED_OFF;
}

int main()
{
  init_led();
  while (true) {
    delay(500);
    LED = LED_OFF;
    delay(500);
    LED = LED_ON;
  }
  return 0;
}
