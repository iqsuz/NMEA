#include "NMEA.h"
#include <stdio.h>

uint8_t parse_gga(char *str, StructGGA *GGA_Struct){
    char *_start;
    char *comma_start;
    char *comma_end;
    uint8_t check_init;

    _start = strchr(str, '$');

    if(!_start){
        printf("No start char is found.");
        return -1;
    }

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

    comma_start = strchr(str, ',');
    comma_end = strchr(comma_start+1, ',');

    if(comma_start == NULL ||  comma_end == NULL){
        printf("No enough term to complete sentence!");
        return -1;
    }

    GGA_Struct->time = str2double(comma_start, comma_end);

    comma_start = comma_end;
    comma_end = strchr(comma_start+1, ',');

    if(comma_start == NULL ||  comma_end == NULL){
        printf("No enough term to complete sentence!");
        return -1;
    }

    GGA_Struct->lat = str2double(comma_start, comma_end);

    comma_start = comma_end;
    comma_end = strchr(comma_start+1, ',');

    if(comma_start == NULL ||  comma_end == NULL){
        printf("No enough term to complete sentence!");
        return -1;
    }

    GGA_Struct->NS = *(comma_start+1);

    comma_start = comma_end;
    comma_end = strchr(comma_start+1, ',');
}

uint8_t is_digit(char str){
    return str >= '0' && str <= '9';
}

double str2double(char *str_start, char *str_end){
    double num = 0.0;
    double frac = 0.0;
    uint8_t cnt = 0;

    while(*(++str_start) != '.'){
        if(str_start == str_end-1){
            return num;
        }
        if(is_digit(*str_start)){
            num = num * 10 + *str_start - '0';
        }else{
            printf("Not a number!");
            return 0.0;
        }
    }

    while(++str_start != (str_end)){
        cnt++;
        if(is_digit(*str_start)){
            frac = frac + (*str_start - '0') * pow(0.1, cnt);
        }else{
            printf("Not a number!");
            return 0.0;
        }
    }

    return num+frac;
}
