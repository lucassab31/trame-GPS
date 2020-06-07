#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vérificationTrame.h"
#include "convertionCoordonnées.h"
#include "formatageHeure.h"

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