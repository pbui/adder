/* utils.c */

#include <ctype.h>
#include <stdbool.h>

bool
is_numeric(const char *s) {
    while (*s) {
    	if (!isdigit(*s)) {
    	    return false;
	}
	s++;
    }

    return true;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
