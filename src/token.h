/* token.h */

#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_INDENT,
    TOKEN_DEDENT,
    TOKEN_NEWLINE,
    TOKEN_COMMENT,
    TOKEN_STRING,
    TOKEN_INTEGER,
    TOKEN_IDENTIFIER,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_ASSIGNMENT,
    TOKEN_PRINT,
    TOKEN_INPUT,
    TOKEN_ARITHMETIC,
    TOKEN_COMPARISON,
    TOKEN_UNKNOWN
} Token;

extern const char *TOKEN_STRINGS[];

#endif

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
