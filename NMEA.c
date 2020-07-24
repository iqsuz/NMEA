#include "NMEA.h"
#include <stdio.h>

int8_t parse_gga(char *str, StructGGA *GGA){
    uint16_t cnt = 0;

    while(*(str++) != '$'){
        if(cnt++ >= GGA_LIMIT){
            return -1;
        }
    }
}

static uint8_t find_comma(char *str){
    while()
}
