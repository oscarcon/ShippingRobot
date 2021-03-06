#include <16F877A.h>
#fuses NOWDT, PUT, HS, NOPROTECT, NOLVP
#use delay(clock=20M)
#use rs232(baud=9600,xmit=pin_c6,rcv=pin_c7)

//#define LOW_SPEED
#define HIGH_SPEED
#include "lib/global.h"
#include "lib/sensor.h"
#include "lib/driver.h"
#include "lib/obstacle.h"
#include "lib/robot_state.h"
#include "lib/esp_comm.h"

int line_sensor = 0;
int current_position = 0;
int destination = 0;
int station = 0;
int delivered_flag = 0;

void init() {
   set_tris_b(0x01);
   port_b_pullups(1);
   set_tris_a(0xff);
   setup_ccp1(CCP_PWM);
   setup_ccp2(CCP_PWM);
   setup_timer_2(T2_DIV_BY_16, 255, 1);
}

void back_to_the_future() {
   turn180();
   int cross_count_to_the_start = 5 + destination - 1;
   current_position = 0;
   forward();
   while (current_position != cross_count_to_the_start) {
      line_sensor = read_line_sensor();
      pid_control();
   }
   stop();
   turn180();
   // reset everythings from the last run
   station = 0;
   destination = 0;
   current_position = 0;
   delivered_flag = 0;
}

int main() {
   init();
   
   while (input(PIN_B0)) {
   }
   
   set_speed(255);
   forward();
   
   while (True) {
      // wait for signal
      static int start_flag = 0;
      char str[3];
      int speed;
      while (get_esp_data_loop(str) && !start_flag) {
         start_flag = 1;
      }
      if ((speed = get_speed(str)) > 0) {
         set_speed(speed);
      }
      if ((station = get_station(str)) > 0) {
      }
      line_sensor = read_line_sensor();
      
      update_current_position();
      
      if (is_at_station()) {
         while ((destination = get_destination(str)) < 0) {
            get_esp_data_loop(str);
            stop();
         }
      }
      // control the robot follow the line
      pid_control();
      
      while (detect_obstacle()) {
         stop();
      }
      
      if (is_at_destination()) {
         stop();
         delivered_flag = 1;
         back_to_the_future();
      }
   }
   return 0;
}



