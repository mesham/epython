#include <stdio.h>
#include <stdlib.h>
#include "misc.h"

void errorCheck(int value, char * errorMessage) {
    if (value == -1) {
        fprintf(stderr, "Error: %s\n", errorMessage);
        exit(EXIT_FAILURE);
    }
}
