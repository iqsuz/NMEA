#include "NMEA.h"
#include <stdio.h>



int8_t parse_gga(char *str){
    uint8_t comma_num = 0;
    uint16_t cnt = 0;
    uint8_t comma[GGA_COMMA];

    char *_start;
    char *_end;
    char *_comma;

    _start = strchr(str, '$');
    str = _start;
    _end = strchr(str, '*');
    _comma = strchr(str, ',');


    if(_start == NULL || _end == NULL || _comma == NULL){
        printf("\'$\', \'*\' or \',\' is missing in string.");
        return -1;
    }

    comma[comma_num] = _comma-str;

    for(cnt = 0; *(str+cnt) != NULL; cnt++){

    }


    while(_comma != NULL){
        _comma = strchr(_comma+1, ',');
        comma_num++;
        comma[comma_num] = _comma-str;
    }

    if(comma_num != GGA_COMMA){
        printf("Not enough parameters to represent GGA.");
        return -1;
    }

}

static uint8_t find_comma(char *str){

}


uint8_t parse_gga2(char *str, StructGGA *GGA_Struct){
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
