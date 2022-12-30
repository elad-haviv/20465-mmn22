#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "set.h"

void read_set(set target, byte members[], byte count) {
    byte i;

    empty_set(target);
    for (i = 0; i < count; i++) {
        set_member(target, members[i]);
    }
}

/* TODO: make it return the set as a string instead of printing it. */
char *print_set(set target) {
    byte i, count;
    char *output = malloc(1);

    for (i = 0, count = 0; i < SET_WIDTH; i++) {
        if (!in_set(target, i)) {
            continue;
        }

        printf("%d%c", i, (count++ % 16) == 15 ? '\n' : ' ');
    }

    if (!count) {
        printf("This set is empty.");
    }

    printf("\n");

    free(output);
    return "";
}

void union_set(set a, set b, set target) {
    int i;
    for (i = 0; i < SET_CHARS; i++) {
        target[i] = a[i] | b[i];
    }
}

void intersect_set(set a, set b, set target) {
    int i;
    for (i = 0; i < SET_CHARS; i++) {
        target[i] = a[i] & b[i];
    }
}

void sub_set(set a, set b, set target) {
    int i;
    for (i = 0; i < SET_CHARS; i++) {
        target[i] = a[i] & ~(a[i] & b[i]);
    }
}

void symdiff_set(set a, set b, set target) {
    int i;
    for (i = 0; i < SET_CHARS; i++) {
        target[i] = (a[i] | b[i]) & ~(a[i] & b[i]);
    }
}

byte byte_pos(byte number) {
    return number / CHAR_BIT;
}

byte bit_pos(byte number) {
    return number % CHAR_BIT;
}

byte member(byte byte_pos, byte bit_pos) {
    return byte_pos * CHAR_BIT + bit_pos;
}

byte in_set(set target, byte number) {
    byte b = target[(int)byte_pos(number)];
    return (b & (1 << (int)bit_pos(number))) != 0;
}

void set_member(set target, byte number) {
    byte *b = &target[byte_pos(number)];
    byte mask = 1 << bit_pos(number);
    *b = (*b | mask);

}

void clear_member(set target, byte number) {
    byte *b = &target[(int)byte_pos(number)];
    byte mask = 1 << bit_pos(number);
    *b  = ~(*b) | mask;
}

void toggle_member(set target, byte number) {
    byte *b = &target[(int)byte_pos(number)];
    byte mask = 1 << bit_pos(number);
    *b  = *b ^ mask;
}

void empty_set(set target) {
    byte i;
    for(i = 0; i < SET_CHARS; i++) {
        target[i] = 0;
    }
}