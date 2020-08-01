#ifndef _NMEA_H_
    #define _NMEA_H_

    #include <stdint.h>
    #include <string.h>

    #define GGA_PARAM_LIMIT 1000
    #define GGA_COMMA 14

    #define COMMA_LIMIT 20


    typedef enum {
        DTM,
        GBS,
        GGA,
        GLL,
        GPQ,
        GRS,
        GSA,
        GST,
        GSV,
        RMC,
        THS,
        TXT,
        VTG,
        ZDA
    }TypeGP;

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
        uint8_t AOD;            //Variable type needs to be checked to see if it is correct.
        uint8_t diff_stat;      //Variable type needs to be checked to see if it is correct.
        uint8_t checksum;
    }StructGGA;

    uint8_t parse_gga(char *, StructGGA *);
    double str2double(char *, char *);
    uint8_t str2int8(char *, char *);
#endif // _NMEA_H_
