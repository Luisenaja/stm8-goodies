/*!
 * @file
 * @brief
 */

#include <stm8s.h>
#include <stddef.h>
#include <stdbool.h>
#include "thermistor_toggler.h"
#include "led.h"
#include "thermistor.h"
#include "tiny_utils.h"

static void thermistor_callback(void* context, const void* args) {
  reinterpret(self, context, thermistor_toggler_t*);
  (void)args;

  // toggle the led
  self->state = !self->state;
  led_set_state(self->state);
}

void thermistor_toggler_init(thermistor_toggler_t* self, i_tiny_event_t* thermistor_read_event) {
  // initialize subscription
  tiny_event_subscription_init(&self->subscription, self, thermistor_callback);
  // subscribe to the press event
  tiny_event_subscribe(thermistor_read_event, &self->subscription);
}