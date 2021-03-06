#ifndef __ESP_COMM__
#define __ESP_COMM__

int get_esp_data_loop(char *str) {
   if (kbhit()) {
      char c;
      int i = 0;
      while ((c = getc()) != '\n') {
         str[i] = c;
         i++;
      }
      return 1;
   }
   return 0;
}
signed int get_speed(char *str) {
   if (str[0] != '1') {
      return -1;
   }
   return str[1];
}
signed int get_destination(char *str) {
   if (str[0] != '0') {
      return -1;
   }
   return str[1];
}
signed int get_station(char *str) {
   if (str[0] != '2') {
      return -1;
   }
   return str[1];
}
#endif
