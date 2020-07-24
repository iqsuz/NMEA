#include "../NMEA.h"

int main(){
    char *str = "mehmet ali ipsuz $ sever.";
    StructGGA strc;

    parse_gga(str, &strc);
    return 0;
}
