#include <stdio.h>
#include <stdlib.h>
#include "include/types.h"
#include "include/h_node_h_tree.h"

extern size_t symbols;

h_tree *h_tree_init()
{
    h_tree *h_tre = malloc(sizeof(*h_tre));
    if (h_tre != NULL)
    {
        h_tre->size = 0;
        h_tre->head = NULL;
    }
    return h_tre;
}

h_node *h_node_init(__size_smbls ch, unsigned int weight, char flag)
{
    h_node *node = malloc(sizeof(*node));
    if (node != NULL)
    {
        node->weight = weight;
        node->s = ch;
        node->flag = flag;
        node->ajacent = NULL; //когда созданный узел получился с самым большим или равным
                              // весом и добавление следующих узлов больше него
                              //происходят по этому указателю
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void h_tree_node_add(h_tree *h_tre, __size_smbls ch, unsigned int weight)
{

    h_node *node = h_node_init(ch, weight, 0);
    if (node == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (h_tre->head == NULL)
    {
        h_tre->head = node;
        h_tre->size++;
        return;
    }

    h_node *n = h_tre->head;

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
    h_tre->size++;
}

void h_tree_node_init(h_tree *h_tre, vector_s_count **vctr_s_cnt)
{
    for (unsigned int i = 0; i < symbols; i++)
    {
        if (vctr_s_cnt[i]->weight != 0)
            h_tree_node_add(h_tre, vctr_s_cnt[i]->symbol, vctr_s_cnt[i]->weight);
    }
}

h_node *dequeue_min(h_tree *h_tre)
{
    h_node *node = h_tre->head, *prew = NULL;

    if ((node->left == NULL) && (node->ajacent == NULL))
    {
        h_tre->head = node->right;
        h_tre->size--;
        node->right = NULL;
        return node;
    }

    while ((node->right != NULL) || (node->left != NULL) || (node->ajacent != NULL))
    {
        if ((node->left != NULL) && (node->flag != -1))
        {
            prew = node;
            node = node->left;
        }
        else if ((h_tre->head->flag == -1) || (h_tre->head->left == NULL))
        {
            h_tre->head = node->ajacent;
            h_tre->size--;
            node->ajacent = NULL;
            return node;
        }
        else if (prew == h_tre->head)
        {
            h_tre->head->left = node->ajacent;
            h_tre->size--;
            node->ajacent = NULL;
            return node;
        }
        else
        {
            prew->left = node->ajacent;
            h_tre->size--;
            node->ajacent = NULL;
            return node;
        }
    }

    prew->left = NULL; //если левый элемент оказался наименьшим
    h_tre->size--;
    return node;
}

void queue_add(h_tree *h_tre, h_node *node)
{
    if (h_tre->size == 0)
    {
        h_tre->head = node;
        h_tre->size++;
        return;
    }
    h_node *n = h_tre->head;
    //    h_node *prew = n;
    while (1)
    {
        if ((node->weight > n->weight) && (n->right != NULL) && (n->flag != -1))
        {
            // prew = n;
            n = n->right;
        }
        else if (n->right == NULL)
        {
            if (node->weight >= n->weight)
            {
                while (n->ajacent != NULL)
                    n = n->ajacent;
                n->ajacent = node;
                h_tre->size++;
                return;
            }
            else
            {
                if (n->left == NULL)
                {
                    n->left = node;
                    h_tre->size++;
                    return;
                }
                else
                {
                    n = n->left;
                    while (n->ajacent != NULL)
                        n = n->ajacent;
                    n->ajacent = node;
                    h_tre->size++;
                    return;
                }
            }
        }
        else if (n->flag == -1)
        {
            while (n->ajacent != NULL)
                n = n->ajacent;
            n->ajacent = node;
            h_tre->size++;
            return;
        }
        else if (node->weight == n->weight)
        {
            if (n->left == NULL)
            {
                n->left = node;
                h_tre->size++;
                return;
            }
            else
            {
                n = n->left;
                while (n->ajacent != NULL)
                    n = n->ajacent;
                n->ajacent = node;
                h_tre->size++;
                return;
            }
        }
        else
        {
            while ((n->left != NULL) && (n->flag != -1))
                n = n->left;
            if (n->flag == -1)
            {
                while (n->ajacent != NULL)
                    n = n->ajacent;
                n->ajacent = node;
                h_tre->size++;
                return;
            }
            else
            {
                n->left = node;
                h_tre->size++;
                return;
            }
        }
    }
}

unsigned int h_tree_sift(h_tree *h_tre, vector_s_count **vctr_s_cnt)
{
    h_tree_node_init(h_tre, vctr_s_cnt);
    unsigned int size = h_tre->size;
    while (h_tre->size > 1)
    {
        h_node *node_1 = dequeue_min(h_tre);
        h_node *node_2 = dequeue_min(h_tre);
        h_node *node = h_node_init(0, 0, -1);
        node->left = node_2;
        node->right = node_1;
        node->weight = node_1->weight + node_2->weight;
        queue_add(h_tre, node);
    }
    return size;
}

void extraction_code(h_tree *h_tre, vector_s_count **s_codes, unsigned int size)
{
    code_type code = 0;
    unsigned int length = 0;
    h_node *node = NULL, *prew = NULL;
    while (size > 0)
    {
        node = h_tre->head;
        while ((node->left != NULL) || (node->right) != NULL)
        {
            prew = node;
            if (length != 0)
                code <<= 1;
            if (node->left != NULL)
            {
                node = node->left;
            }
            else if (node->right != NULL)
            {
                node = node->right;
                code |= 0x1;
            }
            length++;
        }
        if (node->flag != -1)
        {
            int int_char = node->s;
            s_codes[int_char]->code = code;
            s_codes[int_char]->lenght = length;
            size--;
        }
        if ((code & 0x1) == 0x0)
            prew->left = NULL;
        else
            prew->right = NULL;
        code = 0x0;
        length = 0;
    }
}