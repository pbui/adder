/* lexer.h */

#ifndef LEXER_H
#define LEXER_H

#include "token.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    LEXER_READY,
    LEXER_FINISHED,
    LEXER_IO_ERROR,
} lexer_state;

struct Lexer {
    char    path[BUFSIZ];
    char    buffer[BUFSIZ];
    char    text[BUFSIZ];
    char   *barrier;
    char   *current;
    FILE   *stream;
    Token   token;
    size_t  line;
    size_t  indent;
};

lexer_state lexer_init(struct Lexer *l, const char *path);
lexer_state lexer_next(struct Lexer *l);

#endif

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
