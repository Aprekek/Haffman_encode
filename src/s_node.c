#include <stdio.h>
#include <stdlib.h>
#include "include/types.h"
#include "include/s_node.h"

s_node **s_node_itit(__size_smbls count)
{
    s_node **n = (s_node **)malloc(sizeof(*n) * count);
    for (unsigned int i = 0; i < count; i++)
        n[i] = (s_node *)malloc(sizeof(n));
    if (n != NULL)
    {
        for (unsigned int i = 0; i < count; i++)
        {
            n[i]->symbol = 0;
            n[i]->code = 0;
            n[i]->lenght = 0;
            n[i]->left = NULL;
            n[i]->right = NULL;
            n[i]->ajacent = NULL;
        }
    }
    return n;
}

void s_node_sort(s_node **node, __size_smbls count)
{
    for (__size_smbls i = 0; i < count - 1; i++)
        for (__size_smbls j = 0; j < count - i - 1; j++)
            if (node[j]->lenght > node[j + 1]->lenght)
            {
                s_node *temp = node[j + 1];
                node[j + 1] = node[j];
                node[j] = temp;
            }
}

void s_tree_node_add(s_node **tree, s_node **node, __size_smbls count)
{
    __size_smbls mid = (count / 2);

    *tree = node[mid];
    if (count > 1)
    {
        for (__size_smbls i = 0; i < mid; i++)
            s_node_add(*tree, node[i]);
        for (__size_smbls i = mid + 1; i < count; i++)
            s_node_add(*tree, node[i]);
    }
}

void s_node_add(s_node *tree, s_node *node)
{
    s_node *prew;

    while (tree != NULL)
    {
        prew = tree;
        if (node->lenght > tree->lenght)
            tree = tree->right;
        else if (node->lenght == tree->lenght)
            tree = tree->ajacent;
        else
            tree = tree->left;
    }
    if (node->lenght > prew->lenght)
        prew->right = node;
    else if (node->lenght == prew->lenght)
        prew->ajacent = node;
    else
        prew->left = node;
}

int search_symbol(s_node *tree, code_type code, uint8_t lenght)
{
    char flag = 1;
    int symbol = -1;
    while ((flag == 1) && (tree != NULL))
    {
        if (lenght < tree->lenght)
            tree = tree->left;
        else if (lenght > tree->lenght)
            tree = tree->right;
        else if ((lenght == tree->lenght) && (code == tree->code))
        {
            flag = 0;
            symbol = tree->symbol;
        }
        else
            tree = tree->ajacent;
    }
    return symbol;
}