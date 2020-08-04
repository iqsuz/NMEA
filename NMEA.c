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

    if((comma_start = strchr(str, ',')) == NULL || (comma_end = strchr(comma_start+1, ',')) == NULL){
        printf("No term found.");
        return 0.0;
    }

    if((GGA_Struct->time = str2double(comma_start+1, comma_end-1)) == 0){
        printf("Failed during TIME parsing of GGA");
        return 0;
    }

    //Latitude
    comma_start = comma_end;
    comma_end = strchr(comma_start+1, ',');

    if((GGA_Struct->lat = str2double(comma_start+1, comma_end-1)) == 0){
        printf("Failed during LAT parsing of GGA");
        return 0;
    }

    //North or South
    comma_start = comma_end;
    comma_end = strchr(comma_start+1, ',');

    if(comma_end-comma_start-1 == 0){
        printf("There is no NS information.");
        return 0;
    }

    GGA_Struct->NS = *(comma_end-1);


    //Longitude
    comma_start = comma_end;
    comma_end = strchr(comma_start+1, ',');

    if((GGA_Struct->lon = str2double(comma_start+1, comma_end-1)) == 0){
        printf("Failed during LON parsing of GGA");
        return 0;
    }


    //East or West
    comma_start = comma_end;
    comma_end = strchr(comma_start+1, ',');

    if(comma_end-comma_start-1 == 0){
        printf("There is no EW information.");
        return 0;
    }

    GGA_Struct->EW = *(comma_end-1);


    //Quality
    comma_start = comma_end;
    comma_end = strchr(comma_start+1, ',');
    GGA_Struct->quality = str2uint8(comma_start+1, comma_end-1);


    //Number of satellite
    comma_start = comma_end;
    comma_end = strchr(comma_start+1, ',');
    GGA_Struct->num_sat = str2uint8(comma_start+1, comma_end-1);

    //HDOP
    comma_start = comma_end;
    comma_end = strchr(comma_start+1, ',');

    if((GGA_Struct->HDOP = str2double(comma_start+1, comma_end-1)) == 0){
        printf("Failed during HDOP parsing of GGA");
        return 0;
    }

     //MSL_Alt
    comma_start = comma_end;
    comma_end = strchr(comma_start+1, ',');

    if((GGA_Struct->MSL_alt = str2double(comma_start+1, comma_end-1)) == 0){
        printf("Failed during HDOP parsing of GGA");
        return 0;
    }

    //MSL_Alt Unit
    comma_end = strchr(comma_end+1, ',');
    GGA_Struct->MSL_unit = *(comma_end-1);

    //GEO_Sep
    comma_start = comma_end;
    comma_end = strchr(comma_start+1, ',');

    if((GGA_Struct->geo_sep = str2double(comma_start+1, comma_end-1)) == 0){
        printf("Failed during HDOP parsing of GGA");
        return 0;
    }

    //GEO_SEP Unit
    comma_end = strchr(comma_end+1, ',');
    GGA_Struct->geo_sep_unit = *(comma_end-1);





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
            printf("Not a number!");
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
            printf("Not a number!");
            return 0;
        }

        num = num *10 + *(str_start-1) - '0';
    }

    return num;
}
