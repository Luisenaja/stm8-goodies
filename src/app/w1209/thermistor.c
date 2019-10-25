/*!
 * @file
 * @brief
 */

#include "stm8s.h"
#include <stddef.h>
#include <stdbool.h>
#include "thermistor.h"
#include "adc1.h"
#include "tiny_event.h"
#include "tiny_utils.h"

static volatile tiny_adc_counts_t counts;

typedef struct {
  tiny_event_t thermistor_read_event;
  i_tiny_adc_group_t* adc_group;
} thermistor_t;

static thermistor_t thermistor;

void thermistor_init(void) {
  thermistor.adc_group = adc1_init();
  tiny_event_init(&thermistor.thermistor_read_event);
}

i_tiny_event_t* thermistor_read_event(void) {
  return &thermistor.thermistor_read_event.interface;
}

void thermistor_read(void) {
  counts = tiny_adc_group_read(thermistor.adc_group, 6);
  if(counts > 40000) {
    tiny_event_publish(&thermistor.thermistor_read_event, NULL);
    counts++;
  }
  else {
    counts++;
  }
}