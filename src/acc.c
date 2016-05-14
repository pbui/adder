/* acc.c */

#include "lexer.h"
#include <stdio.h>

int
main(int argc, char *argv[]) {
    struct Lexer l;
    lexer_state  s;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s path\n", argv[0]);
        return EXIT_FAILURE;
    }

    s = lexer_init(&l, argv[1]);
    do {
        s = lexer_next(&l);
    } while (s == LEXER_READY);

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
