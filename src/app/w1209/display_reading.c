/*!
 * @file
 * @brief
 */

#include <stm8s.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include "display_reading.h"
#include "led.h"
#include "thermistor.h"
#include "tiny_utils.h"
#include "seven_segment_display.h"

static void display_reading_callback(void* context, const void* args) {
  reinterpret(self, context, display_reading_t*);
  reinterpret(temperature, args, const uint8_t*);

  char buffer[4];
  sprintf(buffer, "%3d", *temperature);

  // Display temperature
  seven_segment_display_temp(buffer);
}

void display_reading_init(display_reading_t* self, i_tiny_event_t* thermistor_read_event) {
  // initialize subscription
  tiny_event_subscription_init(&self->subscription, self, display_reading_callback);
  // subscribe to the thermistor read event
  tiny_event_subscribe(thermistor_read_event, &self->subscription);
}
