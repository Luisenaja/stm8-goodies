/*!
 * @file
 * @brief
 */

#include "stm8s.h"
#include <stddef.h>
#include <stdbool.h>
#include "led.h"

enum {
  pin_3 = (1 << 3)
};

void led_init(void) {
  // Configure push pull output
  GPIOA->CR1 |= pin_3;
  GPIOA->DDR |= pin_3;
}

void led_set_state(bool state) {
  if(state) {
    GPIOA->ODR |= pin_3;
  }
  else {
    GPIOA->ODR &= ~pin_3;
  }
}
