#ifndef __SENSOR__
#define __SENSOR__
#include "global.h"
/*#include "driver.h"
// d5 d6 d7 lll s1 s2 s3
void dk_line()
{
   if(input(pin_d5)==0 && input(pin_d6)==0 && input(pin_d7)==0){
         dk_dc(0);
      }
   if(input(pin_d5)==1 && input(pin_d6)==0 && input(pin_d7)==1){
         dk_dc(0);
      }
   if(input(pin_d5)==0 && input(pin_d6)==0 && input(pin_d7)==1){
        dk_dc(-2);
   }
   if(input(pin_d5)==1 && input(pin_d6)==0 && input(pin_d7)==0){
         dk_dc(2);
   }
   if(input(pin_d5)==0 && input(pin_d6)==1 && input(pin_d7)==1){
        dk_dc(-2);
   }
   if(input(pin_d5)==1 && input(pin_d6)==1 && input(pin_d7)==0){
         dk_dc(2);
   }
}*/
int read_line_sensor() {
   return (~input_a())&0x1f;
}
signed int distance() {
   static signed int last_value = 0;
   if (line_sensor == 0b00000100) {
      return 0;
   }
   if (line_sensor == 0b00010000) {
      return -3;
   }
   if (line_sensor == 0b00001100) {
      return -2;
   }
   if (line_sensor == 0b00001000) {
      return -1;
   }
   if (line_sensor == 0b00000010) {
      return 1;
   }
   if (line_sensor == 0b00000110) {
      return 2;
   }
   if (line_sensor == 0b00000001) {
      return 3;
   }
   else {
      return last_value;
   }
   last_value = line_sensor;
}

int detect_obstacle() {
   return 0;
}

#endif
