#include <stdio.h>
#include <stdlib.h>
#include "include/types.h"
#include "include/encode.h"

extern size_t symbols;

h_tree *h_tree_init()
{
    h_tree *tree = malloc(sizeof(*tree));
    if (tree != NULL)
    {
        tree->size = 0;
        tree->head = NULL;
    }
    return tree;
}

h_node *h_node_init(char ch, unsigned int weight)
{
    h_node *node = malloc(sizeof(*node));
    if (node != NULL)
    {
        node->weight = weight;
        node->s = ch;
        node->ajacent = NULL; //когда созданный узел получился с самым большим или равным
                              // весом и добавление следующих узлов больше него
                              //происходят по этому указателю
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void h_tree_node_add(h_tree *tree, char ch, unsigned int weight)
{
    if (weight == 0)
        return;

    h_node *node = h_node_init(ch, weight);

    if (tree->head == NULL)
    {
        tree->head = node;
        tree->size++;
        return;
    }

    h_node *n = tree->head;

    while (n->right != NULL)
        n = n->right;

    if (node->weight == n->weight)
    {
        while (n->left != NULL)
            n = n->left;
        n->left = node;
    }
    else
        n->right = node;
    tree->size++;
}
void h_tree_node_init(h_tree *tree, vector_s_count *vctr_s_cnt)
{
    for (unsigned int i = 0; i < symbols; i++)
    {
        h_tree_node_add(tree, vctr_s_cnt[i].symbol, vctr_s_cnt[i].weight);
    }
}

h_node *dequeue_min(h_tree *tree)
{
    if (tree->size == 0)
        return NULL;

    h_node *node = tree->head, *prew = NULL;

    if ((node->left == NULL) && (node->ajacent == NULL))
    {
        tree->head = node->right;
        tree->size--;
        return node;
    }

    while ((node->right != NULL) || (node->left != NULL) || (node->ajacent != NULL))
    {
        prew = node;
        if (node->left != NULL)
        {
            node = node->left;
        }
        else
        {
            if (prew->right == NULL)
                tree->head = node->ajacent;
            else
                prew->left = node->ajacent;

            tree->size--;
            return node;
        }
    }

    prew->left = NULL; //если левый элемент оказался наименьшим
    tree->size--;
    return node;
}