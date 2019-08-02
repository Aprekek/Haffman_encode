#ifndef TYPES_H
#define TYPES_H
#include <inttypes.h>
typedef struct
{
    char *array;
    unsigned int size;
    unsigned int capacity;
} vector;

typedef struct
{
    char symbol;
    uint8_t code;
    unsigned int weight;
    unsigned int lenght;
} vector_s_count;

typedef struct h_node h_node;

struct h_node
{
    unsigned int weight;
    char s;
    h_node *ajacent;
    h_node *left;
    h_node *right;
};
typedef struct
{
    unsigned int size;
    h_node *head;
} h_tree;
#endif