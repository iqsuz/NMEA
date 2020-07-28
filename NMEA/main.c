#include "../NMEA.h"

void foo(char *str){
    char cnt = 'a';
    str = &cnt;

}

int main(){
    char *str = "$GPGGA,092750.123,5321.6802,N,00630.3372,W,1,8,1.03,61.7,M,55.2,M,,*76";
    StructGGA GGA_Struct;

    parse_gga(str, &GGA_Struct);
    printf("Time is: %f\n",GGA_Struct.time);
    printf("Latitude is: %f",GGA_Struct.lat);
    printf("%c\n",GGA_Struct.NS);


}
