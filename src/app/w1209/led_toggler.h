/*!
 * @file
 * @brief
 */

#ifndef led_toggler_h
#define led_toggler_h

#include <stdbool.h>
#include "i_tiny_event.h"

typedef struct {
  tiny_event_subscription_t subscription;
  bool state;
} led_toggler_t;

void led_toggler_init(led_toggler_t* self, i_tiny_event_t* button_press_event);

#endif
