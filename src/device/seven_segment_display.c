/*!
 * @file
 * @brief
 */

#include "stm8s_gpio.h"
#include "seven_segment_display.h"

#define init_output(_port, _pin)   \
  GPIO##_port->DDR |= (1 << _pin); \
  GPIO##_port->CR1 |= (1 << _pin)

#define write_output(_port, _pin, _state) \
  if(_state)                              \
    GPIO##_port->ODR |= (1 << _pin);      \
  else                                    \
    GPIO##_port->ODR &= ~(1 << _pin)

static void delay(void) {
  int i;
  for(i = 1; i <= 10000; i++) {
  }
}

void seven_segment_display_init(void) {
  // Turns everything on
  init_output(D, 5); // A
  init_output(A, 2); // B
  init_output(C, 7); // C
  init_output(D, 3); // D
  init_output(D, 1); // E
  init_output(A, 1); // F
  init_output(C, 6); // G
  init_output(D, 2); // P

  init_output(D, 4); // 1
  init_output(B, 5); // 2
  init_output(B, 4); // 3

  // 1 is on, 0 is off
  write_output(D, 5, 1); // A
  write_output(A, 2, 1); // B
  write_output(C, 7, 1); // C
  write_output(D, 3, 1); // D
  write_output(D, 1, 1); // E
  write_output(A, 1, 1); // F
  write_output(C, 6, 1); // G
  write_output(D, 2, 1); // P

  // 1 is off, 0 is on
  write_output(D, 4, 0); // 1
  write_output(B, 5, 0); // 2
  write_output(B, 4, 0); // 3
}

void seven_segment_display_69(void) {
  while(1) {
    // 1 is on, 0 is off
    write_output(D, 5, 1); // A
    write_output(A, 2, 0); // B
    write_output(C, 7, 1); // C
    write_output(D, 3, 1); // D
    write_output(D, 1, 1); // E
    write_output(A, 1, 1); // F
    write_output(C, 6, 1); // G
    write_output(D, 2, 0); // P

    // 1 is off, 0 is on
    write_output(D, 4, 1); // 1
    write_output(B, 5, 0); // 2
    write_output(B, 4, 1); // 3

    delay();

    // 1 is on, 0 is off
    write_output(D, 5, 1); // A
    write_output(A, 2, 1); // B
    write_output(C, 7, 1); // C
    write_output(D, 3, 0); // D
    write_output(D, 1, 0); // E
    write_output(A, 1, 1); // F
    write_output(C, 6, 1); // G
    write_output(D, 2, 0); // P

    // 1 is off, 0 is on
    write_output(D, 4, 1); // 1
    write_output(B, 5, 1); // 2
    write_output(B, 4, 0); // 3

    delay();
  }
}
