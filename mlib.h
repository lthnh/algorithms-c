#ifndef MY_LIBRARY_H
#define MY_LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#if __has_include(<unistd.h>)
    #define MEM_ALLOC_ERR_CHCK(ptr) \
    if (ptr == NULL) {\
        char *err_msg = strerror(errno); \
        fprintf(stderr, "%s\nat %s, line %d.\n", err_msg, __FILE__, __LINE__); \
        exit(EXIT_FAILURE); \
    }
#endif

#define CUSTM_ERR_MSG(msg) \
    fprintf(stderr, msg); \
    fprintf(stderr, "at %s, line %d.", __FILE__, __LINE__); \
    exit(EXIT_FAILURE);

#endif