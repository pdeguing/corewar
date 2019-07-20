#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define REVERSE_BIT reverseBits
#define PERROR perror_
#define ERROR(s) ({ printf(s); exit(1);})
#define false 0
#define true 1

typedef uint8_t t_bool;
typedef uint8_t t_byte;
typedef int32_t t_word;

//lib	
void			perror_(const char *s);
void            *memcpy_(void *dst, const void *src, size_t n);
int             strlen_(char *str);
#endif