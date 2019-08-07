#ifndef NODE_H
#define NODE_H
#include "types.h"

s_node *sNode_init(__size_smbls symbol, uint8_t lenght, code_type code);
s_node **s_node_itit(__size_smbls count);
void s_tree_node_add(s_node **tree, s_node **node, __size_smbls count);
void s_node_add(s_node *tree, s_node *node);
void s_node_sort(s_node **node, __size_smbls count);
#endif