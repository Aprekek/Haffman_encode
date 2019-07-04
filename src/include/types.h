#ifndef TYPES_H
#define TYPES_H

typedef struct
{
    char *array;
    unsigned int size;
    unsigned int capacity;
} vector;

typedef struct
{
    unsigned int count;
    unsigned char symbol;
} vector_s_count;

#endif