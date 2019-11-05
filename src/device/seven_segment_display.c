/*!
 * @file
 * @brief
 */

#include "stm8s_gpio.h"
#include "seven_segment_display.h"
#include <string.h>

#define init_output(_port, _pin)   \
  GPIO##_port->DDR |= (1 << _pin); \
  GPIO##_port->CR1 |= (1 << _pin)

#define write_output(_port, _pin, _state) \
  if(_state)                              \
    GPIO##_port->ODR |= (1 << _pin);      \
  else                                    \
    GPIO##_port->ODR &= ~(1 << _pin)

static void delay(void) {
  int i;
  for(i = 1; i <= 10000; i++) {
  }
}

void seven_segment_display_init(void) {
  // Turns everything on
  init_output(D, 5); // A
  init_output(A, 2); // B
  init_output(C, 7); // C
  init_output(D, 3); // D
  init_output(D, 1); // E
  init_output(A, 1); // F
  init_output(C, 6); // G
  init_output(D, 2); // P

  init_output(D, 4); // 1
  init_output(B, 5); // 2
  init_output(B, 4); // 3

  // 1 is on, 0 is off
  write_output(D, 5, 1); // A
  write_output(A, 2, 1); // B
  write_output(C, 7, 1); // C
  write_output(D, 3, 1); // D
  write_output(D, 1, 1); // E
  write_output(A, 1, 1); // F
  write_output(C, 6, 1); // G
  write_output(D, 2, 1); // P

  // 1 is off, 0 is on
  write_output(D, 4, 0); // 1
  write_output(B, 5, 0); // 2
  write_output(B, 4, 0); // 3
}

void seven_segment_display_sect_on(int section) {
  switch(section) {
    case 1:
      write_output(D, 4, 0);
      break;
    case 2:
      write_output(B, 5, 0);
      break;
    case 3:
      write_output(B, 4, 0);
      break;
    default:
      break;
  }
}

void seven_segment_display_sect_off(int section) {
  switch(section) {
    case 1:
      write_output(D, 4, 1);
      break;
    case 2:
      write_output(B, 5, 1);
      break;
    case 3:
      write_output(B, 4, 1);
      break;
    default:
      break;
  }
}

void seven_segment_display_number(char number) {
  switch(number) {
    case '1':
      write_output(D, 5, 0); // A
      write_output(A, 2, 1); // B
      write_output(C, 7, 1); // C
      write_output(D, 3, 0); // D
      write_output(D, 1, 0); // E
      write_output(A, 1, 0); // F
      write_output(C, 6, 0); // G
      write_output(D, 2, 0); // P
      break;

    case '2':
      write_output(D, 5, 1); // A
      write_output(A, 2, 1); // B
      write_output(C, 7, 0); // C
      write_output(D, 3, 1); // D
      write_output(D, 1, 1); // E
      write_output(A, 1, 0); // F
      write_output(C, 6, 1); // G
      write_output(D, 2, 0); // P
      break;
    
    case '3':
      write_output(D, 5, 1); // A
      write_output(A, 2, 1); // B
      write_output(C, 7, 1); // C
      write_output(D, 3, 1); // D
      write_output(D, 1, 0); // E
      write_output(A, 1, 0); // F
      write_output(C, 6, 1); // G
      write_output(D, 2, 0); // P
      break;

    case '4':
      write_output(D, 5, 0); // A
      write_output(A, 2, 1); // B
      write_output(C, 7, 1); // C
      write_output(D, 3, 0); // D
      write_output(D, 1, 0); // E
      write_output(A, 1, 1); // F
      write_output(C, 6, 1); // G
      write_output(D, 2, 0); // P
      break;

    case '5':
      write_output(D, 5, 1); // A
      write_output(A, 2, 0); // B
      write_output(C, 7, 1); // C
      write_output(D, 3, 1); // D
      write_output(D, 1, 0); // E
      write_output(A, 1, 1); // F
      write_output(C, 6, 1); // G
      write_output(D, 2, 0); // P
      break;

    case '6':
      write_output(D, 5, 1); // A
      write_output(A, 2, 0); // B
      write_output(C, 7, 1); // C
      write_output(D, 3, 1); // D
      write_output(D, 1, 1); // E
      write_output(A, 1, 1); // F
      write_output(C, 6, 1); // G
      write_output(D, 2, 0); // P
      break;

    case '7':
      write_output(D, 5, 1); // A
      write_output(A, 2, 1); // B
      write_output(C, 7, 1); // C
      write_output(D, 3, 0); // D
      write_output(D, 1, 0); // E
      write_output(A, 1, 0); // F
      write_output(C, 6, 0); // G
      write_output(D, 2, 0); // P
      break;

    case '8':
      write_output(D, 5, 1); // A
      write_output(A, 2, 1); // B
      write_output(C, 7, 1); // C
      write_output(D, 3, 1); // D
      write_output(D, 1, 1); // E
      write_output(A, 1, 1); // F
      write_output(C, 6, 1); // G
      write_output(D, 2, 0); // P
      break;

    case '9':
      write_output(D, 5, 1); // A
      write_output(A, 2, 1); // B
      write_output(C, 7, 1); // C
      write_output(D, 3, 1); // D
      write_output(D, 1, 0); // E
      write_output(A, 1, 1); // F
      write_output(C, 6, 1); // G
      write_output(D, 2, 0); // P
      break;

    default:
      break;

  }

}

