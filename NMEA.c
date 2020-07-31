#include "NMEA.h"
#include <stdio.h>

uint8_t parse_gga(char *str, StructGGA *GGA_Struct){
    char *comma_start, * comma_end;

    if((str = strchr(str, '$')) == NULL){
        printf("No start \'$\' char was found.");
        return 0;
    }

    if(((*(str+1) == 'G') && (*(str+2) == 'P') && (*(str+3) == 'G')
       && (*(str+4) == 'G') && (*(str+5) == 'A')))
    {
        strcpy(GGA_Struct->id, "GPGGA");
    }else{
        printf("Sentence ID is not \"GPGGA\".");
        return 0;
    }

    comma_start = strchr(str, ',');
    comma_end = strchr(comma_start+1, ',');

    if((GGA_Struct->time = str2double(comma_start+1, comma_end-1)))



}


/*uint8_t parse_gga(char *str, StructGGA *GGA_Struct){
    char *_start;
    char *comma_start;
    char *comma_end;
    uint8_t check_init;

    _start = strchr(str, '$');

    if(!_start){
        printf("No start char is found.");
        return 0;
    }

    check_init = (*(_start+1) == 'G') && (*(_start+2) == 'P') && (*(_start+3) == 'G') && (*(_start+4) == 'G') && (*(_start+5) == 'A');

    if(!check_init){
        printf("Sentence ID is not \"GPGGA\".");
        return 0;
    }else{
        strcpy(GGA_Struct->id,"GPGGA");
    }

    str = _start;

    if(!strchr(str, '*')){
        printf("Sentence doesn't have \"*\" char in the end.");
        return 0;
    }

    comma_start = strchr(str, ',');
    comma_end = strchr(comma_start+1, ',');

    if(comma_start == NULL ||  comma_end == NULL){
        printf("No enough term to complete sentence!");
        return 0;
    }

    GGA_Struct->time = str2double(comma_start+1, comma_end-1);

    /*comma_start = comma_end;
    comma_end = strchr(comma_start+1, ',');

    if(comma_start == NULL ||  comma_end == NULL){
        printf("No enough term to complete sentence!");
        return 0;
    }

    GGA_Struct->lat = str2double(comma_start+1, comma_end-1);

    comma_start = comma_end;
    comma_end = strchr(comma_start+1, ',');

    if(comma_start == NULL ||  comma_end == NULL){
        printf("No enough term to complete sentence!");
        return 0;
    }

    GGA_Struct->NS = *(comma_start+1);

    comma_start = comma_end;
    comma_end = strchr(comma_start+1, ',');
}*/

/*
This function determines whether a char is in digit value range.
*/

uint8_t is_digit(char str){
    return str >= '0' && str <= '9';
}

/*
This function converts string to double by utilizing two pointers which point start and end character of string.
*/

double str2double(char *str_start, char *str_end){
    double num = 0;
    uint8_t is_num = 1, pow_cnt = 1;

    while(str_start++ <= str_end){
        if(!is_digit(*(str_start - 1))){
            if(*(str_start-1) == '.'){  //let if statement to calculate fraction if there is a dot in upcoming character of string.
                is_num = 0;
                continue;
            }
            printf("Not a number!");
            return 0;
        }
        if(is_num == 1){    //calculate numerator if is_num = 1;
            num = num * 10 + *(str_start-1) - '0';
        }
        if(is_num == 0){    //calculate denumerator if is_num was  changed to 0;
            num = num + (*(str_start-1) - '0') * pow(0.1, pow_cnt);
            pow_cnt++;
        }
    }

    return num;
}
