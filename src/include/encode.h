#ifndef ENCODE_H
#define ENCODE_H
#include "types.h"

h_tree *h_tree_init();
h_node *h_node_init(char ch, unsigned int weight);
void h_tree_node_add(h_tree *tree, char ch, unsigned int weight);
void h_tree_node_init(h_tree *tree, vector_s_count **vctr_s_cnt);
h_node *dequeue_min(h_tree *tree);
void queue_add(h_tree *tree, h_node *node);
unsigned int h_tree_sift(h_tree *tree, vector_s_count **vctr_s_cnt);
void dequeue_code(h_tree *tree, vector_s_count **s_codes, unsigned int size);
unsigned int encode_process(uint8_t *code_vector, vector *vctr, vector_s_count **s_codes);
#endif