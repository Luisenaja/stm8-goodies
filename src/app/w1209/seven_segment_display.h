
/*!
 * @file
 * @brief
 */

#ifndef seven_segment_display_h
#define seven_segment_display_h

#include "i_tiny_event.h"

void seven_segment_display_init(i_tiny_event_t* interrupt);
void seven_segment_display_temp(char* temperature);

#endif
