/*!
 * @file
 * @brief
 */

#ifndef thermistor_h
#define thermistor_h

#include "i_tiny_event.h"

void thermistor_init(void);
i_tiny_event_t* thermistor_read_event(void);
void thermistor_read(void);
int get_temperature(void);

#endif
