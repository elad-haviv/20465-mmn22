#ifndef MAMAN_22_SET_H
#define MAMAN_22_SET_H
#include <limits.h>

/* required set size in bits */
#define SET_WIDTH 128

/* the size of a set in chars to reach SET_WIDTH */
#define SET_CHARS SET_WIDTH/CHAR_BIT

/* byte definition, for easier context.
   takes less memory than int */
typedef unsigned char byte;

/* set definition, an array of bytes (chars) with memory of 128 bits */
typedef byte set[SET_CHARS];

/* Takes a set and populates it with members */
void read_set(set target, byte members[], byte count);

/* return a string to nicely print the set.
   this function is required not to actually print according to maman instructions. */
char *print_set(set target);

/* performs union of sets a and b, puts it in the target set */
void union_set(set a, set b, set target);

/* performs intersection of sets a and b, puts it in the target set */
void intersect_set(set a, set b, set target);

/* performs suntratction of set b from set a, puts it in the target set */
void sub_set(set a, set b, set target);

/* performs symmetric difference of sets a and b, puts it in the target set */
void symdiff_set(set a, set b, set target);

/* ends the program */
void stop();

/* Helper functions for dealing with data that is split to chunks: */
/* determines the byte in which the number is represented */
byte byte_pos(byte number);

/* determines which bit represents the number in the byte */
byte bit_pos(byte number);

/* returns the number represented by a cretain bit in a a certain byte */
byte member(byte byte_pos, byte bit_pos);

/* tells us if a number is in the set */
byte in_set(set target, byte number);

/* sets a bit representing a number in the target set */
void set_member(set target, byte number);

/* clears a bit representing a number in the target set */
void clear_member(set target, byte number);

/* toggles a bit representing a number in the target set */
void toggle_member(set target, byte number);

/* sets the target to the empty set. */
void empty_set(set target);

#endif /* MAMAN_22_SET_H */
