#ifndef NODE_H
#define NODE_H
#include "types.h"

s_node *s_node_itit(__size_smbls count);
void s_tree_node_add(tree* fds, s_node *node, __size_smbls count);
void s_node_add(tree *fds, s_node *node);
void s_node_sort(s_node *node, __size_smbls count);
int search_symbol(tree *fds, code_type code, uint8_t lenght);
#endif
