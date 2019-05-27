// check robot position and status
#include "global.h"
#ifndef __ROBOT_STATE__
#define __ROBOT_STATE__

int is_at_cross() {
   if (line_sensor == 0b00011011) {
      return 1;
   }
   else {
      return 0;
   }
}
int update_current_position() {
   static long last_time = 0, period;
   if (is_at_cross()) {
      period = __TIME__ - last_time;
   }
   else {
      last_time = __TIME__;
   }
   if (period > 50) {
      current_position++;
   }
   return current_position;
}

int is_at_destination() {
   if (current_position > 5) {
      if (current_position - 5 == destination) {
         return 1;
      }
   }
   return 0;
}
int is_at_station() {
   if (current_position == station) {
      return 1;
   }
   return 0;
}

#endif
