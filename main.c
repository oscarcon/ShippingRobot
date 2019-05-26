#include <16F877A.h>
#fuses NOWDT, PUT, HS, NOPROTECT, NOLVP
#use delay(clock=20M)
#use rs232(baud=9600,xmit=pin_c6,rcv=pin_c7)

//#define LOW_SPEED
#define HIGH_SPEED
#include "global.h"
#include "sensor.h"
#include "driver.h"
#include "obstacle.h"
#include "robot_state.h"
#include "esp_comm.h"

int line_sensor = 0;
int destination = 0;
int station = 0;
void init() {
   set_tris_b(0x01);
   port_b_pullups(1);
   set_tris_a(0xff);
   setup_ccp1(CCP_PWM);
   setup_ccp2(CCP_PWM);
   setup_timer_2(T2_DIV_BY_16, 255, 1);
}

int main() {
   init();
   
   while (input(PIN_B0)) {
   }
   
   set_speed(255);
   forward();
   
   while (True) {
      // wait for signal
      
      destination = get_destination();
      while ( !destination ) {
      }
      line_sensor = read_line_sensor();
      /*signed int x = distance();
     */
      // control the robot follow the line
      pid_control();
      
      //avoid_obstacle();

     // stop_at_destination();
      
     // return_to_start();
      
     // stop();
      
      // destination = 0;  */
   }
   return 0;
}



