#include <stdio.h>
#include <stdlib.h>
#include "include/types.h"
#include "include/s_node.h"

s_node **node_itit(__size_smbls count)
{
    s_node **n = (s_node **)malloc(sizeof(*n) * count);
    if (n != NULL)
    {
        for (unsigned int i = 0; i < count; i++)
        {
            n[i] = (s_node *)malloc(sizeof(n));
            n[i]->symbol = 0;
            n[i]->lenght = 0;
            n[i]->code = 0;
        }
    }
    return n;
}