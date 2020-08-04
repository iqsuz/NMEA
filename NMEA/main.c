#include "../NMEA.h"

int main(){
    char *str = "$GPGGA,092750.123,5321.6802,N,00630.3372,W,6,-8,1.03,61.7,M,55.2,M,,*76";
    StructGGA GGA_Struct;

    if(parse_gga(str, &GGA_Struct)){
        printf("ID: %s\n", GGA_Struct.id);
        printf("Time is: %f\n", GGA_Struct.time);
        printf("Latitude is: %f", GGA_Struct.lat);
        printf("%c\n", GGA_Struct.NS);
        printf("Longitude is: %f", GGA_Struct.lon);
        printf("%c\n", GGA_Struct.EW);
        printf("Quality: %d\n", GGA_Struct.quality);
        printf("Number of Satellite: %d\n", GGA_Struct.num_sat);
        printf("HDOP: %f\n", GGA_Struct.HDOP);
        printf("MSL Altitude: %f", GGA_Struct.MSL_alt);
        printf("%c\n", GGA_Struct.MSL_unit);
        printf("GEO Separation: %f", GGA_Struct.geo_sep);
        printf("%c\n", GGA_Struct.geo_sep_unit);
        printf("AOD: %d\n", GGA_Struct.AOD);
        printf("Diff Stat: %d\n", GGA_Struct.diff_stat);
    }
}
