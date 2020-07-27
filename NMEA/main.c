#include "../NMEA.h"

int main(){
    char *str = "$GPGGA,092750.000,5321.6802,N,00630.3372,W,1,8,1.03,61.7,M,55.2,M,,*76";
    double a;
    a = str2double(str+6,str+9);
    printf("%f",a);
    return 0;
}
