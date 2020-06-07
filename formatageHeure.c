#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "formatageHeure.h"

void formatHeure(char *heure) {
    int time = strtol(heure, NULL, 10);
    int secondes = time%100;
    int minutes = ((time%10000)-secondes)/100;
    int heures = ((time%1000000)-minutes-secondes)/10000;;
    printf("%dh ", heures);
    printf("%dmin ", minutes);
    printf("%ds\n", secondes);
}