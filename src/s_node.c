#include <stdio.h>
#include <stdlib.h>
#include "include/types.h"
#include "include/s_node.h"

s_node *s_node_itit(__size_smbls count)
{
    s_node *n = (s_node *)malloc(sizeof(s_node) * count);
    if (n != NULL)
    {
        for (unsigned int i = 0; i < count; i++)
        {
            n[i].symbol = 0;
            n[i].code = 0;
            n[i].lenght = 0;
            n[i].left = NULL;
            n[i].right = NULL;
            n[i].ajacent = NULL;
        }
    }
    return n;
}

void s_node_sort(s_node *node, __size_smbls count)
{
    for (__size_smbls i = 0; i < count - 1; i++)
        for (__size_smbls j = 0; j < count - i - 1; j++)
            if (node[j].lenght > node[j + 1].lenght)
            {
                s_node temp = node[j + 1];
                node[j + 1] = node[j];
                node[j] = temp;
            }
}

void s_tree_node_add(tree *fds, s_node *node, __size_smbls count)
{
    __size_smbls mid = (count / 2);
    fds->head = &node[mid];
    if (count > 1)
    {
        for (__size_smbls i = 0; i < mid; i++)
            s_node_add(fds, &node[i]);
        for (__size_smbls i = mid + 1; i < count; i++)
            s_node_add(fds, &node[i]);
    }
}

void s_node_add(tree *fds, s_node *node)
{
    s_node *prew;
    s_node *tre = fds->head;
    while (tre != NULL)
    {
        prew = tre;
        if (node->lenght > tre->lenght)
            tre = tre->right;
        else if (node->lenght == tre->lenght)
            tre = tre->ajacent;
        else
            tre = tre->left;
    }
    if (node->lenght > prew->lenght)
        prew->right = node;
    else if (node->lenght == prew->lenght)
        prew->ajacent = node;
    else
        prew->left = node;
}

int search_symbol(tree *fds, code_type code, uint8_t lenght)
{
    char flag = 1;
    int symbol = -1;
    s_node *tre = fds->head;
    while ((flag == 1) && (tre != NULL))
    {
        if (lenght < tre->lenght)
            tre = tre->left;
        else if (lenght > tre->lenght)
            tre = tre->right;
        else if ((lenght == tre->lenght) && (code == tre->code))
        {
            flag = 0;
            symbol = tre->symbol;
        }
        else
            tre = tre->ajacent;
    }

    return symbol;
}