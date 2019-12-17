/*!
 * @file
 * @brief
 */

#ifndef thermistor_h
#define thermistor_h

#include "i_tiny_event.h"
#include "tiny_timer.h"

void thermistor_init(tiny_timer_group_t* timer_group);
i_tiny_event_t* thermistor_read_event(void);

#endif
