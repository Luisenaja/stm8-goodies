/*!
 * @file
 * @brief
 */

#ifndef button_h
#define button_h

#include <stdbool.h>
#include "i_tiny_event.h"

void button_init(void);
i_tiny_event_t* button_press_event(void);
bool button_pressed(void);
void button_run(void);

#endif
