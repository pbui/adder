/* lexer.c */

#include "debug.h"
#include "lexer.h"
#include "token.h"
#include "utils.h"

#include <ctype.h>

lexer_state
lexer_init(struct Lexer *l, const char *path) {
    debug("path: %s", path);

    memset(l, 0, sizeof(struct Lexer));
    strncpy(l->path, path, BUFSIZ);

    l->stream = fopen(l->path, "r");
    if (l->stream == NULL) {
        return LEXER_IO_ERROR;
    }

    return LEXER_READY;
}

/* TODO: Re-factor? */
lexer_state
lexer_next(struct Lexer *l) {
    /* Read in next line if necessary */
    if (l->current == NULL || l->current >= l->barrier) {
        if (fgets(l->buffer, BUFSIZ, l->stream) == NULL) {
            /* FIXME: Could also be LEXER_IOERROR */
            return LEXER_FINISHED;
        }

        l->barrier = l->buffer + strlen(l->buffer);
        l->current = l->buffer;
    }

    /* Count spaces and tabs to compute indentation */
    char  *head   = l->current;
    size_t indent = 0;
    while (*head && (*head == ' ' || *head == '\t')) {
        if (*head == ' ')  indent++;
        if (*head == '\t') indent+=8;
        head++;
    }

    /* Scan for tokens */
    char  *tail   = head;
    size_t offset = 0;
    if (head == l->buffer && indent > l->indent) {
        l->token = TOKEN_INDENT;
    } else if (head == l->buffer && indent < l->indent) {
        l->token = TOKEN_DEDENT;
    } else {
        if (l->current[0] == '#') {
            while (*tail && *tail != '\r' && *tail != '\n') {
                tail++;
            }
            l->token = TOKEN_COMMENT;
        } else if (l->current[0] == '"' || l->current[0] == '\'') {
            head++;
            tail++;
            while (*tail && *tail != l->current[0]) {
                tail++;
            }
            offset = 1;
            l->token = TOKEN_STRING;
        } else if (l->current[0] == '\r' || l->current[0] == '\n') {
            while (*tail) {
                tail++;
            }
            l->token = TOKEN_NEWLINE;
        } else {
            while (*tail && !isspace(*tail)) {
                tail++;
            }
            l->token = TOKEN_UNKNOWN;
        }
    }

    size_t length = tail - head;
    strncpy(l->text, head, length);
    l->text[length] = 0;
    l->current = tail + offset;

    if (l->token == TOKEN_UNKNOWN) {
        if (strcmp(l->text, "+") == 0 ||
            strcmp(l->text, "-") == 0 ||
            strcmp(l->text, "*") == 0 ||
            strcmp(l->text, "/") == 0 ||
            strcmp(l->text, "%") == 0) {
            l->token = TOKEN_ARITHMETIC;
        } else if (strcmp(l->text, "=") == 0) {
            l->token = TOKEN_ASSIGNMENT;
        } else if (
            strcmp(l->text, "==") == 0 ||
            strcmp(l->text, ">=") == 0 ||
            strcmp(l->text, "<=") == 0 ||
            strcmp(l->text, ">" ) == 0 ||
            strcmp(l->text, "<" ) == 0 ||
            strcmp(l->text, "!=") == 0) {
            l->token = TOKEN_COMPARISON;
        } else if (strcmp(l->text, "if") == 0) {
            l->token = TOKEN_IF;
        } else if (strcmp(l->text, "while") == 0) {
            l->token = TOKEN_WHILE;
        } else if (strcmp(l->text, "print") == 0) {
            l->token = TOKEN_PRINT;
        } else if (strcmp(l->text, "input") == 0) {
            l->token = TOKEN_INPUT;
        } else if (is_numeric(l->text)) {
            l->token = TOKEN_INTEGER;
        } else {
            l->token = TOKEN_IDENTIFIER;
        }
    }

    debug("l->text: %s", l->text);
    debug("l->token: %s", TOKEN_STRINGS[l->token]);
    return LEXER_READY;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
