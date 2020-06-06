#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

void main() {
    char trame[] = "$GPGGA,092750.000,5321.6802,N,00630.3372,W,1,8,1.03,61.7,M,55.2,M,,*76";
    char trame2[] = "$GPGGA,092751.000,5321.6802,N,00630.3371,W,1,8,1.03,61.7,M,55.3,M,,*75";

    if (verifierTrame(trame, sizeof(trame)) == 1) {
        printf("Trame GPS : \n%s\n", trame);
        char** extrait = (char**) malloc(10 * sizeof(char*));
        if (extraireTrame(trame, extrait) == 1) {

            printf("De coordonées :\n");
            convertirCoordonnee(extrait);
            printf("Reçut à :\n");
            formatHeure(extrait[0]);
        } else {
            printf("Une erreure est survenue lors de la segmentation");
        }
        
    } else {
        printf("La trame ne correspond pas au format $GPGGA");
    }    
}

int verifierTrame(char *trame, int size) {
    
    if (strstr(trame, "$GPGGA") != NULL) {
        int nbChamps = 0;
        for(int i=0; i < size; i++) {
            if(trame[i] == ',') {
                nbChamps++;
            }
        }
        nbChamps++;
        if (nbChamps == 15) {
            char delim[] = "$*";
            if (checksum(strtok(trame, delim)) == strtol(strtok(NULL, delim), NULL, 16)) {
                return 1;
            } else {
                return 0;
            } 
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}
int checksum(const char *s) {
    int c = 0;

    while (*s)
        c ^= *s++;

    return c;
}

int extraireTrame(char* trame, char** extrait) {
    char* ptr = strtok(trame, ",");
    
    for (int i=0; i < 10; i++){   
        ptr = strtok(NULL, ",");
        extrait[i] = (char*) calloc(strlen(ptr), sizeof(char));
        if(NULL == extrait[i]){
            return -1;
        }
        strcpy( extrait[i], ptr );
    }
    return 1;
}

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

void formatHeure(char *heure) {
    int time = strtol(heure, NULL, 10);
    int secondes = time%100;
    int minutes = ((time%10000)-secondes)/100;
    int heures = ((time%1000000)-minutes-secondes)/10000;;
    printf("%dh ", heures);
    printf("%dmin ", minutes);
    printf("%ds\n", secondes);
}