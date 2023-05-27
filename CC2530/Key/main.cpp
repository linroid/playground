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
  // General-Purpose I/O
  P1SEL &= ~(1 << 2);
  // Input direction
  P1DIR &= ~(1 << 2);
  // Pull Up/Down Mode
  P1INP &= ~(1 << 2);
  // Set Port 0 pull up mode
  P2INP &= ~(1 << 6);
}

void init_interrupt() {
  
}

int main()
{
  init_led();
  init_buzzer();
  init_interrupt();
  init_key();
  while (true) {
    if (KEY != KEY_DOWN) continue;
    // Delay 10ms for debouncing
    delay(10);
    if (KEY != KEY_DOWN) continue;
    DEBUG_LOG("Key Down\n");
    while(KEY == KEY_DOWN);
    DEBUG_LOG("Key Up\n");
    LED = LED == LED_ON ? LED_OFF : LED_ON; 
  }
  return 0;
}
