#include <avr/io.h>
#include "util/delay.h"

#define DELAY_CLK 25

void clocke() {
  PORTB |= 2;
  _delay_ms(DELAY_CLK);
  PORTB &= ~2;
  _delay_ms(DELAY_CLK);
}

int cd4511[] = {
  0b11111100,
  0b01100000,
  0b11011010,
  0b11110010,
  0b01100110,
  0b10110110,
  0b10111110,
  0b11100000,
  0b11111110,
  0b11100110,
};

void setbit(short p) {
  PORTB |= (1 << p);
}

void clearbit(short p) {
  PORTB &= ~(1 << p);
}

void resetbits() {
  PORTB &= ~4;
  PORTB |= 4;
}

int main() {
  DDRB |= (1 << 0);        // PB0 - DATA 1
  DDRB |= (1 << 1);        // PB1 - CLOCK
  DDRB |= (1 << 2);        // PB2 - RESET
  DDRB |= (1 << 3);        // PB3 - DATA 2

  resetbits();

  while (1) {
    for (int i = 0 ; i < 10; i++) {
      for (int k = 0; k < 10; k++) {
        for (int j = 0; j < 8; j++) {
          (cd4511[k] & (1 << j)) ? (setbit(0)) : (clearbit(0));
          clocke();
        }
        for (int j = 0; j < 8; j++) {
          (cd4511[i] & (1 << j)) ? (setbit(0)) : (clearbit(0));
          clocke();
        }
        _delay_ms(200);
        //resetbits();
      }
    }
  }
}
