#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "convertionCoordonnées.h"

void convertirCoordonnee(char** extrait){
    convertirlatitude(extrait[1]);
    printf("%s\n", extrait[2]);
    convertirlongitude(extrait[3]);
    printf("%s\n", extrait[4]);
}
void convertirlatitude(char *latitude) {
    int latit = strtol(latitude, NULL, 10);
    int minute = latit % 100;
    int degres = ((latit%100000)-minute)/100;
    strtok(latitude, ".");
    float seconde = (strtol(strtok(NULL, "."), NULL, 10) * 60) / 10000;
    printf("Latitude : %d° %d' %.2f\" ", degres,minute, seconde);
}
void convertirlongitude(char *longitude) {
    int longi = strtol(longitude, NULL, 10);
    int minute = longi % 100;
    int degres = ((longi%100000)-minute)/100;
    strtok(longitude, ".");
    float seconde = (strtol(strtok(NULL, "."), NULL, 10) *60) / 10000;
    printf("Longitude : %d° %d' %.2f\" ", degres, minute, seconde);
}