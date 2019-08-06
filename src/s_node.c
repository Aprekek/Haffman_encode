#include <stdio.h>
#include <stdlib.h>
#include "include/types.h"
#include "include/s_node.h"

s_node **s_node_itit(__size_smbls count)
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

s_tree *s_tree_init()
{
    s_tree *tree = malloc(sizeof(*tree));
    if (tree != NULL)
    {
        tree->size = 0;
        tree->head = NULL;
    }
    return tree;
}

void s_node_sort(s_node **node, __size_smbls count)
{
    for (unsigned int i = 0; i < count - 1; i++)
        for (unsigned int j = 0; j < count - i - 1; j++)
            if ((node[j]->code > node[j + 1]->code) ||
                ((node[j]->code == node[j + 1]->code) && (node[j]->lenght > node[j + 1]->lenght)))
            {
                s_node *temp = node[j + 1];
                node[j + 1] = node[j];
                node[j] = temp;
            }
}