void seven_segment_display_69(void) {
  while(1) {
    // 1 is on, 0 is off
    write_output(D, 5, 1); // A
    write_output(A, 2, 0); // B
    write_output(C, 7, 1); // C
    write_output(D, 3, 1); // D
    write_output(D, 1, 1); // E
    write_output(A, 1, 1); // F
    write_output(C, 6, 1); // G
    write_output(D, 2, 0); // P

    // 1 is off, 0 is on
    write_output(D, 4, 1); // 1
    write_output(B, 5, 0); // 2
    write_output(B, 4, 1); // 3

    delay();

    // 1 is on, 0 is off
    write_output(D, 5, 1); // A
    write_output(A, 2, 1); // B
    write_output(C, 7, 1); // C
    write_output(D, 3, 0); // D
    write_output(D, 1, 0); // E
    write_output(A, 1, 1); // F
    write_output(C, 6, 1); // G
    write_output(D, 2, 0); // P

    // 1 is off, 0 is on
    write_output(D, 4, 1); // 1
    write_output(B, 5, 1); // 2
    write_output(B, 4, 0); // 3

    delay();
  }
}

void seven_segment_display_temp(char* temp_str) {

  int length = strlen(temp_str);

  if(length == 1) {
    seven_segment_display_sect_off(1);
    seven_segment_display_sect_off(2);
    seven_segment_display_sect_on(3);
    seven_segment_display_number(temp_str[0]);
  }

  if(length == 2) {
    while(1) {
      seven_segment_display_sect_off(1);
      for(int i = 0; i < length; i++) {
        if(i == 0) {
          seven_segment_display_sect_on(2);
          seven_segment_display_sect_off(3);
        } else if (i == 1) {
          seven_segment_display_sect_off(2);
          seven_segment_display_sect_on(3);
        }
        seven_segment_display_number(temp_str[i]);
        delay();
      }
    }
  }

  if(length == 3) {
    while(1) {
      for(int i = 0; i < length; i++) {
        if(i == 0) {
          seven_segment_display_sect_on(1);
          seven_segment_display_sect_off(2);
          seven_segment_display_sect_off(3);
        } else if (i == 1) {
          seven_segment_display_sect_off(1);
          seven_segment_display_sect_on(2);
          seven_segment_display_sect_off(3);
        } else if (i == 2) {
          seven_segment_display_sect_off(1);
          seven_segment_display_sect_off(2);
          seven_segment_display_sect_on(3);
        }
        seven_segment_display_number(temp_str[i]);
        delay();
      }
    }
  }
}