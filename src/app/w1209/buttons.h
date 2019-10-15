/*!
 * @file
 * @brief
 */

#ifndef buttons_h
#define buttons_h

#include <stdbool.h>
#include "i_tiny_event.h"

void buttons_init(void);
i_tiny_event_t* button_press_event(void);
i_tiny_event_t* on_button_press_event(void);
i_tiny_event_t* off_button_press_event(void);
void buttons_run(void);

#endif
