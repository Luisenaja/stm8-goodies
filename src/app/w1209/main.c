/*!
 * @file
 * @brief
 */

#include <stdbool.h>
#include <stddef.h>
#include "stm8s.h"
#include "clock.h"
#include "tim4_system_tick.h"
#include "pa3_heartbeat.h"
#include "tiny_timer.h"
#include "watchdog.h"
// #include "button.h"
#include "buttons.h"
#include "led.h"
#include "led_toggler.h"
#include "led_switch.h"
#include "i_tiny_adc_group.h"
#include "thermistor.h"
#include "thermistor_toggler.h"
#include "seven_segment_display.h"

static tiny_timer_group_t timer_group;
static tiny_timer_t timer;
static thermistor_toggler_t thermistor_toggler;
static led_toggler_t button_toggler;
static led_toggler_t on_button_toggler;
static led_toggler_t off_button_toggler;
int temperature;

static void kick_watchdog(tiny_timer_group_t* _timer_group, void* context) {
  (void)context;
  (void)_timer_group;
  watchdog_kick();
  tiny_timer_start(&timer_group, &timer, 1, kick_watchdog, NULL);
}

void main(void) {
  disableInterrupts();
  {
    watchdog_init();
    clock_init();
    tiny_timer_group_init(&timer_group, tim4_system_tick_init());
    led_init();
    buttons_init();
    thermistor_init();
    thermistor_toggler_init(&thermistor_toggler, thermistor_read_event());
    led_toggler_init(&button_toggler, button_press_event());
    led_toggler_init(&on_button_toggler, on_button_press_event());
    led_toggler_init(&off_button_toggler, off_button_press_event());
    seven_segment_display_init();
    // pa3_heartbeat_init(&timer_group);
  }
  enableInterrupts();

  tiny_timer_start(&timer_group, &timer, 1, kick_watchdog, NULL);

  while(true) {
    tiny_timer_group_run(&timer_group);
    buttons_run();
    thermistor_read();
    temperature = get_temperature();
    wfi();
  }
}
