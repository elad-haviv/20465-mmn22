#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "parse.h"

int error = 0, end = 0;

char *TOKEN_TYPES[8] = {
    "T_INVALID",
    "T_OPERATION",
    "T_SET",
    "T_LIST_END",
    "T_NUMBER",
    "T_COMMA",
    "T_NEWLINE",
    "T_EOF"
};

void execute(char *input, set *sets[], char *set_names[], byte count) {
    printf("DEBUG: input is '%s'\n", input);

    int pos = 0;
    char *token = strtok(input, " \t");

    printf("First token");

    while (token != NULL && end == 0) {
        switch (get_token(token)) {
            case T_OPERATION:
                 parse_command(token, sets, set_names, count);
                 break;
            case T_EOF:
                fprintf(stderr, "Error: reached End of File without stop command.");
                error = 1;
                break;
            case T_INVALID:
                fprintf(stderr, "Error: Invalid token '%s'", token);
                error = 1;
                break;
            case T_NEWLINE:
                /* This is fine, move on. */
                break;
            default:
                fprintf(stderr, "Error: Expected T_OPERATION, got %s", TOKEN_TYPES[get_token(token)]);
                error = 1;
                break;
        }

        if (error) {
            do {
                token = next();
            } while (get_token(token) != T_NEWLINE);
            error = 0;
        }

        pos++;
        token = next();
    }
}

Token get_token(char *str) {
    if (strcmp(str, "\n") == 0) {
        return T_NEWLINE;
    }

    if (strcmp(str, "-1") == 0) {
        return T_LIST_END;
    }

    if (strcmp(str, ",") == 0) {
        return T_COMMA;
    }

    if (get_operation(str) != INVALID_OP) {
        return T_OPERATION;
    }

    if (strncmp(str, "SET", 3) == 0 && strlen(str) == 4) {
        return T_SET;
    }

    if (is_number(str)) {
        return T_NUMBER;
    }

    return T_INVALID;
}

Operation get_operation(char *str) {
    int i;

    char *cmds[7];
    cmds[PRINT_SET] = "print_set";
    cmds[READ_SET] = "read_set";
    cmds[UNION_SET] = "union_set";
    cmds[INTERSECT_SET] = "intersect_set";
    cmds[SUB_SET] = "sub_set";
    cmds[SYMDIFF_SET] = "symdiff_set";
    cmds[STOP_OP] = "stop";

    for (i = 0; i < 7; ++i) {
        if (strcmp(str, cmds[i]) == 0) {
            return i;
        }
    }

    return INVALID_OP;
}

char *next() {
    return strtok(NULL, " \t");
}

/* TODO: this might cause problems. */
byte is_set(char *str, char *set_names[], byte count) {
    byte i;
    for (i = 0; i < count; ++i) {
        if (strcmp(str, set_names[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

byte is_number(char *str) {
    byte i;
    for (i = 0; str[i] != '\0'; ++i) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }

    return 1;
}

set *get_set(char *str, set *valid_sets[], char *set_names[], byte count) {
    byte i;
    for (i = 0; i < count; ++i) {
        if (strcmp(str, set_names[i]) == 0) {
            return valid_sets[i];
        }
    }

    return NULL;
}

byte get_number(char *str) {
    return atoi(str);
}

void parse_command(char *token, set *sets[], char *set_names[], byte count) {
    Operation op = get_operation(token);
    switch (op) {
        case PRINT_SET:
            parse_print_cmd(token, sets, set_names, count);
        case STOP_OP:
            end = 1;
            break;
        case INVALID_OP:
        default:
            fprintf(stderr, "Error: Undefined command name '%s'.\n", token);
            error = 1;
            break;
    }
}

void parse_print_cmd(char *token, set *sets[], char *set_names[], byte count) {
    token = next();
    Token t = get_token(token);

    if (t != T_SET) {
        fprintf(stderr, "Error: Expected T_SET, got %s.\n", TOKEN_TYPES[t]);
        error = 1;
        return;
    }

    set *s = get_set(token, sets, set_names, count);
    if (s == NULL) {
        fprintf(stderr, "Error: undefined set name %s.\n", token);
        error = 1;
        return;
    }

    if (get_token(next()) != T_NEWLINE) {
        fprintf(stderr, "Error Extraneous text after end of command.\n");
    }

    print_set(*s);
}