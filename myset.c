#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "parse.h"

#define SET_COUNT 6

void instructions() {
    printf("Set Calculator:\n");
    printf("1) You have 6 sets you can use: \n\tSETA, SETB, SETC,\n\tSETD, SETE, SETF\n");
    printf("2) sets support any number between 0-127.\n");
    printf("3) You can use the following commands:\n");
    printf("\n\tread_set SET# n1, n2, n3, ..., nn, -1  \n");
    printf("\t# stores n1-nn in SET#\n");
    printf("\n\tprint_set SET#  \n");
    printf("\t# prints the memners of SET#\n");
    printf("\n\tunion_set SET# SET# SET#(result)  \n");
    printf("\t# stores the union of the 1st & 2nd set in the result in the 3rd.\n");
    printf("\n\tintersect_set SET# SET# SET#(result)  \n");
    printf("\t# stores the intersection of the 1st & 2nd set in the result in the 3rd.\n");
    printf("\n\tsub_set SET# SET# SET#(result)  \n");
    printf("\t# subtract the 2nd set from the 1st set & stores the result in the 3rd.\n");
    printf("\n\tsymdiff_set SET# SET# SET#(result)  \n");
    printf("\t# stores the symmetric difference of the 1st & 2nd set in the result in the 3rd.\n");
    printf("\n\tstop\n");
    printf("\t# end the program.\n");
}

int main() {
    set SETA = {0},
        SETB = {0},
        SETC = {0},
        SETD = {0},
        SETE = {0},
        SETF = {0};

    set *sets[] = { &SETA, &SETB, &SETC, &SETD, &SETE, &SETF };
    char *names[] = { "SETA", "SETB", "SETC", "SETD", "SETE", "SETF" };
    int set_count = 6;

    execute("sprint_set SETA", sets, names, set_count);

    return 0;
}