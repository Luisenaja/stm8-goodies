/*!
 * @file
 * @brief
 */

#ifndef thermistor_toggler_h
#define thermistor_toggler_h

#include <stdbool.h>
#include "i_tiny_event.h"

typedef struct {
  tiny_event_subscription_t subscription;
  bool state;
} thermistor_toggler_t;

void thermistor_toggler_init(thermistor_toggler_t* self, i_tiny_event_t* thermistor_read_event);

#endif
