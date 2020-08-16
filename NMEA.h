#ifndef _NMEA_H_
    #define _NMEA_H_

    #include <stdint.h>
    #include <string.h>

    typedef struct {
        char id[5];
        double time;
        double lat;
        char NS;
        double lon;
        char EW;
        uint8_t quality;
        uint8_t num_sat;
        double HDOP;
        double MSL_alt;
        char MSL_unit;
        double geo_sep;
        char geo_sep_unit;
        double AOD;            //Variable type needs to be checked to see if it is correct.
        int diff_stat;      //Variable type needs to be checked to see if it is correct.
        int checksum;
    }StructGGA;

    uint8_t parse_gga(char *, StructGGA *);
    double str2double(char *, char *);
    int str2int(char *, char *);
    uint8_t str2uint8(char *, char *);
#endif // _NMEA_H_
