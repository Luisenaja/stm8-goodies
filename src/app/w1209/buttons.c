/*!
 * @file
 * @brief
 */

#include "stm8s.h"
#include <stddef.h>
#include <stdbool.h>
#include "buttons.h"
#include "tiny_event.h"
#include "tiny_timer.h"
#include "tiny_utils.h"

typedef struct {
  tiny_event_t press_event;
  uint8_t pin_mask;
  bool handled_press;
} button_t;

static button_t buttons[3];
static tiny_timer_t timer;

enum {
  pin_3 = (1 << 3),
  pin_4 = (1 << 4),
  pin_5 = (1 << 5)
};

static bool button_pressed(button_t* button) {
  return (GPIOC->IDR & button->pin_mask) == 0;
}

static void buttons_run(tiny_timer_group_t* timer_group, void* context) {
  (void)context;

  for(uint8_t i = 0; i < element_count(buttons); i++) {
    bool pressed = button_pressed(&buttons[i]);

    if(pressed) {
      if(!buttons[i].handled_press) {
        buttons[i].handled_press = true;
        tiny_event_publish(&buttons[i].press_event, NULL);
      }
    }
    else {
      buttons[i].handled_press = false;
    }
  }

  tiny_timer_start(timer_group, &timer, 10, buttons_run, NULL);
}

void buttons_init(tiny_timer_group_t* timer_group) {
  buttons[0].pin_mask = pin_3;
  buttons[1].pin_mask = pin_4;
  buttons[2].pin_mask = pin_5;

  for(uint8_t i = 0; i < element_count(buttons); i++) {
    GPIOC->DDR &= ~buttons[i].pin_mask;
    GPIOC->CR1 |= buttons[i].pin_mask;
    tiny_event_init(&buttons[i].press_event);
  }

  buttons_run(timer_group, NULL);
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
