/*!
 * @file
 * @brief
 */

#include "stm8s.h"
#include <stddef.h>
#include <stdbool.h>
#include "button.h"
#include "tiny_event.h"

static tiny_event_t press_event;
static bool handled_press;

enum {
  pin_3 = (1 << 3)
};

void button_init(void) {
  GPIOC->DDR &= ~pin_3;
  tiny_event_init(&press_event);
}

// i_tiny_event_t* button_press_event(void) {
//   return &press_event.interface;
// }

void button_run(void) {
  if(button_pressed()) {
    if(!handled_press) {
      handled_press = true;
      tiny_event_publish(&press_event, NULL);
    }
  }
  else {
    handled_press = false;
  }
}

bool button_pressed(void) {
  return (GPIOC->IDR & pin_3) == 0;
}