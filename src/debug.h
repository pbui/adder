/* debug.h
 * Based on Zed Shaw's Awesome Debugging Macros:
 * http://c.learncodethehardway.org/book/ex20.html
 */

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define error(M, ...) fprintf(stderr, "ERROR %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#endif
