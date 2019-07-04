#include <stdio.h>
#include <stdlib.h>
#include "include/types.h"
#include "include/vector.h"

extern size_t capacity;

vector *vector_init()
{
    vector *v = malloc(sizeof(*v));
    if (v != NULL)
    {
        v->capacity = capacity;
        v->size = 0;
        v->array = malloc(capacity * sizeof(char));
        if (v->array == NULL)
        {
            free(v);
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
    return v;
}
int vector_push_back(vector *v, char item)
{
    if (v == NULL || v->array == NULL)
        return -1;
    if (v->capacity == 0)
        return 0;

    if (v->size + 1 <= v->capacity)
    {
        v->array[v->size] = item;
        v->size++;
    }
    else
    {
        char *helper = realloc(v->array, 2 * v->capacity * sizeof(char));
        if (helper == NULL)
            return -1;
        v->array = helper;
        v->array[v->size++] = item;
        v->capacity *= 2;
    }
    return 0;
}