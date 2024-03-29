#ifndef NODE_H_TREE_H
#define NODE_H_TREE_H

#include "types.h"
h_tree *h_tree_init();
h_node *h_node_init(__size_smbls ch, unsigned int weight, char flag);
void h_tree_node_add(h_tree *tree, __size_smbls ch, unsigned int weight);
void h_tree_node_init(h_tree *tree, vector_s_count **vctr_s_cnt);
h_node *dequeue_min(h_tree *tree);
void queue_add(h_tree *tree, h_node *node);
unsigned int h_tree_sift(h_tree *tree, vector_s_count **vctr_s_cnt);
void extraction_code(h_tree *tree, vector_s_count **s_codes, unsigned int size);

#endif