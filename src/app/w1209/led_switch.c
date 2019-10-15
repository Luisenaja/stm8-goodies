/*!
 * @file
 * @brief
 */

#include <stm8s.h>
#include <stddef.h>
#include <stdbool.h>
#include "led_switch.h"
#include "led.h"

static tiny_event_subscription_t subscription;
static bool state;

static void button_callback(void* context, const void* args) {
  // toggle the led
  (void)context;
  (void)args;
  state = !state;
  led_set_state(state);
}

void led_switch_init(i_tiny_event_t* button_press_event) {
  // initialize subscription
  tiny_event_subscription_init(&subscription, NULL, button_callback);
  // subscribe to the press event
  tiny_event_subscribe(button_press_event, &subscription);
}