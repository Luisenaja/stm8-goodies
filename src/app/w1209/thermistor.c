/*!
 * @file
 * @brief
 */

#include "stm8s.h"
#include <stddef.h>
#include <stdbool.h>
#include "thermistor.h"
#include "tiny_timer.h"
#include "adc1.h"
#include "tiny_event.h"
#include "tiny_timer.h"
#include "tiny_utils.h"

#define ADC_RAW_TABLE_SIZE sizeof raw_adc_counts / sizeof raw_adc_counts[0]
#define ADC_RAW_TABLE_BASE_TEMP 20
#define ADC_COUNTS_MIN 33587

/* Look-up table for raw ADC counts for every degree between
   20 F and 110 F */
static const tiny_adc_counts_t raw_adc_counts[] = {
  58787, 58507, 58227, 57947, 57667, 57387, 57107, 56827, 56547, 56267, 55987, 55707, 55427, 55147, 54867, 54587, 54307, 54027, 53747, 53467, 53187, 52907, 52627, 52347, 52067, 51787, 51507, 51227, 50947, 50667, 50387, 50107, 49827, 49547, 49267, 48987, 48707, 48427, 48147, 47867, 47587, 47307, 47027, 46747, 46467, 46187, 45907, 45627, 45347, 45067, 44787, 44507, 44227, 43947, 43667, 43387, 43107, 42827, 42547, 42267, 41987, 41707, 41427, 41147, 40867, 40587, 40307, 40027, 39747, 39467, 39187, 38907, 38627, 38347, 38067, 37787, 37507, 37227, 36947, 36667, 36387, 36107, 35827, 35547, 35267, 34987, 34707, 34427, 34147, 33867, 33587
};

typedef struct {
  tiny_event_t thermistor_read_event;
  i_tiny_adc_group_t* adc_group;
} thermistor_t;

static thermistor_t thermistor;
static tiny_timer_t timer;
static uint8_t temperatures[10];
static uint8_t temperature_index;
static uint8_t sample_count;
static size_t size_temperatures = sizeof(temperatures) / sizeof(temperatures[0]);

static uint8_t get_temperature(tiny_adc_counts_t counts) {
  unsigned char right_bound_temp_index = ADC_RAW_TABLE_SIZE;
  unsigned char left_bound_temp_index = 0;

  // Search through the raw ADC temperature table
  while(right_bound_temp_index - left_bound_temp_index > 1) {
    unsigned char mid_temp_index = ((left_bound_temp_index + right_bound_temp_index) >> 1);

    if(counts > raw_adc_counts[mid_temp_index]) {
      right_bound_temp_index = mid_temp_index;
    }
    else {
      left_bound_temp_index = mid_temp_index;
    }
  }

  // Estimate low if between two values
  return ADC_RAW_TABLE_BASE_TEMP + left_bound_temp_index;
}

static uint8_t get_average_temperature(void) {
  uint16_t sum = 0;
  for(uint16_t i = 0; i < size_temperatures; i++) {
    sum += temperatures[i];
  }
  return sum / size_temperatures;
}

static void thermistor_read(tiny_timer_group_t* timer_group, void* context) {
  (void)context;
  tiny_adc_counts_t counts = tiny_adc_group_read(thermistor.adc_group, 6);

  if(counts > ADC_COUNTS_MIN) {
    temperatures[temperature_index++] = get_temperature(counts);
  }
  else {
    temperatures[temperature_index++] = ADC_RAW_TABLE_BASE_TEMP;
  }

  // fill up the temperatures array and wrap back around the index
  temperature_index %= size_temperatures;

  // if gotten enough samples
  if(sample_count == size_temperatures) {
    // get average and publish it
    uint8_t average_temperature = get_average_temperature();
    tiny_event_publish(&thermistor.thermistor_read_event, &average_temperature);
  }
  else {
    sample_count++;
  }

  tiny_timer_start(timer_group, &timer, 100, thermistor_read, NULL);
}

void thermistor_init(tiny_timer_group_t* timer_group) {
  thermistor.adc_group = adc1_init();
  tiny_event_init(&thermistor.thermistor_read_event);
  thermistor_read(timer_group, NULL);
}

i_tiny_event_t* thermistor_read_event(void) {
  return &thermistor.thermistor_read_event.interface;
}
