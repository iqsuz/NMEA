#include "NMEA.h"
#include <stdio.h>

uint8_t parse_gga(char *str, StructGGA *GGA_Struct){
    char *_start;
    char *comma;
    char *tmp;
    uint8_t check_init, cnt;

    _start = strchr(str, '$');
    check_init = (*(_start+1) == 'G') && (*(_start+2) == 'P') && (*(_start+3) == 'G') && (*(_start+4) == 'G') && (*(_start+5) == 'A');

    if(!check_init){
        printf("Sentence ID is not \"GPGGA\".");
        return -1;
    }else{
        strcpy(GGA_Struct->id,"GPGGA");
    }

    str = _start;

    if(!strchr(str, '*')){
        printf("Sentence doesn't have \"*\" char in the end.");
        return -1;
    }

    comma = strchr(str, ',');

    for(cnt = 0; *(++comma) != ','; cnt++){
        *(tmp+cnt) = *(comma);
    }

}

uint8_t is_digit(char *str){
    return *str >= '0' && *str<= '9';
}

double str2double(char *str){
    float num = 0.0;
    float frac = 0.0;
    uint8_t cnt;

    while(*(str++) != '.'){
        num = num * 10 + *(str-1) - '0';
    }

    for(cnt = 1; *(str++) != '\0'; cnt++){
        frac = frac + (*(str-1) - '0') * pow(0.1,cnt);
    }

    return num+frac;
}
