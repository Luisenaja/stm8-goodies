/*!
 * @file
 * @brief
 */

#include "stm8s.h"
#include <stddef.h>
#include <stdbool.h>
#include "buttons.h"
#include "tiny_event.h"

typedef struct {
  tiny_event_t press_event;
  uint8_t pin_mask;
  bool handled_press;
} button_t;

// static tiny_event_t press_event_3;
// static tiny_event_t press_event_4;
// static tiny_event_t press_event_5;
// static bool handled_press;

static button_t buttons[3];

enum {
  pin_3 = (1 << 3),
  pin_4 = (1 << 4),
  pin_5 = (1 << 5)
};

void buttons_init(void) {
  buttons[0].pin_mask = pin_3;
  buttons[1].pin_mask = pin_4;
  buttons[2].pin_mask = pin_5;

  for(uint8_t i = 0; i < element_count(buttons); i++) {
    GPIOC->DDR &= ~buttons[i].pin_mask;
    tiny_event_init(&buttons[i].press_event);
  }
}

i_tiny_event_t* button_press_event(void) {
  return &buttons[0].press_event.interface;
}

i_tiny_event_t* on_button_press_event(void) {
  return &buttons[1].press_event.interface;
}

i_tiny_event_t* off_button_press_event(void) {
  return &buttons[2].press_event.interface;
}

void buttons_run(void) {
  // if(button_3_pressed()) {
  //   if(!handled_press) {
  //     handled_press = true;
  //     tiny_event_publish(&press_event_3, NULL);
  //   }
  // }
  // else if(button_4_pressed()) {
  //   if(!handled_press) {
  //     handled_press = true;
  //     tiny_event_publish(&press_event_4, NULL);
  //   }
  // }
  // else if(button_5_pressed()) {
  //   if(!handled_press) {
  //     handled_press = true;
  //     tiny_event_publish(&press_event_5, NULL);
  //   }
  // }
  // else {
  //   handled_press = false;
  // }

  for(uint8_t i = 0; i < element_count(buttons); i++) {
    bool pressed = (GPIOC->IDR & buttons[i].pin_mask) == 0;

    if(pressed) {
      if(!buttons[i].handled_press) {
        buttons[i].handled_press = true;
        tiny_event_publish(&buttons[i].press_event, NULL);
      }
    }
    else {
      buttons[i].handled_press;
    }
  }
}

// bool button_3_pressed(void) {
//   return (GPIOC->IDR & pin_3) == 0;
// }

// bool button_4_pressed(void) {
//   return (GPIOC->IDR & pin_4) == 0;
// }

// bool button_5_pressed(void) {
//   return (GPIOC->IDR & pin_5) == 0;
// }