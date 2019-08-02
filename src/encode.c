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
void h_tree_node_init(h_tree *tree, vector_s_count **vctr_s_cnt)
{
    for (unsigned int i = 0; i < symbols; i++)
    {
        if (vctr_s_cnt[i]->weight != 0)
            h_tree_node_add(tree, vctr_s_cnt[i]->symbol, vctr_s_cnt[i]->weight);
    }
}

h_node *dequeue_min(h_tree *tree)
{
    h_node *node = tree->head, *prew = NULL;

    if ((node->left == NULL) && (node->ajacent == NULL))
    {
        tree->head = node->right;
        tree->size--;
        node->right = NULL;
        return node;
    }

    while ((node->right != NULL) || (node->left != NULL) || (node->ajacent != NULL))
    {
        prew = node;
        if ((node->left != NULL) && (node->s != -1))
        {
            node = node->left;
        }
        else if ((tree->head->s == -1) || (tree->head->left == NULL))
        {
            tree->head = node->ajacent;
            tree->size--;
            node->ajacent = NULL;
            return node;
        }
        else
        {
            tree->head->left = node->ajacent;
            tree->size--;
            node->ajacent = NULL;
            return node;
        }
    }

    prew->left = NULL; //если левый элемент оказался наименьшим
    tree->size--;
    return node;
}

void queue_add(h_tree *tree, h_node *node)
{
    if (tree->size == 0)
    {
        tree->head = node;
        tree->size++;
        return;
    }
    h_node *n = tree->head;
    //    h_node *prew = n;
    while (1)
    {
        if ((node->weight > n->weight) && (n->right != NULL) && (n->s != -1))
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
                tree->size++;
                return;
            }
            else
            {
                if (n->left == NULL)
                {
                    n->left = node;
                    tree->size++;
                    return;
                }
                else
                {
                    n = n->left;
                    while (n->ajacent != NULL)
                        n = n->ajacent;
                    n->ajacent = node;
                    tree->size++;
                    return;
                }
            }
        }
        else if (n->s == -1)
        {
            while (n->ajacent != NULL)
                n = n->ajacent;
            n->ajacent = node;
            tree->size++;
            return;
        }
        else if (node->weight == n->weight)
        {
            if (n->left == NULL)
            {
                n->left = node;
                tree->size++;
                return;
            }
            else
            {
                n = n->left;
                while (n->ajacent != NULL)
                    n = n->ajacent;
                n->ajacent = node;
                tree->size++;
                return;
            }
        }
        else
        {
            while ((n->left != NULL) || (n->s != -1))
                n = n->left;
            if (n->s == -1)
            {
                while (n->ajacent != NULL)
                    n = n->ajacent;
                n->ajacent = node;
                tree->size++;
                return;
            }
            else
            {
                n->left = node;
                tree->size++;
                return;
            }
        }
    }
}

unsigned int h_tree_sift(h_tree *tree, vector_s_count **vctr_s_cnt)
{
    h_tree_node_init(tree, vctr_s_cnt);
    unsigned int size = tree->size;
    while (tree->size > 1)
    {
        h_node *node_1 = dequeue_min(tree);
        h_node *node_2 = dequeue_min(tree);
        h_node *node = h_node_init(-1, 0);
        node->left = node_2;
        node->right = node_1;
        node->weight = node_1->weight + node_2->weight;
        queue_add(tree, node);
    }
    return size;
}

void dequeue_code(h_tree *tree, vector_s_count **s_codes, unsigned int size)
{
    code_type code = 0;
    unsigned int length = 0;
    h_node *node = NULL, *prew = NULL;
    while (size > 0)
    {
        node = tree->head;
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
        if (node->s != -1)
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

unsigned int encode_process(uint8_t *code_vector, vector *vctr, vector_s_count **s_codes)
{
    code_type code = 0x0;
    code_type tmp_code = 0x0;
    char lenght = 0;
    char byte_lenght = 0;
    unsigned int total_bytes = 0;
    unsigned int ch_int;
    char old_lenght;

    for (unsigned int i = 0; i < vctr->size; i++)
    {
        if (byte_lenght == 8)
        {
            byte_lenght = 0;
            total_bytes++;
        }

        ch_int = vctr->array[i];
        tmp_code = s_codes[ch_int]->code;
        lenght = s_codes[ch_int]->lenght;

        if (byte_lenght + lenght <= 8)
        {
            code_vector[total_bytes] |= tmp_code;
            byte_lenght += lenght;
            code_vector[total_bytes] <<= (8 - byte_lenght);
        }
        else
        {
            while (lenght > 0)
            {
                if (byte_lenght == 8)
                {
                    byte_lenght = 0;
                    total_bytes++;
                }

                code = tmp_code;
                old_lenght = lenght;
                lenght = lenght - (8 - byte_lenght);

                if (lenght >= 0)
                {
                    tmp_code >>= lenght;
                    byte_lenght += old_lenght - lenght;
                }

                code_vector[total_bytes] |= tmp_code;

                if (lenght < 0)
                {
                    code_vector[total_bytes] <<= (abs(lenght));
                    byte_lenght = old_lenght;
                }

                if (lenght > 0)
                {
                    tmp_code = code << (sizeof(code_type) * 8 - lenght);
                    tmp_code >>= sizeof(code_type) * 8 - lenght;
                }
            }
        }
    }
    return total_bytes;
}