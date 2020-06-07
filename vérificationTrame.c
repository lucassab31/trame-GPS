#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vérificationTrame.h"

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