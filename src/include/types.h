#ifndef TYPES_H
#define TYPES_H
#include <inttypes.h>

#define code_type uint16_t
#define __size_smbls uint8_t

typedef struct
{
    char *array;
    unsigned int size;
    unsigned int capacity;
} vector;

typedef struct
{
    __size_smbls symbol;
    code_type code;
    unsigned int weight;
    uint8_t lenght;
} vector_s_count;

typedef struct h_node h_node;

struct h_node
{
    unsigned int weight;
    __size_smbls s;
    char flag;
    h_node *ajacent;
    h_node *left;
    h_node *right;
};

typedef struct
{
    unsigned int size;
    h_node *head;
} h_tree;

typedef struct s_node s_node;

struct s_node
{
    uint8_t symbol;
    uint8_t lenght;
    uint16_t code;
    s_node *ajacent;
    s_node *left;
    s_node *right;
};

#endif