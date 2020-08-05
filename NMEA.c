#include "NMEA.h"
#include <stdio.h>

uint8_t parse_gga(char *str, StructGGA *GGA_Struct){
    char *comma_start, *comma_end;

    //Search for starting character. ($)
    if((str = strchr(str, '$')) == NULL){
        return 0;
    }

    //Search for "GPGGA" after starting character.
    if(((*(str+1) == 'G') && (*(str+2) == 'P') && (*(str+3) == 'G')
       && (*(str+4) == 'G') && (*(str+5) == 'A')))
    {
        strcpy(GGA_Struct->id, "GPGGA");
    }else{
        return 0;
    }

    //Find first and second comma to parse time.
    if((comma_start = strchr(str, ',')) == NULL || (comma_end = strchr(comma_start+1, ',')) == NULL){
        return 0.0;
    }

    //Time
    GGA_Struct->time = str2double(comma_start+1, comma_end-1);

    //Latitude
    comma_start = comma_end;

    if((comma_end = strchr(comma_start+1, ',')) == NULL){
        GGA_Struct->lat = 0.0;
        return 0;
    }

    GGA_Struct->lat = str2double(comma_start+1, comma_end-1);

    //North or South
    comma_start = comma_end;

    if((comma_end = strchr(comma_start+1, ',')) != NULL && comma_end-comma_start-2 == 0){
        GGA_Struct->NS = *(comma_end-1);
    }else{
        GGA_Struct->NS = '\0';
        return 0;
    }

    //Longitude
    comma_start = comma_end;

    if((comma_end = strchr(comma_start+1, ',')) == NULL){
        GGA_Struct->lon = 0.0;
        return 0;
    }

    GGA_Struct->lon = str2double(comma_start+1, comma_end-1);

    //East or West
    comma_start = comma_end;

    if((comma_end = strchr(comma_start+1, ',')) != NULL && comma_end-comma_start-2 == 0){
        GGA_Struct->EW = *(comma_end-1);
    }else{
        GGA_Struct->EW = '\0';
        return 0;
    }

    //Quality
    comma_start = comma_end;

    if((comma_end = strchr(comma_start+1, ',')) == NULL){
        GGA_Struct->quality = 0;
        return 0;
    }

    GGA_Struct->quality = str2uint8(comma_start+1, comma_end-1);

    //Number of Satellite
    comma_start = comma_end;

    if((comma_end = strchr(comma_start+1, ',')) == NULL){
        GGA_Struct->num_sat = 0;
        return 0;
    }

    GGA_Struct->num_sat = str2uint8(comma_start+1, comma_end-1);

    //HDOP
    comma_start = comma_end;

    if((comma_end = strchr(comma_start+1, ',')) == NULL){
        GGA_Struct->HDOP = 0.0;
        return 0;
    }

    GGA_Struct->HDOP = str2double(comma_start+1, comma_end-1);

    //MSL_Alt
    comma_start = comma_end;

    if((comma_end = strchr(comma_start+1, ',')) == NULL){
        GGA_Struct->MSL_alt = 0.0;
        return 0;
    }

    GGA_Struct->MSL_alt = str2double(comma_start+1, comma_end-1);


    //MSL_Alt Unit
    comma_start = comma_end;

    if((comma_end = strchr(comma_start+1, ',')) != NULL && comma_end-comma_start-2 == 0){
        GGA_Struct->MSL_unit = *(comma_end-1);
    }else{
        GGA_Struct->MSL_unit = '\0';
        return 0;
    }

    //GEO_SEP
    comma_start = comma_end;

    if((comma_end = strchr(comma_start+1, ',')) == NULL){
        GGA_Struct->geo_sep = 0.0;
        return 0;
    }

    GGA_Struct->geo_sep = str2double(comma_start+1, comma_end-1);


    //GEO_SEP Unit
    comma_start = comma_end;

    if((comma_end = strchr(comma_start+1, ',')) == NULL){
        GGA_Struct->geo_sep_unit = '\0';
        return 0;
    }else{
        if((comma_end-comma_start-1)/sizeof(char) > 1){

        }
    }


    if((comma_end = strchr(comma_start+1, ',')) != NULL){
        if((comma_end-comma_start-1)/sizeof(char) > 1){
            GGA_Struct->geo_sep_unit = '\0';
            return 0;
        }
        GGA_Struct->geo_sep_unit = *(comma_end-1);
    }else{

    }

    //AOD
    comma_start = comma_end;

    if((comma_end = strchr(comma_start+1, ',')) == NULL){
        GGA_Struct->AOD = 0.0;
        return 0;
    }

    GGA_Struct->AOD = str2double(comma_start+1, comma_end-1);

    //Diff State
    comma_start = comma_end;

    if((comma_end = strchr(comma_start+1, '*')) == NULL){
        GGA_Struct->diff_stat = 0.0;
        return 0;
    }

    GGA_Struct->diff_stat = str2int(comma_start+1, comma_end-1);

    return 1;
}


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
    int8_t is_positive = 1;
    uint8_t is_num = 1, pow_cnt = 1;

    if(*str_start == '-'){
        is_positive = -1;
        str_start++;
    }

    while(str_start++ <= str_end){
        if(!is_digit(*(str_start - 1))){
            if(*(str_start-1) == '.'){  //let if statement to calculate fraction if there is a dot in upcoming character of string.
                is_num = 0;
                continue;
            }
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

    return is_positive*num;
}

int str2int(char *str_start, char *str_end){
    int num = 0;
    int8_t is_positive = 1;

    if(*str_start == '-'){
        is_positive = -1;
        str_start++;
    }

    while(str_start++ <= str_end){
        if(!is_digit(*(str_start-1))){
            return 0;
        }

        num = num *10 + *(str_start-1) - '0';
    }

    return is_positive*num;
}

uint8_t str2uint8(char *str_start, char *str_end){
    int num = 0;

    while(str_start++ <= str_end){
        if(!is_digit(*(str_start-1))){
            return 0;
        }

        num = num *10 + *(str_start-1) - '0';
    }

    return num;
}
