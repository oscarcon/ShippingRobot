#ifndef __ESP_COMM__
#define __ESP_COMM__
int get_destination() {
   if (kbhit()) {
      return getc() - 49; 
   }
   return -1;
}
#endif
