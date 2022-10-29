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

const uint8_t BUTTON_LED1_ON[]  = {0xAA, 0x04, 0x02, 0x00, 0x01, 0x00, 0xB1};
const uint8_t BUTTON_LED1_OFF[] = {0xAA, 0x04, 0x02, 0x00, 0x00, 0x00, 0xB0};
const uint8_t BUTTON_LED3_ON[]  = {0xAA, 0x04, 0x02, 0x01, 0x01, 0x00, 0xB2};
const uint8_t BUTTON_LED3_OFF[] = {0xAA, 0x04, 0x02, 0x01, 0x00, 0x00, 0xB1};

int button_led1_on = false;
int button_led3_on = false;

void setSystemClk32MHZ() {
  CLKCONCMD &= ~0x40;
  while(CLKCONSTA & 0x40);
  CLKCONCMD &= ~0x47;
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

void uart1_send(const uint8_t *data, uint8_t len) {
  for (uint8_t i = 0; i < len; ++i) {
    U1DBUF = data[i];
    // DEBUG_LOG("UART1.TX: 0x%2x\n", data[i]);
    while (UTX1IF == 0);
    UTX1IF = 0;
  }
}

uint8_t received[7] = {0};
uint8_t index = 0;
#pragma vector = URX1_VECTOR 
__interrupt void URX1_ISR(void) {
  // Clear interrupt flag
  URX1IF = 0;
  if (U1DBUF == 0xAA) {
    index = 0;
  }
  if (index >= sizeof(received)) return;
  received[index++] = U1DBUF;
  if (index == sizeof(received) - 1 && received[4] == 0x01) {
    switch(received[3]) {
      case 0x00:
        button_led1_on = !button_led1_on;
        uart1_send(button_led1_on ? BUTTON_LED1_ON : BUTTON_LED1_OFF, sizeof(BUTTON_LED1_ON));
        break;
      case 0x1:
        button_led3_on = !button_led3_on;
        uart1_send(button_led3_on ? BUTTON_LED3_ON : BUTTON_LED3_OFF, sizeof(BUTTON_LED3_ON));
        break;
      default:
        DEBUG_LOG("Unknown data:");
        for (uint8_t i = 0; i < sizeof(received); ++i) {
          DEBUG_LOG("%0x", received[i]);
        }
        DEBUG_LOG("\n");
        break;
    }
  }
}

void init_uart1() {
  // Use P1_4 && P1_5 as TX ports
  PERCFG = 0x01;
  // P1_4, P1_5 as peripheral function
  P0SEL = 0x3c;
  P1SEL |= 3 << 4;
  // Port 0 periphera 1st priority: USART 0
  P2DIR &= ~0xc0;

  // USART mode select: UART mode
  U1CSR |= 1 << 7;

  // Set baud to 9600
  U1GCR  |= 8;  
  U1BAUD |= 59;

  // Clear tx-interrupt flag
  UTX1IF = 0;
  // Clear rx-interrupt flag
  URX1IF = 0;
  // Enable port 1 interrupts
  URX1IE = 1;  
  // Enable interrupt
  EA = 1;

  // Enable UART-Rx
  U1CSR |= 1 << 6;
}

void init_button_leds() {
  uart1_send(BUTTON_LED1_OFF, sizeof(BUTTON_LED1_OFF));
  uart1_send(BUTTON_LED3_OFF, sizeof(BUTTON_LED3_OFF));
}

int main()
{
  init_led();
  init_buzzer();
  setSystemClk32MHZ();
  init_uart1();
  init_button_leds();
  while(true){
  }
  return 0;
}
