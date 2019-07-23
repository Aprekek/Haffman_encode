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
    unsigned int weight;
    char symbol;
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