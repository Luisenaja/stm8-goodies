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

static tiny_timer_group_t timer_group;
static tiny_timer_t timer;

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
    // button_init();
    buttons_init();
    led_toggler_init(button_press_event());
    led_switch_init(on_button_press_event());
    led_switch_init(off_button_press_event());
    // pa3_heartbeat_init(&timer_group);
  }
  enableInterrupts();

  tiny_timer_start(&timer_group, &timer, 1, kick_watchdog, NULL);

  while(true) {
    tiny_timer_group_run(&timer_group);
    buttons_run();
    wfi();
  }
}
