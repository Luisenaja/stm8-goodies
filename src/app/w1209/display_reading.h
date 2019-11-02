/*!
 * @file
 * @brief
 */

#ifndef display_reading_h
#define display_reading_h

#include <stdbool.h>
#include "i_tiny_event.h"

typedef struct {
  tiny_event_subscription_t subscription;
} display_reading_t;

void display_reading_init(display_reading_t* self, i_tiny_event_t* thermistor_read_event);

#endif
