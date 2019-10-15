/*!
 * @file
 * @brief
 */

#ifndef led_switch_h
#define led_switch_h

#include <stdbool.h>
#include "i_tiny_event.h"

void led_switch_init(i_tiny_event_t* button_press_event);

#endif
