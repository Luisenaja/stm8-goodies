/*!
 * @file
 * @brief
 */

#include <stm8s.h>
#include <stddef.h>
#include <stdbool.h>
#include "led_toggler.h"
#include "led.h"
#include "tiny_utils.h"

static void button_callback(void* context, const void* args) {
  reinterpret(self, context, led_toggler_t*);
  (void)args;

  // toggle the led
  self->state = !self->state;
  led_set_state(self->state);
}

void led_toggler_init(led_toggler_t* self, i_tiny_event_t* button_press_event) {
  // initialize subscription
  tiny_event_subscription_init(&self->subscription, self, button_callback);
  // subscribe to the press event
  tiny_event_subscribe(button_press_event, &self->subscription);
}