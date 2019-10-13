/*!
 * @file
 * @brief
 */

#include "stm8s.h"
#include <stddef.h>
#include <stdbool.h>
#include "led.h"

enum {
  pin_5 = (1 << 5)
};

void led_init(void) {
  // Configure push pull output
  GPIOC->CR1 |= pin_5;
  GPIOC->DDR |= pin_5;
}

void led_set_state(bool state) {
  if(state) {
    GPIOC->ODR |= pin_5;
  }
  else {
    GPIOC->ODR &= ~pin_5;
  }
}
