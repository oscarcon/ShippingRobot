// check robot position and status
#include "global.h"
#ifndef __ROBOT_STATE__
#define __ROBOT_STATE__

int is_at_station() {
   if (line_sensor == 0b00011011) {
      return 1;
   }
   else {
      return 0;
   }
}
int current_station() {
   
   return 0;
}
void stop_at_destination() {

}

void return_to_start() {
}


#endif
