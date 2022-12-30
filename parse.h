#ifndef MAMAN_22_PARSE_H
#define MAMAN_22_PARSE_H
#include "set.h"

/* Operation types after parsing. */
typedef enum {
    PRINT_SET = 0,
    READ_SET,
    UNION_SET,
    INTERSECT_SET,
    SUB_SET,
    SYMDIFF_SET,
    STOP_OP,
    INVALID_OP
} Operation;

/* Types of tokens for parsing. */
typedef enum {
    T_INVALID = 0,
    T_OPERATION,
    T_SET,
    T_LIST_END,
    T_NUMBER,
    T_COMMA,
    T_NEWLINE,
    T_EOF
} Token;

/* Command struct to run, built after parsing. */
typedef struct {
    char *command;
    Operation op;
    char *params;
} Command;

Token get_token(char *str);

Operation get_operation(char *str);

char *next();

byte is_set(char *str, char *set_names[], byte count);

set *get_set(char *str, set *valid_sets[], char *set_names[], byte count);

byte is_number(char *str);

byte get_number(char *str);

void execute(char *input, set *valid_sets[], char *set_names[], byte count);

void parse_command(char *token, set *sets[], char *set_names[], byte count);

void parse_print_cmd(char *token, set *sets[], char *set_names[], byte count);

#endif /* MAMAN_22_PARSE_H */
